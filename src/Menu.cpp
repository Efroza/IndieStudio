/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** Menu
*/

#include "../include/Menu.hpp"
#include "../include/Map.hpp"
#include "../include/Screen.hpp"

Menu::Menu(Raylib *raylib) : _raylib(raylib)
{
    _cursor = new Animation(_raylib->LoadImageToTexture("cursor"), 1, RAYWHITE, {0, 0});
    _menu = true;
    _rect_cursor = {0.0f, 0.0f, 64.0f, 64.0f};
    _buttons.insert(std::make_pair("play", std::unique_ptr<Button>(new Button({300.0f, 500.0f}, {126.0f, 60.0f}, " Play ", [&](){launchGame();}))));
    _buttons.insert(std::make_pair("quit", std::unique_ptr<Button>(new Button({300.0f, 800.0f}, {126.0f, 60.0f}, " Quit ", [&](){quit();}))));
    _buttons.insert(std::make_pair("option", std::unique_ptr<Button>(new Button({300.0f, 600.0f}, {198.0f, 60.0f}, " Settings ", [&](){optionMenu();}))));
    _buttons.insert(std::make_pair("help", std::unique_ptr<Button>(new Button({300.0f, 700.0f}, {126.0f, 60.0f}, " Help ", [&](){helpMenu();}))));
    _buttons.insert(std::make_pair("back", std::unique_ptr<Button>(new Button({0.0f, HEIGHT}, {170.0f, 60.0f}, "Go back", [&](){reset();}))));
    _buttons_option.insert(std::make_pair("back", std::unique_ptr<Button>(new Button({0.0f, 1000.0f}, {170.0f, 60.0f}, "Go back", [&](){reset();}))));
    _buttons_option.insert(std::make_pair("-", std::unique_ptr<Button>(new Button({830.0f, 320.0f}, {60.0f, 60.0f}, " - ", [&](){_raylib->lessVolume();}))));
    _buttons_option.insert(std::make_pair("+", std::unique_ptr<Button>(new Button({1230.0f, 320.0f}, {60.0f, 60.0f}, " + ", [&](){_raylib->addVolume();}))));
    _buttons_option.insert(std::make_pair("30", std::unique_ptr<Button>(new Button({810.0f, 520.0f}, {90.0f, 60.0f}, " 30 ", [&](){_raylib->setFps(30);}))));
    _buttons_option.insert(std::make_pair("60", std::unique_ptr<Button>(new Button({1010.0f, 520.0f}, {90.0f, 60.0f}, " 60 ", [&](){_raylib->setFps(60);}))));
    _buttons_option.insert(std::make_pair("120", std::unique_ptr<Button>(new Button({1210.0f, 520.0f}, {108.0f, 60.0f}, " 120 ", [&](){_raylib->setFps(120);}))));
    _buttons_option.insert(std::make_pair("left", std::unique_ptr<Button>(new Button({830.0f, 720.0f}, {60.0f, 60.0f}, " < ", [&](){_raylib->changeCurrentMusicLeft();}))));
    _buttons_option.insert(std::make_pair("right", std::unique_ptr<Button>(new Button({1430.0f, 720.0f}, {60.0f, 60.0f}, " > ", [&](){_raylib->changeCurrentMusicRight();}))));
    _buttons_help.insert(std::make_pair("back", std::unique_ptr<Button>(new Button({0.0f, 1000.0f}, {170.0f, 60.0f}, "Go back", [&](){reset();}))));
    HideCursor();
}

Menu::~Menu()
{
}

std::map<std::string, Animation *> Menu::createAnimation(std::vector<std::string> list_string, std::vector<int> list_int, std::vector<Color> list_color, std::vector<std::pair<float, float>> list_position)
{
    std::map<std::string, Animation *> map_animation;
    for (int i = 0; i < list_string.size(); i++)
    {
        map_animation[list_string[i]] = new Animation(_raylib->LoadImageToTexture(list_string[i]), list_int[i], list_color[i], list_position[i]);
    }
    return map_animation;
}

