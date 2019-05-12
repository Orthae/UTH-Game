#pragma once

#include<vector>

class Tile {
private:
    bool isWalkable;
    unsigned long sprite[16][16];
public:
    unsigned long getSpritePixel(int const x, int const y) const;

    bool isTileWalkable() const;

    Tile(std::vector<std::vector<int>> const rawTile, bool const isWalkable);

    ~Tile();
};

