#pragma once

#include "GameObject.h"

class Player : public GameObject {
private:
    unsigned int points;
    unsigned int gamePoints;
    bool secondPlayer;
    bool isAlive;
public:
    void setIsAlive(bool const isAlive);

    bool getIsAlive() const;

    void addGamePoints();

    unsigned int getGamePoints() const;

    void setSecondPlayer(bool const isSecondPlayer);

    virtual bool handle() const;

    void setCoords(Coords const * const mapCoords);

    unsigned int getPoints() const;

    void setPoints(unsigned int const points);

    Player(Tile const * const objectSprite, int const x, int const y, bool const isSecondPlayer);

    ~Player();
};

