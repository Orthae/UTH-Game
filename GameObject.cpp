#include "pch.h"
#include "GameObject.h"
#include "GameData.h"

Coords * GameObject::getCurrentCoords() const {
	return current;
}

Coords * GameObject::getLastCoords() const {
    return last;
}

Tile const *GameObject::getSprite() const {
    return sprite;
}

bool GameObject::moveUp() const {
    int y = getCurrentCoords()->getY();
    if (y > 0) {
        if (GameData::getInstance()->getCurrentMap()->getTile(y - 1, getCurrentCoords()->getX())->isTileWalkable()) {
            getLastCoords()->setY(y);
            getLastCoords()->setX(getCurrentCoords()->getX());
            getCurrentCoords()->setY(y - 1);
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool GameObject::moveDown() const {
    int y = getCurrentCoords()->getY();
    if (y < 24) {
        if (GameData::getInstance()->getCurrentMap()->getTile(y + 1, getCurrentCoords()->getX())->isTileWalkable()) {
            getLastCoords()->setY(y);
            getLastCoords()->setX(getCurrentCoords()->getX());
            getCurrentCoords()->setY(y + 1);
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool GameObject::moveLeft() const {
    int x = getCurrentCoords()->getX();
    if (x > 0) {
        if (GameData::getInstance()->getCurrentMap()->getTile(getCurrentCoords()->getY(), x - 1)->isTileWalkable()) {
            getLastCoords()->setX(x);
            getLastCoords()->setY(getCurrentCoords()->getY());
            getCurrentCoords()->setX(x - 1);
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool GameObject::moveRight() const {
    int x = getCurrentCoords()->getX();
    if (x < 24) {
        if (GameData::getInstance()->getCurrentMap()->getTile(getCurrentCoords()->getY(), x + 1)->isTileWalkable()) {
            getLastCoords()->setX(x);
            getLastCoords()->setY(getCurrentCoords()->getY());
            getCurrentCoords()->setX(x + 1);
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

GameObject::GameObject(Tile const * const playerSprite, int const x , int const y) {
    this->sprite = playerSprite;
    this->current = new Coords(x, y);
    this->last = new Coords(x, y);
}

GameObject::~GameObject()
= default;
