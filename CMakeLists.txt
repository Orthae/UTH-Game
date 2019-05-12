cmake_minimum_required(VERSION 3.12)
project(UTH_Game)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(UTH_Game
        Book.cpp
        Book.h
        Coords.cpp
        Coords.h
        Enemy.cpp
        Enemy.h
        Game.cpp
        Game.h
        GameAssets.cpp
        GameAssets.h
        GameData.cpp
        GameData.h
        GameObject.cpp
        GameObject.h
        Main.cpp
        Main.h
        Map.cpp
        Map.h
        pch.cpp
        pch.h
        Player.cpp
        Player.h
        RenderEngine.cpp
        RenderEngine.h
        Tile.cpp
        Tile.h
        UI.cpp
        UI.h)
