/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-melinda.saglam
** File description:
** Raylib
*/

#ifndef RAYLIB_HPP_
#define RAYLIB_HPP_

#include <iostream>
#include <map>
#include <vector>
#include "raylib.h"
#include "raylib/Camera.hpp"

    #define WIDTH 1900
    #define HEIGHT 1080
    #define folder_assets "assets/"

    typedef enum {
        PERSPECTIVE = 0,
        CUSTOM = 0,
        FREE,
        ORBITAL,
        FIRST_PERSON,
        THIRD_PERSON,
    } CAM_STATE;

class Raylib {
    public:
        Raylib(int, int, std::string const &);
        ~Raylib();
        Texture2D LoadImageToTexture(std::string const &);
        void setMusic(std::string const &);
        Music getMusic();
        void checkIfMusicIsPlaying();
        void pauseOrResumeMusic();
        void setVolumeMusic(float);
        float getVolumeMusic();
        void lessVolume();
        void addVolume();
        Font loadFont(std::string const &);
        void StartAndEndDrawing(bool);
        void drawRectangle(std::pair<int, int> position, std::pair<int, int> size, Color color);
        void drawTextureRectangle(std::pair<float, float> position, Rectangle rectangle, Color color, Texture2D texture);
        void drawRectangleOutline(std::pair<int, int> position, std::pair<int, int> size, Color color);
        void drawRectangleOutlineThick(Rectangle, Color, int);
        void drawFPS(std::pair<int, int> position);
        void drawText(std::pair<float, float> position, std::string const &text, Color color, Font font, float fontSize, float spacing = 0.0f);
        void drawTexture(std::pair<int, int> position, Texture2D texture, Color);
        bool isWindowClosed(void);
        float getFrameTime(void);
        bool keyPressed(int);
        void setCamera(const Vector3 &, const Vector3 &, const Vector3 &, float, CAM_STATE);
        ry::v3d::Camera &getCamera(void) noexcept;
        void cameraControl(bool control);
        bool isMousePressed();
        void closeWindow();
        void setWindowOpen(bool);
        std::pair<float, float> getMousePosition(void);
        std::pair<int, int> getWindowSize(void);
        void actionMusic();
        int getMaxFps();
        void setFps(int);
        void changeCurrentMusicLeft();
        void changeCurrentMusicRight();
        void updateMusic();
        void draw_list_music(std::pair<float, float>, Color, Font, float, Color);

    protected:
    private:
        Sound _current_sound;
        ry::v3d::Camera _camera;
        Music _current_music;
        std::map < std::string, std::vector<int>> map_resize_image = {
            {"logo_image", {400, 200}},
            {"character_animation_first", {0, 257}},
            {"bomb_image_animation", {0, 0}},
            {"explosion_menu", {1524, 1524}},
            {"logo_epitech", {0, 0}},
            {"background_menu", {0, 0}},
            {"cursor", {0, 0}},
            {"option_background", {0, 0}},
            {"pause_background", {0, 0}},
            {"background_win", {0, 0}},
            {"background_load", {0, 0}},
            {"background_control", {0, 0}},
            {"background_help", {0, 0}}
        };
        std::map < std::string, std::string> map_load_file{
            {"logo_image", folder_assets + std::string("logo.png")},
            {"font_gamer", folder_assets + std::string("Gamer.ttf")},
            {"font_music", folder_assets + std::string("music.otf")},
            {"background_menu", folder_assets + std::string("background.png")},
            {"character_animation_first", folder_assets + std::string("character_animation.png")},
            {"bomb_image_animation", folder_assets + std::string("bomb.png")},
            {"sound_menu", folder_assets + std::string("awesomeness.wav")},
            {"sound_game", folder_assets + std::string("bomberman_area_1.mp3")},
            {"bomberman_sound", folder_assets + std::string("theme_song_bomberman.mp3")},
            {"explosion_menu", folder_assets + std::string("explosion.png")},
            {"logo_epitech", folder_assets + std::string("logo_epitech.png")},
            {"cursor", folder_assets + std::string("cursor_bomb.png")},
            {"option_background", folder_assets + std::string("purple_option.png")},
            {"pause_background", folder_assets + std::string("background_pause.png")},
            {"background_win", folder_assets + std::string("background_win.png")},
            {"background_load", folder_assets + std::string("background_load.png")},
            {"background_control", folder_assets + std::string("background_control.png")},
            {"background_help", folder_assets + std::string("background_help.png")}
        };
        std::vector<std::pair<std::string, std::string>> _list_music = {
            {"bomberman_sound", "theme_song"},
            {"sound_menu", "awesomeness"},
            {"sound_game", "bomberman_retro"}
        };
        bool windowOpen;
        float _volume;
        int _max_fps;
        std::pair<std::string,std::string> _current_music_listening;
        int _vector_music = 0;

};

#endif /* !RAYLIB_HPP_ */