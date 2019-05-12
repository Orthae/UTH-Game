#pragma once

#include "GameObject.h"

class Book : public GameObject {
private:
    int points;
public:
    int getPoints() const;

    Book(Tile const * const objectSprite, int const points, int const x, int const y);

	virtual bool handle() const;

    ~Book();
};

