#include "pch.h"
#include "Game.h"
#include "GameAssets.h"
#include <vector>
#include <iostream>
#include "GameData.h"
#include <chrono>
#include "Coords.h"
#include <conio.h>
#include <iomanip>
#include "Book.h"
#include "UI.h"
#include <string>

void Game::start() {
    mainMenu();
    while (GameData::getInstance()->nextMap()) {
        run();
    }
    printScore();
    // Oczekiwanie na ESC zeby zamknac gre
    while (_getch() != 27);

}

void Game::mainMenu() {
    system("cls");
    std::cout << "UTH Game\n"
              << "1. Start game\n"
              << "2. Change enemy multiplier\n"
              << "3. Change enemy speed\n\n\n"
              << "Player 1 keys\n"
              << "UP - Arrow up, DOWN - Arrow down, LEFT - Arrow left, Right - Arrow Right\n"
              << "Player 2 keys\n"
              << "UP - W, DOWN - S, LEFT - A, Right - D\n\n";

    std::string command;
    do {
        std::cout << "Command: ";
        std::cin >> command;
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
            if(command == "1"){
                system("cls");
                return;
            }
            if(command == "2"){
                setEnemyMultiplier();
                continue;
            }
            if(command == "3"){
                setGameSpeed();
                continue;
            }
        std::cout << "Unknown command\n";
    } while (true);
}

void Game::setGameSpeed(){
		std::cout << "Enter game speed from 1 to 3.\n"
					 "Current Game speed is " << 7 / gameSpeed << "\n";

        std::string command;
    do {
        std::cout << "Enter game speed :";
        std::cin >> command;
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        if(command == "1"){
            gameSpeed = 7;
            return;
        }
        if(command == "2"){
            gameSpeed = 3;
            return;
        }
        if(command == "3"){
            gameSpeed = 2;
            return;
        }
        std::cout << "Unknown command\n";
    } while(true);
}

void Game::setEnemyMultiplier(){
    std::cout << "Enter enemy multiplier from 1 to 3.\n"
                 "Current enemy multiplier is " << enemyMultiplier << "\n";
    std::string command;
    do {
        std::cout << "Enter enemy multiplier :";
        std::cin >> command;
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        if(command == "1"){
            gameSpeed = 1;
            return;
        }
        if(command == "2"){
            gameSpeed = 2;
            return;
        }
        if(command == "3"){
            gameSpeed = 3;
            return;
        }
        std::cout << "Unknown command\n";
    } while(true);
}

void Game::printScore() const {
    Player * p1 = &GameData::getInstance()->getPlayerList()->at(0);
    Player * p2 = &GameData::getInstance()->getPlayerList()->at(1);

    renderEngine.renderTile(11, 12, &GameAssets::getInstance()->getGameTiles()->at(18));
    renderEngine.renderTile(11, 12, p1->getSprite());
    renderEngine.renderTile(13, 13, &GameAssets::getInstance()->getGameTiles()->at(18));
    renderEngine.renderTile(13, 13, p2->getSprite());
    renderEngine.renderTile(12, 12, GameData::getInstance()->getScoreTile(p1));
    renderEngine.renderTile(12, 13, GameData::getInstance()->getScoreTile(p2));
}

void Game::renderGame() const {
	renderEngine.renderBackground(GameData::getInstance()->getCurrentMap());
	for (unsigned int i = 0; i < GameData::getInstance()->getPlayerList()->size(); i++) {
		renderEngine.renderUI(i, &GameAssets::getInstance()->getGameUI()->at(i));
	}
}

void Game::spawnObjects() const {
	for (Player &player : *GameData::getInstance()->getPlayerList()) {
		renderEngine.spawnObject(&player);
	}
	for (Enemy &enemy : *GameData::getInstance()->getEnemyList()) {
		renderEngine.spawnObject(&enemy);
	}
	for (Book &book : *GameData::getInstance()->getBookList()) {
		renderEngine.spawnObject(&book);
	}
}

void Game::createGameObjects() const {
	static int called = 1;
	GameData::getInstance()->createPlayer();
	for (unsigned int i = 0; i < (unsigned int)(called * enemyMultiplier); i++) {
		GameData::getInstance()->createEnemy();
	}
	for (unsigned int i = 0; i < 3; i++) {
		GameData::getInstance()->createBook();
	}
	called++;
}

void Game::despawnGameObjects() const{
	for (Player &player : *GameData::getInstance()->getPlayerList()) {
		renderEngine.despawnObject(&player);
	}
	for (Enemy &enemy : *GameData::getInstance()->getEnemyList()) {
		renderEngine.despawnObject(&enemy);
	}
	for (Book &book : *GameData::getInstance()->getBookList()) {
		renderEngine.despawnObject(&book);
	}
	GameData::getInstance()->getBookList()->clear();
	GameData::getInstance()->getEnemyList()->clear();
}

void Game::playerLogic() const {
	for (Player &player : *GameData::getInstance()->getPlayerList()) {
		if (player.handle()) {
			renderEngine.updateObject(&player);
		}
	}
}

