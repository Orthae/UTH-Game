#pragma once

#include "Tile.h"

class UI {
    Tile * guiTiles[24];
public:
    Tile * getTile(int const index) const;

    UI(std::vector<int> const rawUI);

    ~UI();
};