void Menu::AnimationBeforeMenu(void)
{
    std::map<std::string, Animation *> animation = createAnimation({"logo_image", "character_animation_first", "bomb_image_animation", "explosion_menu", "logo_epitech", "background_menu"}, {1, 7, 3, 5, 1, 1}, {RAYWHITE, RAYWHITE, RAYWHITE, RAYWHITE, Color{255, 255, 255, 0}, RAYWHITE}, {{float(WIDTH / 2 - 160), float(HEIGHT / 2 - 200)}, {-200.0f, 280.0f}, {float(WIDTH / 2), float(HEIGHT / 2 - 100)}, {float(WIDTH / 2), 0.0f}, {float(WIDTH / 2 - 160), 0.0f}, {0.0f, 0.0f}});
    Rectangle rectangle{animation["logo_image"]->getPosition().first, animation["logo_image"]->getPosition().second, (float)animation["logo_image"]->getTexture().width, (float)animation["logo_image"]->getTexture().height};
    std::pair<int, int> position_character = {animation["character_animation_first"]->getPosition().first, animation["character_animation_first"]->getPosition().second};
    std::pair<int, int> position_bomb = {animation["bomb_image_animation"]->getPosition().first, animation["bomb_image_animation"]->getPosition().second};
    float time_switch = 0;
    float width_background = 0;
    bool explosion_done = false;
    int frame_counter = 0;
    Color logo_epitech_color = animation["logo_epitech"]->getColor();

    while (!_raylib->isWindowClosed())
    {
        _raylib->updateMusic();
        _cursor->setPosition(_raylib->getMousePosition());
        time_switch += _raylib->getFrameTime();
        time_switch >= 0.2f ? time_switch = 0, animation["character_animation_first"]->addToFrameWidth(1) : reset();
        animation["character_animation_first"]->setFrameWidth(float((int)animation["character_animation_first"]->getFrameWidth() % (int)animation["character_animation_first"]->getMaxFrame()));
        _raylib->StartAndEndDrawing(true);
        ClearBackground(BLACK);
        _raylib->drawTexture(animation["logo_image"]->getPosition(), animation["logo_image"]->getTexture(), animation["logo_image"]->getColor());
        _raylib->drawRectangle({rectangle.x, rectangle.y}, {rectangle.width, rectangle.height}, BLACK);
        explosion_done == true && position_bomb.second != -100 ? _raylib->drawTextureRectangle(animation["explosion_menu"]->getPosition(), Rectangle{animation["explosion_menu"]->getNbOfFrameWidth() * animation["explosion_menu"]->getFrameWidth(), animation["explosion_menu"]->getNbOfFrameHeight() * animation["explosion_menu"]->getFrameHeight(), animation["explosion_menu"]->getNbOfFrameWidth(), animation["explosion_menu"]->getNbOfFrameHeight()}, animation["explosion_menu"]->getColor(), animation["explosion_menu"]->getTexture()) : reset();
        position_bomb.second == -100 ? logo_epitech_color.a++, _raylib->drawTexture(animation["logo_epitech"]->getPosition(), animation["logo_epitech"]->getTexture(), logo_epitech_color) : reset();
        position_character.first >= WIDTH / 2 && position_bomb.second <= HEIGHT - 100 && position_bomb.second != -100 ? _raylib->drawTextureRectangle(animation["bomb_image_animation"]->getPosition(), Rectangle{animation["bomb_image_animation"]->getFrameWidth() * animation["bomb_image_animation"]->getNbOfFrameWidth(), 0, animation["bomb_image_animation"]->getNbOfFrameWidth(), (float)animation["bomb_image_animation"]->getTexture().height}, animation["bomb_image_animation"]->getColor(), animation["bomb_image_animation"]->getTexture()) : reset();
        _raylib->drawTextureRectangle(animation["character_animation_first"]->getPosition(), Rectangle{animation["character_animation_first"]->getFrameWidth() * animation["character_animation_first"]->getNbOfFrameWidth(), 0, animation["character_animation_first"]->getNbOfFrameWidth(), (float)animation["character_animation_first"]->getTexture().height}, animation["character_animation_first"]->getColor(), animation["character_animation_first"]->getTexture());
        _raylib->drawTextureRectangle(animation["background_menu"]->getPosition(), Rectangle{0, 0, width_background, HEIGHT}, animation["background_menu"]->getColor(), animation["background_menu"]->getTexture());
        _raylib->drawFPS({10, 10});
        _raylib->drawTextureRectangle(_cursor->getPosition(), _rect_cursor, _cursor->getColor(), _cursor->getTexture());
        _raylib->StartAndEndDrawing(false);
        position_bomb.second > HEIGHT - 100 &&!explosion_done ? explosion_done = true, animation["explosion_menu"]->setPosition({animation["explosion_menu"]->getPosition().first - 100, position_bomb.second - 200}), animation["logo_epitech"]->setPosition({WIDTH / 2 - 100, position_bomb.second - 100}) : reset();
        position_character.first >= WIDTH / 2 &&position_bomb.second > -100 ? position_bomb.second += 2 : position_bomb.second;
        animation["bomb_image_animation"]->setPosition(position_bomb);
        position_character.first += 3;
        animation["character_animation_first"]->setPosition(position_character);
        position_character.first >= animation["logo_image"]->getPosition().first - 30 ? rectangle.x += 3 : rectangle.x;
        position_character.first >= WIDTH + 200 ? width_background += 8 : width_background;
        if (width_background >= WIDTH || _raylib->keyPressed(KEY_SPACE))
            break;
        if (explosion_done)
        {
            frame_counter++;
            if (frame_counter > 2)
            {
                animation["explosion_menu"]->addToFrameWidth(1);
                if (animation["explosion_menu"]->getFrameWidth() >= 5)
                {
                    animation["explosion_menu"]->setFrameWidth(0);
                    animation["explosion_menu"]->addToFrameHeight(1);
                    if (animation["explosion_menu"]->getFrameHeight() >= 5)
                    {
                        animation["explosion_menu"]->setFrameHeight(0);
                        explosion_done = false;
                        position_bomb.second = -100;
                    }
                }
            }
        }
    }
    if (!IsKeyPressed(KEY_ESCAPE))
        LaunchMenu(animation["background_menu"]->getTexture());
}

