#include "pch.h"
#include "Enemy.h"
#include "GameData.h"
#include <chrono>
#include <iostream>

bool Enemy::collisionWithEnemies(Direction const moveDirection) const {
    int x, y;
    for (Enemy &enemy : *GameData::getInstance()->getEnemyList()) {
		Coords const * const objectCoords = enemy.getCurrentCoords();
        switch (moveDirection) {
            case NORTH:
                x = this->getCurrentCoords()->getX();
                y = this->getCurrentCoords()->getY() - 1;
                break;
            case SOUTH:
                x = this->getCurrentCoords()->getX();
                y = this->getCurrentCoords()->getY() + 1;
                break;
            case WEST:
                x = this->getCurrentCoords()->getX() - 1;
                y = this->getCurrentCoords()->getY();
                break;
            case EAST:
                x = this->getCurrentCoords()->getX() + 1;
                y = this->getCurrentCoords()->getY();
                break;
        }
        if (x == objectCoords->getX() && y == objectCoords->getY()) {
            return true;
        }
    }
    return false;
}

bool Enemy::handle() const {
    unsigned long seed = (unsigned long) std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
    std::srand(seed);
    switch (std::rand() % 4) {
        case 0:
            if (!collisionWithEnemies(SOUTH))
                return moveDown();
        case 1:
            if (!collisionWithEnemies(NORTH))
                return moveUp();
        case 2:
            if (!collisionWithEnemies(WEST))
                return moveLeft();
        case 3:
            if (!collisionWithEnemies(EAST))
                return moveRight();
    }
    return false;
}

Enemy::Enemy(Tile const * const objectSprite, int const x, int const y) : GameObject(objectSprite, x, y) {
}

Enemy::~Enemy()
= default;
