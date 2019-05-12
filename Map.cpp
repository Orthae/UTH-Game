#include "pch.h"
#include "Map.h"
#include "GameAssets.h"
#include <vector>
#include "GameData.h"
#include <iostream>

Tile *Map::getTile(int const mapX, int const mapY) const {
    return mapTiles[mapX][mapY];
}

Map::Map(std::vector<std::vector<int>> const rawMap) {
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 25; j++) {
            mapTiles[i][j] = &GameAssets::getInstance()->getGameTiles()->at(rawMap[i][j]);
        }
    }
}

Map::~Map()
= default;