void Menu::button_pressed(std::pair<float, float> mouse_position)
{
    if (_raylib->isMousePressed())
    {
        for (auto &it : _buttons)
        {
            if (it.second->getText().compare("Go back") != 0)
                it.second->isClicked(mouse_position) ? it.second->action() : reset();
        }
    }
}

void Menu::LaunchMenu(Texture2D background)
{
    Font font = _raylib->loadFont("font_gamer");

    while (!_raylib->isWindowClosed() && _menu)
    {
        _raylib->updateMusic();
        _cursor->setPosition(_raylib->getMousePosition());
        _raylib->StartAndEndDrawing(true);
        ClearBackground(BLACK);
        _raylib->drawTextureRectangle(std::make_pair(0, 0), Rectangle{0, 0, WIDTH, HEIGHT}, WHITE, background);
        print_buttons(font);
        _raylib->drawFPS({10, 10});
        _raylib->drawTextureRectangle(_cursor->getPosition(), _rect_cursor, _cursor->getColor(), _cursor->getTexture());
        _raylib->StartAndEndDrawing(false);
        button_pressed(_raylib->getMousePosition());
    }
    ShowCursor();
    if (font.glyphCount > 0)
        UnloadFont(font);
}

void Menu::print_buttons(Font font)
{
    for (auto &it : _buttons)
    {
        if (it.second->getText().compare("Go back") != 0)
        {
            _raylib->drawRectangle({it.second->getRectangle().x, it.second->getRectangle().y}, {it.second->getRectangle().width, it.second->getRectangle().height}, BLACK);
            _raylib->drawText(it.second->getPosition(), it.second->getText(), WHITE, font, 50);
        }
        if (_raylib->getMousePosition().first >= it.second->getPosition().first && _raylib->getMousePosition().first <= it.second->getPosition().first + it.second->getSize().first &&
            _raylib->getMousePosition().second >= it.second->getPosition().second && _raylib->getMousePosition().second <= it.second->getPosition().second + it.second->getSize().second)
        {
            if (it.second->getText().compare("Go back") != 0)
            {
                _raylib->drawRectangle({it.second->getRectangle().x, it.second->getRectangle().y}, {it.second->getRectangle().width, it.second->getRectangle().height}, PURPLE);
                _raylib->drawText(it.second->getPosition(), it.second->getText(), WHITE, font, 50);
            }
        }
    }
}

