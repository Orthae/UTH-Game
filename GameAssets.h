#pragma once

#include <vector>
#include "Map.h"
#include "Tile.h"
#include "UI.h"

class GameAssets {
private:
    static GameAssets *instance;
    std::vector<Map> gameMaps;
    std::vector<UI> gameUIs;
    std::vector<Tile> gameTiles;
    std::vector<unsigned long> colorPallete;

    GameAssets();

    void loadColorPalette();

    void loadGameTiles();

    bool checkCollision(int i);

    void loadGameMaps();

    void loadUI();

public:
    std::vector<UI> *getGameUI();

    static GameAssets *getInstance();

    std::vector<Map> *getGameMaps();

    std::vector<unsigned long> *getColorPallete();

    std::vector<Tile> *getGameTiles();

    void initialize();

    ~GameAssets();
};

