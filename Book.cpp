#include "pch.h"
#include "Book.h"

int Book::getPoints() const {
    return points;
}

Book::Book(Tile const * const objectSprite, int const points, int const x, int const y) : GameObject(objectSprite, x, y) {
    this->points = points;
}

bool Book::handle() const
{
	// TODO ??
	return false;
}

Book::~Book()
= default;
