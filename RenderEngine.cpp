#include "pch.h"
#include "RenderEngine.h"
#include <windows.h>
#include <iostream>
#include <iomanip>
#include "GameData.h"
#include "Tile.h"
#include "GameAssets.h"
#include "Map.h"
#include "UI.h"
#include <thread>

	void RenderEngine::spawnObject(GameObject const * const object) const {
		renderTile(object->getCurrentCoords()->getX(), object->getCurrentCoords()->getY(), object->getSprite());
	}

	void RenderEngine::despawnObject(GameObject const * const object) const {
		int x = object->getCurrentCoords()->getX();
		int y = object->getCurrentCoords()->getY();
		renderTile(x, y, GameData::getInstance()->getCurrentMap()->getTile(y, x));
	}

	void RenderEngine::updateObject(GameObject const * const object) const {
		spawnObject(object);
		int const lastX = object->getLastCoords()->getX();
		int const lastY = object->getLastCoords()->getY();
		renderTile(lastX, lastY, GameData::getInstance()->getCurrentMap()->getTile(lastY, lastX));
	}

	void RenderEngine::renderUI(int const playerIndex, UI const * const gameUI) const {
		for (int x = 0; x < 24; x++) {
			renderUITile(playerIndex, x, gameUI->getTile(x));
		}
	}

	void RenderEngine::renderTile(int const mapX, int const mapY, Tile const * const gameTile) const {
		for (int tileX = 0; tileX < 32; tileX++) {
			for (int tileY = 0; tileY < 32; tileY++) {
				if (gameTile->getSpritePixel((tileY / 2), (tileX / 2)) == 0)
					continue;
				int x = (mapX * 32) + tileX;
				int y = ((mapY + 1) * 32) + tileY;
				SetPixel(console, x, y, gameTile->getSpritePixel((tileY / 2), (tileX / 2)));
			}
		}
	}

	void RenderEngine::renderUITile(int const player, int const x, Tile const * const guiTile) const {
		for (int tileX = 0; tileX < 32; tileX++) {
			for (int tileY = 0; tileY < 32; tileY++) {
				SetPixel(console, (x * 32) + tileX, (26 * 32 * player) + tileY, guiTile->getSpritePixel((tileY / 2), (tileX / 2)));
			}
		}
	}

	void RenderEngine::renderBackground(Map const * const currentMap) const {
		Map const * const last = GameData::getInstance()->getLastMap();	
		for (int mapX = 0; mapX < 25; mapX++)
			for (int mapY = 0; mapY < 25; mapY++) {
				if (last != nullptr && (currentMap->getTile(mapY, mapX) == last->getTile(mapY, mapX)))
					continue;
				renderTile(mapX, mapY, currentMap->getTile(mapY, mapX));
			}
	}

	RenderEngine::RenderEngine() {
		system("MODE CON COLS=120 LINES=80");
		console = GetDC(GetConsoleWindow());
		ShowWindow(GetConsoleWindow(), SW_MAXIMIZE); 
		if (console == nullptr) {
			exit(1);
		}
	}

	RenderEngine::~RenderEngine()
	= default;


