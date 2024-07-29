/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** Raylib
*/

#include "../include/Raylib.hpp"
#include "../include/Exception.hpp"

Raylib::Raylib(int height, int width, std::string const &title)
{
    InitWindow(height, width, title.c_str());
    ToggleFullscreen();
    MaximizeWindow();
    SetTargetFPS(60);
    _current_music_listening = _list_music.front();
    _max_fps = 60;
    windowOpen = true;
    _volume = 0.5f;
    InitAudioDevice();
    try {
        if (!IsAudioDeviceReady())
            throw Exception("Couldn't initialize audio device");
    } catch (Exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

Raylib::~Raylib()
{
    if (IsMusicStreamPlaying(_current_music))
        UnloadMusicStream(_current_music);
    if (IsAudioDeviceReady())
        CloseAudioDevice();
    if(WindowShouldClose() && windowOpen)
        CloseWindow();
}

Texture2D Raylib::LoadImageToTexture(std::string const &path)
{
    Image image;
    int width = map_resize_image[path][0];
    int height = map_resize_image[path][1];

    image = LoadImage(map_load_file[path].c_str());
    try {
        if (image.data == nullptr)
            throw Exception("Error: Image is null");
    } catch (Exception &e) {
        std::cerr << e.what() << std::endl;
    }
    if (width == 0)
        width = image.width;
    if (height == 0)
        height = image.height;
    ImageResize(&image, width, height);
    Texture2D texture = LoadTextureFromImage(image);
    try {
        if (texture.id == 0)
            throw Exception("Error: Texture is null");
    } catch (Exception &e) {
        std::cerr << e.what() << std::endl;
    }
    UnloadImage(image);
    return texture;
}

void Raylib::setMusic(std::string const &path)
{
    _current_music = LoadMusicStream(map_load_file[path].c_str());
    try {
        if (_current_music.ctxData == nullptr)
            throw Exception("Error: Music is null");
    } catch (Exception &e) {
        std::cerr << e.what() << std::endl;
    }
    _current_music.looping = true;
    SetMusicVolume(_current_music, _volume);
    PlayMusicStream(_current_music);
}

Music Raylib::getMusic()
{
    return _current_music;
}

void Raylib::checkIfMusicIsPlaying()
{
    if (!IsMusicStreamPlaying(_current_music))
        PlayMusicStream(_current_music);
}

void Raylib::pauseOrResumeMusic()
{
    if (IsMusicStreamPlaying(_current_music))
        PauseMusicStream(_current_music);
    else
        PlayMusicStream(_current_music);
}

void Raylib::setVolumeMusic(float number)
{
    SetMusicVolume(_current_music, number);
}

Font Raylib::loadFont(std::string const &path)
{
    Font font = LoadFont(map_load_file[path].c_str());
    try {
        if (font.baseSize <= 0)
            throw Exception("Error: Font is null");
    } catch (Exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return font;
}

void Raylib::StartAndEndDrawing(bool start)
{
    start == true ? BeginDrawing() : EndDrawing();
}

void Raylib::drawRectangle(std::pair<int, int> position, std::pair<int, int> size, Color color)
{
    DrawRectangle(position.first, position.second, size.first, size.second, color);
}

void Raylib::drawTextureRectangle(std::pair<float, float> position, Rectangle rectangle, Color color, Texture2D texture)
{
    DrawTextureRec(texture, rectangle, {position.first, position.second}, color);
}

void Raylib::drawFPS(std::pair<int, int> position)
{
    DrawFPS(position.first, position.second);
}

void Raylib::drawText(std::pair<float, float> position, std::string const &text, Color color, Font font, float fontSize, float spacing)
{
    DrawTextEx(font, text.c_str(), {position.first, position.second}, fontSize, spacing, color);
}

void Raylib::drawTexture(std::pair<int, int> position, Texture2D texture, Color color)
{
    DrawTexture(texture, position.first, position.second, color);
}

bool Raylib::isWindowClosed(void)
{
    return WindowShouldClose();
}

float Raylib::getFrameTime(void)
{
    return GetFrameTime();
}

bool Raylib::keyPressed(int key)
{
    return IsKeyPressed(key);
}

ry::v3d::Camera &Raylib::getCamera(void) noexcept
{
    return _camera;
}

void Raylib::cameraControl(bool able)
{
    return able ? _camera.begin() : _camera.end();
}

std::pair<float, float> Raylib::getMousePosition(void)
{
    return {GetMouseX(), GetMouseY()};
}

bool Raylib::isMousePressed()
{
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

void Raylib::closeWindow()
{
    CloseWindow();
}

void Raylib::setWindowOpen(bool open)
{
    windowOpen = open;
}

float Raylib::getVolumeMusic()
{
    return _volume;
}

void Raylib::lessVolume()
{
    if (_volume > 0.1f)
        _volume -= 0.1f;
    setVolumeMusic(_volume);
}

void Raylib::addVolume()
{
    if (_volume < 1.0f)
        _volume += 0.1f;
    setVolumeMusic(_volume);
}

std::pair<int, int> Raylib::getWindowSize()
{
    return {GetScreenWidth(), GetScreenHeight()};
}

void Raylib::actionMusic()
{
    if (IsMusicStreamPlaying(_current_music)) {
        if (getVolumeMusic() != 0) {
            _volume = 0.0f;
            setVolumeMusic(_volume);
        } else {
            _volume = 1.0f;
            setVolumeMusic(_volume);
        }
    }
}

int Raylib::getMaxFps()
{
    return _max_fps;
}

void Raylib::setFps(int new_fps)
{
    SetTargetFPS(new_fps);
    _max_fps = new_fps;
}

void Raylib::changeCurrentMusicLeft()
{
    if (_vector_music == 0)
        _vector_music = _list_music.size() - 1;
    else
        _vector_music -= 1;
    _current_music_listening = _list_music[_vector_music];
    if (_current_music.ctxData != nullptr)
        UnloadMusicStream(_current_music);
    setMusic(_current_music_listening.first);
}

void Raylib::changeCurrentMusicRight()
{
    if (_vector_music == _list_music.size() - 1)
        _vector_music = 0;
    else
        _vector_music += 1;
    _current_music_listening = _list_music[_vector_music];
    if (_current_music.ctxData != nullptr)
        UnloadMusicStream(_current_music);
    setMusic(_current_music_listening.first);
}

void Raylib::updateMusic()
{
    if (IsMusicStreamPlaying(_current_music))
        UpdateMusicStream(_current_music);
}

void Raylib::draw_list_music(std::pair<float, float> position, Color color, Font font, float fontSize, Color special)
{
    for (auto &i : _list_music) {
        if (i.second == _current_music_listening.second)
            drawText(position, i.second, special, font, fontSize, 0.0f);
        else
            drawText(position, i.second, color, font, fontSize, 0.0f);
        position.second += 50;
    }
}

void Raylib::drawRectangleOutline(std::pair<int, int> position, std::pair<int, int> size, Color color)
{
    DrawRectangleLines(position.first, position.second, size.first, size.second, color);
}

void Raylib::drawRectangleOutlineThick(Rectangle rect, Color color, int tickness)
{
    DrawRectangleLinesEx(rect, tickness, color);
}