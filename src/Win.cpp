/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** Win
*/

#include "../include/Win.hpp"
#include "../include/Map.hpp"
#include "../include/Menu.hpp"

Win::Win(Raylib *raylib)
{
    _raylib = raylib;
    _background = _raylib->LoadImageToTexture("background_win");
    _model = LoadModel("assets/player.iqm");
    _camera = Camera3D{Vector3{-5, 8, -5}, Vector3{0, 2, 0}, Vector3{0, 2, 0}, 45, CAMERA_PERSPECTIVE};
    _animsCount = 1;
    _anims = LoadModelAnimations("assets/player.iqm", &_animsCount);
    float cam_radius = 10;
	float cam_angle = 1.57;
    _camera.position.x = cam_radius * cos(cam_angle);
    _camera.position.z = cam_radius * sin(cam_angle);
    _font = _raylib->loadFont("font_gamer");
    _buttons.insert(std::make_pair("quit", std::unique_ptr<Button>(new Button({350.0f, 850.0f}, {200.0f, 90.0f}, " Quit ", [&](){end = true;}))));
    _buttons.insert(std::make_pair("restart", std::unique_ptr<Button>(new Button({850.0f, 850.0f}, {290.0f, 90.0f}, " Restart ", [&](){restart(), end = true;}))));
    _buttons.insert(std::make_pair("menu", std::unique_ptr<Button>(new Button({1350.0f, 850.0f}, {200.0f, 90.0f}, " Menu ", [&](){goMenu(), end = true;}))));
}

Win::~Win()
{
    for (unsigned int i = 0; i < _animsCount; i++) UnloadModelAnimation(_anims[i]);
    if (_anims != NULL)
        RL_FREE(_anims);
    if (_background.id != 0)
        UnloadTexture(_background);
    if (_model.bones != 0)
        UnloadModel(_model);
    if (_font.baseSize != 0)
        UnloadFont(_font);
}

void Win::screenWin(const std::string &color_of_winner, const std::string &name_of_winner)
{
    Texture2D texture = LoadTexture(color_of_winner.c_str());
    SetMaterialTexture(&_model.materials[0], MATERIAL_MAP_DIFFUSE, texture);
    int animFrameCounter = 0;

    SetExitKey(KEY_ESCAPE);
    ShowCursor();
    while (!_raylib->isWindowClosed()) {
        UpdateModelAnimation(_model, _anims[5], animFrameCounter);
        animFrameCounter++;
        if (animFrameCounter >= _anims[5].frameCount)
            animFrameCounter = 0;
        _raylib->StartAndEndDrawing(true);
        ClearBackground(RAYWHITE);
        _raylib->drawTexture({0, 0}, _background, WHITE);
        _raylib->drawText({700, 400}, "Winner is : ", WHITE, _font, 80);
        _raylib->drawText({1100, 400}, name_of_winner, GREEN, _font, 80);
        BeginMode3D(_camera);
        DrawModelEx(_model, Vector3{0, 0, 0}, Vector3{0, 500, 0}, 90, Vector3{1, 1, 1}, WHITE);
        EndMode3D();
        draw_buttons(_font);
        _raylib->StartAndEndDrawing(false);
        action_buttons();
        if (end)
            break;
    }
    if (texture.id != 0)
        UnloadTexture(texture);
}

void Win::draw_buttons(Font font)
{
    for (auto &it : _buttons) {
        if (_raylib->getMousePosition().first >= it.second->getPosition().first && _raylib->getMousePosition().first <= it.second->getPosition().first + it.second->getSize().first &&
            _raylib->getMousePosition().second >= it.second->getPosition().second && _raylib->getMousePosition().second <= it.second->getPosition().second + it.second->getSize().second)         {
                _raylib->drawRectangle({it.second->getRectangle().x, it.second->getRectangle().y}, {it.second->getRectangle().width, it.second->getRectangle().height}, RED);
        } else
            _raylib->drawRectangle({it.second->getRectangle().x, it.second->getRectangle().y}, {it.second->getRectangle().width, it.second->getRectangle().height}, BLACK);
        _raylib->drawText(it.second->getPosition(), it.second->getText(), WHITE, font, 80);
    }
}

void Win::action_buttons()
{
    if (_raylib->isMousePressed())
        for (auto &it : _buttons)
            it.second->isClicked(_raylib->getMousePosition()) ? it.second->action() : reset();
}

void Win::reset()
{
    return;
}

void Win::restart()
{
    Map map(30, 20, _raylib);

    map.setNeedLoad(false);
    map.run();
}

void Win::goMenu()
{
    Menu menu(_raylib);
    Texture2D background = _raylib->LoadImageToTexture("background_menu");

    menu.LaunchMenu(background);
}