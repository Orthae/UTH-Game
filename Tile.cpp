#include "pch.h"
#include "Tile.h"
#include "GameData.h"
#include "GameAssets.h"

unsigned long Tile::getSpritePixel(int const x, int const y) const {
    return sprite[x][y];
}

bool Tile::isTileWalkable() const {
    return isWalkable;
}

Tile::Tile(std::vector<std::vector<int>> const rawTile, bool const isWalkable) {
    for (int i = 0; i < 16; i++)
        for (int j = 0; j < 16; j++) {
            sprite[i][j] = GameAssets::getInstance()->getColorPallete()->at(rawTile[i][j]);
        }
    this->isWalkable = isWalkable;
}

Tile::~Tile()
= default;
