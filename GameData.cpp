#include "pch.h"
#include "GameData.h"
#include "GameAssets.h"
#include "Tile.h"
#include <Windows.h>
#include <iostream>
#include <chrono>

GameData *GameData::instance = nullptr;

std::vector<Enemy> *GameData::getEnemyList() {
    return &enemyList;
}

Map *GameData::getCurrentMap() {
    return currentMap;
}

Map * GameData::getLastMap() {
	return lastMap;
}

std::vector<Book> *GameData::getBookList() {
    return &bookList;
}

std::vector<Player> *GameData::getPlayerList() {
    return &playerList;
}

std::vector<UI> *GameData::getUI() {
    return GameAssets::getInstance()->getGameUI();
}

Tile * GameData::getScoreTile(Player * player){
    switch (player->getGamePoints() % 4) {
        case 0:
            return &GameAssets::getInstance()->getGameTiles()->at(14);
        case 1:
            return &GameAssets::getInstance()->getGameTiles()->at(15);
        case 2:
            return &GameAssets::getInstance()->getGameTiles()->at(16);
        case 3:
            return &GameAssets::getInstance()->getGameTiles()->at(17);
    }
    return &GameAssets::getInstance()->getGameTiles()->at(18);
}

// Tworzenie obiektow
Coords GameData::getRandomWalkableTile() {
    int x, y;
    do {
        x = std::rand() % 25;
        y = std::rand() % 25;
    } while (!getCurrentMap()->getTile(y, x)->isTileWalkable());
    return Coords(x, y);
}

void GameData::createBook() {
    Coords coords = getRandomWalkableTile();
    int points = (std::rand() % 3) + 1;
    Tile *sprite;
    switch (points) {
        case 1:
            sprite = &GameAssets::getInstance()->getGameTiles()->at(4);
            break;
        case 2:
            sprite = &GameAssets::getInstance()->getGameTiles()->at(11);
            break;
        case 3:
            sprite = &GameAssets::getInstance()->getGameTiles()->at(12);
            break;
        default:
            exit(0);
    }
    bookList.insert(bookList.end(), Book(sprite, points, coords.getX(), coords.getY()));
}

void GameData::createPlayer() {
    Coords coords = getRandomWalkableTile();
    if (playerList.empty()) {
        playerList.insert(playerList.end(),
                          Player(&GameAssets::getInstance()->getGameTiles()->at(2), coords.getX(), coords.getY(),
                                 false));
        playerList.insert(playerList.end(), Player(&GameAssets::getInstance()->getGameTiles()->at(13), 5, 4, true));
    } else {
        for (auto &player : playerList) {
            Coords walkableTile = getRandomWalkableTile();
            player.setCoords(&walkableTile);
            player.setPoints(0);
            player.setIsAlive(true);

        }
    }
}

void GameData::createEnemy() {
    Coords coords = getRandomWalkableTile();
    enemyList.insert(enemyList.end(),
                     Enemy(&GameAssets::getInstance()->getGameTiles()->at(3), coords.getX(), coords.getY()));
}

// Ustawianie nastepnej mapy
bool GameData::nextMap() {
    static unsigned int i = 0;
    if (i < GameAssets::getInstance()->getGameMaps()->size()) {
		if (currentMap != nullptr) {
			lastMap = currentMap;
		}
		currentMap = &GameAssets::getInstance()->getGameMaps()->at(i);
		i++;
        return true;
    } else {
        return false;
    }
}

void GameData::initialize() {
    currentMap = nullptr;
    lastMap = nullptr;
}

GameData *GameData::getInstance() {
    if (instance == nullptr) {
        instance = new GameData();
    }
    return instance;
}

GameData::GameData() {
    std::srand((unsigned long) std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count());
}

