#pragma once

#include "Grid.h"
#include "Enums.h"

class GameManager
{
public:
	GameManager(bool team);

	void Update();
	void Draw(RenderWindow& w);
	char* ClickOnScreen(int mousePosX, int mousePosY);
	void SetInputEnable(bool enable);
	bool AddShape(PlayerTeam team, int x, int y);
	PlayerTeam GetTeam();
	bool IsInputEnable();
	
private:
	
	bool IsLocationAvailable(int x, int y);
	bool CheckVictoryConditions(PlayerShape* last);

	PlayerShape* GetShape(int x, int y);

	Grid* grid;
	PlayerTeam currentPlayerTurn;
	PlayerTeam playerTeam;
	bool isRunning = true;

	bool isMyTurn;
};

