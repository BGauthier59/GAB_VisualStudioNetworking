#pragma once

#include "Grid.h"
#include "Enums.h"

class GameManager
{
public:
	GameManager();

	void Update();
	void Draw(RenderWindow& w);
	bool TryAddShape(PlayerTeam team, int x, int y);

	Grid* grid;
};

