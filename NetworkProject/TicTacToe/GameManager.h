#pragma once

#include "Grid.h"
#include "Enums.h"

class GameManager
{
public:
	GameManager();

	void Update();
	void Draw(RenderWindow& w);
	void ClickOnScreen(int mousePosX, int mousePosY);
	
private:
	
	void SwitchTurn();
	bool TryAddShape(PlayerTeam team, int x, int y);
	bool IsLocationAvailable(int x, int y);
	bool CheckVictoryConditions(PlayerShape* last);

	PlayerShape* GetShape(int x, int y);

	Grid* grid;
	PlayerTeam currentPlayerTurn;
	bool isRunning = true;
};

