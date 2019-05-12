#include "pch.h"
#include "UI.h"
#include "GameAssets.h"

Tile *UI::getTile(int const index) const {
    return guiTiles[index];
}

UI::UI(std::vector<int> const rawUI) {
    for (int i = 0; i < 24; i++) {
        guiTiles[i] = &GameAssets::getInstance()->getGameTiles()->at(rawUI[i]);
    }
}


UI::~UI()
= default;
