#pragma once

#include "Map.h"
#include <vector>
#include "Player.h"
#include "UI.h"
#include "Book.h"
#include "GameAssets.h"

class GameData {
private:
    std::vector<Enemy> enemyList;
    std::vector<Book> bookList;
    std::vector<Player> playerList;
    static GameData *instance;
    Coords getRandomWalkableTile();
    Map *currentMap;
	Map *lastMap;
    GameData();
public:
    // Getters
    std::vector<Player> *getPlayerList();

    Tile * getScoreTile(Player * player);
	
	Map * getLastMap();

    std::vector<Book> *getBookList();

    std::vector<Enemy> *getEnemyList();

    static GameData *getInstance();

    std::vector<UI> *getUI();

    Map *getCurrentMap();

    void createBook();

    void createPlayer();

    void createEnemy();

    void initialize();

    bool nextMap();
};

