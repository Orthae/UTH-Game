#pragma once

#include "GameObject.h"
#include "Tile.h"

enum Direction {
    SOUTH, NORTH, WEST, EAST
};

class Enemy : public GameObject {
public:
    bool collisionWithEnemies(Direction const moveDirection) const;

    bool handle() const;

    Enemy(Tile const * const objectSprite, int const x, int const y);

    ~Enemy();
};

