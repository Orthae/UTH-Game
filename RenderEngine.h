#pragma once
#include <windows.h>
#include "Tile.h"
#include "GameObject.h"
#include "Map.h"
#include "UI.h"

class RenderEngine
{
private:
	HDC console;
public:
	RenderEngine();
	~RenderEngine();
	void spawnObject(GameObject const * const object) const;
	void despawnObject(GameObject const * const object) const;
	void updateObject(GameObject const * const object) const;
	void renderBackground(Map const * const currentMap) const;
	void renderTile(int const mapX, int const mapY, Tile const * const gameTile) const;
	void renderUI(int const playerIndex , UI const * const gameUI) const;
	void renderUITile(int const player, int const x, Tile const * const guiTile) const;
};

