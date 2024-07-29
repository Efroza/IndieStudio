cmake_minimum_required(VERSION 3.17)

project(bomberman)

set(CMAKE_CXX_STANDARD 11)

include("cmake/Findraylib.cmake")


set(SRCS
    ./src/raylib/Shape.cpp
    ./src/raylib/Rectangle.cpp
    ./src/raylib/Circle.cpp
    ./src/raylib/Sprite.cpp
    ./src/raylib/Scopeloop.cpp
    ./src/raylib/Camera.cpp
    ./src/ACollision.cpp
    ./src/main.cpp
    ./src/Map.cpp
    ./src/Bomb.cpp
    ./src/Menu.cpp
    ./src/Wall.cpp
    ./src/Raylib.cpp
    ./src/Animation.cpp
    ./src/Button.cpp
    ./src/Character.cpp
    ./src/IA.cpp
    ./src/FireUpBonus.cpp
    ./src/SpeedBonus.cpp
    ./src/WallPassBonus.cpp
    ./src/BombBonus.cpp
    ./src/Exception.cpp
    ./src/SubMenu.cpp
    ./src/Win.cpp
    ./src/Screen.cpp
    ./src/Pause.cpp
    ./src/Choose.cpp
    )
    
set(HEADERS
    ./include/global.h
    ./include/raylib/Shape.hpp
    ./include/raylib/Circle.hpp
    ./include/raylib/Rectangle.hpp
    ./include/raylib/Sprite.hpp
    ./include/raylib/Scopeloop.hpp
    ./include/raylib/Camera.hpp
    ./include/Bomb.hpp
    ./include/IBonus.hpp
    ./include/Button.hpp
    ./include/ICollision.hpp
    ./include/ACollision.hpp
    ./include/Map.hpp
    ./include/Menu.hpp
    ./include/Wall.hpp
    ./include/Character.hpp
    ./include/Raylib.hpp
    ./include/Animation.hpp
    ./include/IA.hpp
    ./include/Win.hpp
    ./include/Screen.hpp
    ./include/Pause.hpp
    ./include/Choose.hpp
    )

add_executable(${PROJECT_NAME} ${SRCS} ${HEADERS})
target_link_libraries(${PROJECT_NAME} raylib)