void Menu::print_fps_button(Font font)
{
    int current_max = _raylib->getMaxFps();
    std::string current_max_fps = std::to_string(current_max);

    _raylib->drawRectangle({_buttons_option[current_max_fps]->getRectangle().x, _buttons_option[current_max_fps]->getRectangle().y}, {_buttons_option[current_max_fps]->getRectangle().width, _buttons_option[current_max_fps]->getRectangle().height}, PURPLE);
    _raylib->drawText(_buttons_option[current_max_fps]->getPosition(), _buttons_option[current_max_fps]->getText(), WHITE, font, 50);
}

void Menu::reset()
{
    return;
}

void Menu::NotDoneYet()
{
    Font font = _raylib->loadFont("font_gamer");

    while (!_raylib->isWindowClosed()) {
        _cursor->setPosition(_raylib->getMousePosition());
        _raylib->StartAndEndDrawing(true);
        ClearBackground(BLACK);
        _raylib->drawFPS({10, 10});
        _raylib->drawText({WIDTH / 2, HEIGHT / 2}, "Not done yet", RAYWHITE, font, 50);
        _raylib->drawText(_buttons["back"]->getPosition(), _buttons["back"]->getText(), RED, font, 50);
        _raylib->drawTextureRectangle(_cursor->getPosition(), _rect_cursor, _cursor->getColor(), _cursor->getTexture());
        _raylib->StartAndEndDrawing(false);
        if (_raylib->isMousePressed())
        {
            if (_buttons["back"]->isClicked(_raylib->getMousePosition()))
                break;
        }
    }
    if (font.glyphCount > 0)
        UnloadFont(font);
}

void Menu::print_help_button(Font font)
{
    for (auto &it : _buttons_help)
    {
        _raylib->drawRectangle({it.second->getRectangle().x, it.second->getRectangle().y}, {it.second->getRectangle().width, it.second->getRectangle().height}, WHITE);
        _raylib->drawText(it.second->getPosition(), it.second->getText(), BLACK, font, 50);
        if (_raylib->getMousePosition().first >= it.second->getPosition().first && _raylib->getMousePosition().first <= it.second->getPosition().first + it.second->getSize().first &&
            _raylib->getMousePosition().second >= it.second->getPosition().second && _raylib->getMousePosition().second <= it.second->getPosition().second + it.second->getSize().second)
        {
            _raylib->drawRectangle({it.second->getRectangle().x, it.second->getRectangle().y}, {it.second->getRectangle().width, it.second->getRectangle().height}, GREEN);
            _raylib->drawText(it.second->getPosition(), it.second->getText(), WHITE, font, 50);
        }
    }
}

void Menu::helpMenu()
{
    Font font = _raylib->loadFont("Welcome to the help menu");
    Texture2D background = _raylib->LoadImageToTexture("background_help");

    while (!WindowShouldClose())
    {
        _raylib->updateMusic();
        _cursor->setPosition(_raylib->getMousePosition());
        _raylib->StartAndEndDrawing(true);
        ClearBackground(PURPLE);
        _raylib->drawTexture({0, 0}, background, WHITE);
        _raylib->drawFPS({10, 10});
        print_help_button(font);
        _raylib->drawTextureRectangle(_cursor->getPosition(), _rect_cursor, _cursor->getColor(), _cursor->getTexture());
        _raylib->StartAndEndDrawing(false);
        if (_raylib->isMousePressed())
            if (_buttons_help["back"]->isClicked(_raylib->getMousePosition()))
                break;
    }
    if (font.glyphCount > 0)
        UnloadFont(font);
    if (background.id > 0)
        UnloadTexture(background);
}

