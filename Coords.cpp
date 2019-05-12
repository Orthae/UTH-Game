#include "pch.h"
#include "Coords.h"
#include <iostream>

bool Coords::operator==(Coords const * const p ) const {
    if (this->x == p->x && this->y == p->y) {
        return true;
    } else {
        return false;
    }
}

int Coords::getX() const {
    return x;
}

int Coords::getY() const {
    return y;
}

bool Coords::setX(int const x) {
    if (x >= 0 && x <= 24) {
        this->x = x;
        return true;
    } else {
        return false;
    }
}

bool Coords::setY(int const y) {
    if (y >= 0 && y <= 24) {
        this->y = y;
        return true;
    } else {
        return false;
    }
}

Coords::Coords(int const x, int const y) {
    setX(x);
    setY(y);
}

Coords::Coords()
= default;

Coords::~Coords()
= default;
