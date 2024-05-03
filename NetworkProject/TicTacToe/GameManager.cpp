#include "GameManager.h"

GameManager::GameManager()
{
	grid = new Grid("grid.png");
}

void GameManager::Update()
{
}

void GameManager::Draw(RenderWindow& w)
{
	grid->Draw(w);
}

bool GameManager::TryAddShape(PlayerTeam team, int x, int y)
{
	PlayerShape* shape = new PlayerShape(team, x, y);
	grid->shapes.push_back(shape);

	return false;
}
