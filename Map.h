#pragma once

#include "Tile.h"
#include <vector>
#include "GameObject.h"
#include "Enemy.h"

class Map {
private:
    Tile * mapTiles[25][25];
public:
    Tile * getTile(int const mapX, int const mapY) const;

    Map(std::vector<std::vector<int>> const rawMap);

    ~Map();
};