void Menu::quit()
{
    _raylib->closeWindow();
    _raylib->setWindowOpen(false);
}

void Menu::launchGame()
{
    Map map(31, 21, _raylib);

    _menu = false;
    map.run();
    return;
}

void Menu::print_option_button(Font font)
{
    for (auto &it : _buttons_option)
    {
        _raylib->drawRectangle({it.second->getRectangle().x, it.second->getRectangle().y}, {it.second->getRectangle().width, it.second->getRectangle().height}, WHITE);
        print_fps_button(font);
        _raylib->drawText(it.second->getPosition(), it.second->getText(), BLACK, font, 50);
        if (_raylib->getMousePosition().first >= it.second->getPosition().first && _raylib->getMousePosition().first <= it.second->getPosition().first + it.second->getSize().first &&
            _raylib->getMousePosition().second >= it.second->getPosition().second && _raylib->getMousePosition().second <= it.second->getPosition().second + it.second->getSize().second)
        {
            _raylib->drawRectangle({it.second->getRectangle().x, it.second->getRectangle().y}, {it.second->getRectangle().width, it.second->getRectangle().height}, GREEN);
            _raylib->drawText(it.second->getPosition(), it.second->getText(), WHITE, font, 50);
        }
    }
}

std::string Menu::remove_useless(std::string str)
{
    std::string::size_type pos = str.find('.');
    if (pos != std::string::npos)
        str.erase(pos + 1);
    str.erase(pos);
    return str;
}

void Menu::draw_menu_option(Font font, Texture2D background, Font music)
{
    _raylib->StartAndEndDrawing(true);
    ClearBackground(BLACK);
    _raylib->drawTextureRectangle(std::make_pair(0, 0), Rectangle{0, 0, WIDTH, HEIGHT}, WHITE, background);
    _raylib->drawFPS({10, 10});
    print_option_button(font);
    _raylib->drawText({500.0f, 300.0f}, "volume :", RAYWHITE, font, 80);
    _raylib->drawText({500.0f, 500.0f}, "FPS :", RAYWHITE, font, 80);
    _raylib->drawText({500.0f, 700.0f}, "Music :", RAYWHITE, font, 80);
    _raylib->drawText({1030.0f, 300.0f}, remove_useless(std::to_string(trunc(_raylib->getVolumeMusic() * 100))), RAYWHITE, font, 80);
    _raylib->draw_list_music({980.0f, 680.0f}, WHITE, music, 50, GREEN);
    _raylib->drawTextureRectangle(_cursor->getPosition(), _rect_cursor, _cursor->getColor(), _cursor->getTexture());
    _raylib->StartAndEndDrawing(false);
}

void Menu::optionMenu()
{
    Font font = _raylib->loadFont("font_gamer");
    Texture2D background = _raylib->LoadImageToTexture("option_background");
    Font music = _raylib->loadFont("font_music");

    while (!_raylib->isWindowClosed())
    {
        _raylib->updateMusic();
        _cursor->setPosition(_raylib->getMousePosition());
        draw_menu_option(font, background, music);
        button_pressed_option(_raylib->getMousePosition());
        if (_raylib->isMousePressed())
            if (_buttons_option["back"]->isClicked(_raylib->getMousePosition()))
                break;
    }
    if (font.glyphCount > 0)
        UnloadFont(font);
    if (background.id > 0)
        UnloadTexture(background);
    if (music.glyphCount > 0)
        UnloadFont(music);
}

void Menu::button_pressed_option(std::pair<float, float> mouse_position)
{
    if (_raylib->isMousePressed())
    {
        for (auto &it : _buttons_option)
            if (it.second->getText().compare("Go back") != 0)
                it.second->isClicked(mouse_position) ? it.second->action() : reset();
    }
}