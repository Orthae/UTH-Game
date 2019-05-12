#pragma once

#include "Tile.h"
#include "Coords.h"

class GameObject {
private:
    Coords * current;
    Coords * last;
    Tile const * sprite;
public:
	virtual bool handle() const abstract;

    Coords * getCurrentCoords() const;

    Coords * getLastCoords() const;

    Tile const * getSprite() const;

    bool moveUp() const;

    bool moveDown() const;

    bool moveLeft() const;

    bool moveRight() const;

    GameObject(Tile const * const playerSprite, int const x, int const y);


    ~GameObject();
};

