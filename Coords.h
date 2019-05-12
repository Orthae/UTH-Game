#pragma once

class Coords {
private:
    int x;
    int y;
public:
    int getX() const;

    int getY() const;

    bool operator==(Coords const * const p) const;

    bool setX(int const x);

    bool setY(int const y);

    Coords(int const x, int const y);

    Coords();

    ~Coords();
};
