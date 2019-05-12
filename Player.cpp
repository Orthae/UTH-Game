#include "pch.h"
#include "Player.h"
#include <Windows.h>
#include <iostream>


unsigned int Player::getPoints() const {
    return points;
}

void Player::setPoints(unsigned int const points) {
    this->points = points;
}

void Player::setIsAlive(bool const isAlive) {
    this->isAlive = isAlive;
}

bool Player::getIsAlive() const {
    return isAlive;
}

void Player::addGamePoints() {
    gamePoints++;
}

unsigned int Player::getGamePoints() const {
    return gamePoints;
}

void Player::setSecondPlayer(bool const isSecondPlayer) {
    secondPlayer = isSecondPlayer;
}

void Player::setCoords(Coords const * const mapCoords) {
    getLastCoords()->setX(mapCoords->getX());
    getLastCoords()->setY(mapCoords->getY());
    getCurrentCoords()->setX(mapCoords->getX());
    getCurrentCoords()->setY(mapCoords->getY());
}

bool Player::handle() const {
    if (isAlive) {
        if (secondPlayer) {
            if (GetKeyState(0x57) & 0x8000)
                return this->moveUp();
            if (GetKeyState(0x53) & 0x8000)
                return this->moveDown();
            if (GetKeyState(0x41) & 0x8000)
                return this->moveLeft();
            if (GetKeyState(0x44) & 0x8000)
                return this->moveRight();
        } else {
            if (GetKeyState(0x26) & 0x8000)
                return this->moveUp();
            if (GetKeyState(0x28) & 0x8000)
                return this->moveDown();
            if (GetKeyState(0x25) & 0x8000)
                return this->moveLeft();
            if (GetKeyState(0x27) & 0x8000)
                return this->moveRight();
        }

    }
    return false;
}

Player::Player(Tile const * const objectSprite, int const x, int const y, bool const isSecondPlayer) : GameObject(objectSprite, x, y) {
    points = 0;
    secondPlayer = isSecondPlayer;
    gamePoints = 0;
    isAlive = true;
}

Player::~Player()
= default;
