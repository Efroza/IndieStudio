/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** Pause
*/

#include "../include/Pause.hpp"
#include <string>

Pause::Pause(Raylib *raylib, std::function<void(std::string &)> loadGame, std::function<void()> saveGame, std::function<void(bool)> draw) :
    _raylib(raylib),
    _loadGame(loadGame),
    _saveGame(saveGame),
    _draw(draw)
{
    fillButtonPause();
    _background = _raylib->LoadImageToTexture("pause_background");
    _font = _raylib->loadFont("font_gamer");
    _music = _raylib->loadFont("font_music");
    _background_load = _raylib->LoadImageToTexture("background_load");
}

Pause::~Pause()
{
    if (_font.glyphCount > 0)
        UnloadFont(_font);
    if (_background.id > 0)
        UnloadTexture(_background);
    if (_music.glyphCount > 0)
        UnloadFont(_music);
}

bool Pause::beforeGame()
{
    float height = 100.0f;

    ShowCursor();
    while (!_raylib->isWindowClosed()) {
        _raylib->updateMusic();
        _raylib->StartAndEndDrawing(true);
        ClearBackground(WHITE);
        printButtonsBefore(_font);
        _raylib->drawFPS({10, 10});
        _raylib->StartAndEndDrawing(false);
        actionButtonBefore();
        if (_done)
            break;
    }
    HideCursor();
    return _new_game;
}

void Pause::printButtonsBefore(Font font)
{
    _raylib->drawTexture({0, 0}, _background_load, WHITE);
    _raylib->drawRectangle({1020.0f, 150.0f}, {400.0f, 900.0f}, BLACK);
    _raylib->drawRectangleOutlineThick({1020.0f, 150.0f, 400.0f, 900.0f}, WHITE, 7);
    _raylib->drawText({1070.0f, 180.0f}, "List save :", RED, _music, 70);
    _raylib->drawRectangle({500.0f, 420.0f}, {400.0f, 200.0f}, BLACK);
    _raylib->drawRectangleOutlineThick({500.0f, 420.0f, 400.0f, 200.0f}, WHITE, 7);
    _raylib->drawText({630.0f, 430.0f}, "New :", RED, _music, 70);
    for (auto &it : _buttons_select) {
        _raylib->drawRectangle({it.second->getRectangle().x, it.second->getRectangle().y},
                {it.second->getRectangle().width, it.second->getRectangle().height}, BLACK);
        if (_raylib->getMousePosition().first >= it.second->getPosition().first && _raylib->getMousePosition().first <= it.second->getPosition().first + it.second->getSize().first &&
            _raylib->getMousePosition().second >= it.second->getPosition().second && _raylib->getMousePosition().second <= it.second->getPosition().second + it.second->getSize().second)
            _raylib->drawText(it.second->getPosition(), it.second->getText(), ORANGE, _font, 80);
        else
            _raylib->drawText(it.second->getPosition(), it.second->getText(), RED, _font, 70);
    }
}

void Pause::actionButtonBefore()
{
    std::string file;

    if (_raylib->isMousePressed()) {
        for (auto &it : _buttons_select) {
            if (it.second->isClicked(_raylib->getMousePosition())) {
                it.second->action();
                _done = true;
                if (it.first.find(".txt") != std::string::npos) {
                    file = it.first;
                    _loadGame(file);
                    file.clear();
                }
                break;
            }
        }
    }
}

void Pause::printButtonsPause(Font font)
{
    for (auto &it : _buttons) {
        if (it.first.find(".txt") != std::string::npos && !_load_save)
            continue;
        _raylib->drawRectangle({it.second->getRectangle().x, it.second->getRectangle().y},
                {it.second->getRectangle().width, it.second->getRectangle().height}, WHITE);
        if (_raylib->getMousePosition().first >= it.second->getPosition().first && _raylib->getMousePosition().first <= it.second->getPosition().first + it.second->getSize().first &&
            _raylib->getMousePosition().second >= it.second->getPosition().second && _raylib->getMousePosition().second <= it.second->getPosition().second + it.second->getSize().second)
            _raylib->drawText(it.second->getPosition(), it.second->getText(), ORANGE, font, 60);
        else
            _raylib->drawText(it.second->getPosition(), it.second->getText(), RED, font, 50);
    }
}

void Pause::actionButton()
{
    std::string file;

    for (auto &it : _buttons) {
        if (it.second->isClicked(_raylib->getMousePosition())) {
            if (it.first.find(".txt") != std::string::npos) {
                file = it.first;
                _loadGame(file);
            } else
                it.second->action();
        }
    }
}

std::string Pause::remove_useless(std::string str)
{
    std::string::size_type pos = str.find('.');
    if (pos != std::string::npos)
        str.erase(pos + 1);
    str.erase(pos);
    return str;
}