bool Game::collisionWithEnemies() const {
	for (unsigned int playerIndex = 0; playerIndex < GameData::getInstance()->getPlayerList()->size(); playerIndex++) {
		for (unsigned int enemyIndex = 0; enemyIndex < GameData::getInstance()->getEnemyList()->size(); enemyIndex++) {
			Player *player = &GameData::getInstance()->getPlayerList()->at(playerIndex);
			if (*player->getCurrentCoords() ==
				GameData::getInstance()->getEnemyList()->at(enemyIndex).getCurrentCoords() && player->getIsAlive()) {
				player->setIsAlive(false);
			}
		}
	}
	return false;
}

void Game::collisionWithBooks() const {
	for (unsigned int bookIndex = 0; bookIndex < GameData::getInstance()->getBookList()->size(); bookIndex++) {
		for (unsigned int playerIndex = 0;
			playerIndex < GameData::getInstance()->getPlayerList()->size(); playerIndex++) {
			if (*GameData::getInstance()->getPlayerList()->at(playerIndex).getCurrentCoords() ==
				GameData::getInstance()->getBookList()->at(bookIndex).getCurrentCoords()) {
				int points = GameData::getInstance()->getPlayerList()->at(playerIndex).getPoints();
				for (int j = points;
					j < (points + GameData::getInstance()->getBookList()->at(bookIndex).getPoints()); j++) {
					if (points >= 19) {
						break;
					}
					renderEngine.renderUITile(playerIndex, j + 5, &GameAssets::getInstance()->getGameTiles()->at(10));
				}
				GameData::getInstance()->getPlayerList()->at(playerIndex).setPoints(points + GameData::getInstance()->getBookList()->at(bookIndex).getPoints());
				GameData::getInstance()->getBookList()->erase(GameData::getInstance()->getBookList()->begin() + bookIndex);
				GameData::getInstance()->createBook();
				GameData::getInstance()->getBookList()->at(GameData::getInstance()->getBookList()->size() - 1);
				renderEngine.spawnObject(&GameData::getInstance()->getBookList()->at(GameData::getInstance()->getBookList()->size() - 1));
			}
		}
	}
}

bool Game::checkPlayersScore() const {
	int alivePlayerIndex = -1;
	int alivePlayerCount = 0;
	for (unsigned int playerIndex = 0; playerIndex < GameData::getInstance()->getPlayerList()->size(); playerIndex++) {
		if (GameData::getInstance()->getPlayerList()->at(playerIndex).getPoints() >= 19) {
			renderEngine.despawnObject(&GameData::getInstance()->getPlayerList()->at(playerIndex));
			GameData::getInstance()->getPlayerList()->at(playerIndex).addGamePoints();
			return true;
		}
		if (GameData::getInstance()->getPlayerList()->at(playerIndex).getIsAlive()) {
			alivePlayerIndex = playerIndex;
			alivePlayerCount++;
		}
	}
	if (alivePlayerCount == 1 && alivePlayerIndex != -1) {
		GameData::getInstance()->getPlayerList()->at(alivePlayerIndex).addGamePoints();
		return true;
	}
	return false;
}

bool Game::gameLogic() const {
	if (collisionWithEnemies()) {
		return false;
	}
	collisionWithBooks();
	if (checkPlayersScore()) {
		return false;
	}
	return true;
}

void Game::run() const {
    createGameObjects();
    renderGame();
    updateScore();
    spawnObjects();
    while (gameLogic()) {
        enemyLogic();
        playerLogic();
        Sleep(50);
    }
    updateScore();
    despawnGameObjects();
}

void Game::updateScore() const {
    for (unsigned int playerIndex = 0; playerIndex < GameData::getInstance()->getPlayerList()->size(); playerIndex++) {
        Player * player = &GameData::getInstance()->getPlayerList()->at(playerIndex);
        renderEngine.renderUITile(playerIndex, 24, GameData::getInstance()->getScoreTile(player));
    }
}

void Game::enemyLogic() const {
    static unsigned int iterator = 0;
    if ((iterator % gameSpeed) == 0) {
        for (Enemy &enemy : *GameData::getInstance()->getEnemyList()) {
            if (enemy.handle())
                renderEngine.updateObject(&enemy);
        }
        for (unsigned int i = 0; i < GameData::getInstance()->getEnemyList()->size(); i++) {
            for (unsigned int j = 0; j < GameData::getInstance()->getBookList()->size(); j++) {
                if (*GameData::getInstance()->getEnemyList()->at(i).getLastCoords() ==
                    GameData::getInstance()->getBookList()->at(j).getCurrentCoords()) {
                    renderEngine.updateObject(&GameData::getInstance()->getBookList()->at(j));
                }
            }
        }
    }
    iterator++;
}

Game::Game() {
    GameAssets::getInstance()->initialize();
    GameData::getInstance()->initialize();
    renderEngine = RenderEngine();
    gameSpeed = 7;
    enemyMultiplier = 3;
}

Game::~Game()
= default;