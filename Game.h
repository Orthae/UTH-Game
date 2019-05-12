#pragma once
#include "RenderEngine.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>

class Game
{
private:
	int gameSpeed;
	int enemyMultiplier;
	RenderEngine renderEngine;
public:
	void mainMenu();
	void setGameSpeed();
	void setEnemyMultiplier();
	void printScore() const;
	void start();
	void spawnObjects() const;
	void renderGame() const;
	void createGameObjects() const;
	void despawnGameObjects() const;
	void playerLogic() const;
	bool collisionWithEnemies() const;
	void collisionWithBooks() const;
	bool checkPlayersScore() const;
	bool gameLogic() const;
	void updateScore() const;
	void enemyLogic() const;
	void run() const;
	Game();
	~Game();
};