bool Pause::screenPause()
{
    ShowCursor();
    SetExitKey(KEY_ESCAPE);
    while (!_raylib->isWindowClosed()) {
        _raylib->updateMusic();
        drawPauseButton(_music, _font, _background);
        if (_raylib->isMousePressed()) {
            if (_buttons["go back"]->isClicked(_raylib->getMousePosition()))
                break;
            actionButton();
        }
        if (_quit)
            break;
    }
    SetExitKey(KEY_EIGHT);
    HideCursor();
    return _quit;
}

void Pause::drawPauseButton(Font music, Font font, Texture2D background)
{
    _raylib->StartAndEndDrawing(true);
    ClearBackground(RAYWHITE);
    _raylib->cameraControl(true);
    _draw(true);
    _raylib->cameraControl(false);
    _raylib->drawTexture({400.0f, 50.0f}, background, WHITE);
    if (_load_save) {
        _raylib->drawRectangle({1450.0f, 50.0f}, {400.0f, 1000.0f}, WHITE);
        _raylib->drawRectangleOutlineThick({1450.0f, 50.0f, 400.0f, 1000.0f}, BLACK, 5);
        _raylib->drawText({1550.0f, 80.0f}, "List save :", RED, music, 50);
    }
    _raylib->drawRectangleOutlineThick({1120.0f, 330.0f, 250.0f, 300.0f}, BLACK, 5);
    _raylib->drawText({1150.0f, 340.0f}, "volume :", RED, music, 50);
    _raylib->drawText({1210.0f, 460.0f}, remove_useless(std::to_string(trunc(_raylib->getVolumeMusic() * 100))), PURPLE, music, 50);
    _raylib->drawRectangleOutlineThick({490.0f, 330.0f, 500.0f, 210.0f}, BLACK, 5);
    _raylib->drawText({580.0f, 340.0f}, "List of music :", RED, music, 50);
    _raylib->draw_list_music({600.0f, 400.0f}, BLACK, music, 40, RED);
    printButtonsPause(font);
    _raylib->StartAndEndDrawing(false);
}

void Pause::fillButtonPause()
{
    std::string save_ = "save_";
    std::string file = "";

    _buttons.insert(std::make_pair<std::string, Button *>("go back", new Button({500.0f, 800.0f}, {200.0f, 60.0f}, "Go back", [&]() {return;})));
    _buttons.insert(std::make_pair<std::string, Button *>("quit", new Button({500.0f, 900.0f}, {232.0f, 60.0f}, "Close Game", [&]() {_quit = true;})));
    _buttons.insert(std::make_pair<std::string, Button *>("save", new Button({1000.0f, 900.0f}, {214.0f, 60.0f}, "Save Game", [&]() {_saveGame();})));
    _buttons.insert(std::make_pair<std::string, Button *>("less", new Button({1200.0f, 550.0f}, {54.0f, 60.0f}, " - ", [&]() {_raylib->lessVolume();})));
    _buttons.insert(std::make_pair<std::string, Button *>("plus", new Button({1200.0f, 380.0f}, {54.0f, 60.0f}, " + ", [&]() {_raylib->addVolume();})));
    _buttons.insert(std::make_pair<std::string, Button *>("left", new Button({500.0f, 440.0f}, {72.0f, 60.0f}, " <- ", [&]() {_raylib->changeCurrentMusicLeft();})));
    _buttons.insert(std::make_pair<std::string, Button *>("right", new Button({900.0f, 440.0f}, {72.0f, 60.0f}, " -> ", [&]() {_raylib->changeCurrentMusicRight();})));
    _buttons.insert(std::make_pair<std::string, Button *>("load", new Button({1000.0f, 800.0f}, {214.0f, 60.0f}, "Load Game", [&]() {_load_save = true;})));
    _buttons_select.insert(std::make_pair<std::string, Button *>("New Game", new Button({560.0f, 500.0f}, {300.0f, 70.0f}, "New Game", [&]() {_new_game = true;})));
    for (int number = 1, height = 160; std::ifstream(save_ + std::to_string(number) + ".txt").good(); number++, height += 80) {
        file = save_ + std::to_string(number) + ".txt";
        _buttons.insert(std::pair<std::string, Button *>(file, new Button({1550.0f, height}, {108.0f, 60.0f}, "Save " + std::to_string(number), [&]() {return;})));
        _buttons_select.insert(std::pair<std::string, Button *>(file, new Button({1150.0f, height + 100}, {188.0f, 70.0f}, "Save " + std::to_string(number), [&]() {return;})));
        file.clear();
    }
}

void Pause::insertButton(std::string name_button, std::pair<float, float> pos, std::pair<float, float> size, std::string name, std::function<void()> funct)
{
    _buttons.insert(std::pair<std::string, Button *>(name_button, new Button(pos, size, name, [&] () {funct();})));
}

float Pause::getHeightLastButton() const noexcept
{
    return (--_buttons.end())->second->getPosition().second + 80;
}

std::string Pause::getFirstLastButton() const noexcept
{
    return (--_buttons.end())->first;
}