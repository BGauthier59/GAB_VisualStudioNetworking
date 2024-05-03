#include "GameManager.h"

#include "iostream"
using namespace std;

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

void GameManager::ClickOnScreen(int mousePosX, int mousePosY)
{
	// Find the hit box

	int gridSize = 500;

	int hitX = mousePosX < gridSize / 3.0f ? 0 : mousePosX < gridSize / 1.5f ? 1 : 2;
	int hitY = mousePosY < gridSize / 3.0f ? 0 : mousePosY < gridSize / 1.5f ? 1 : 2;

	if (TryAddShape(currentPlayerTurn, hitX, hitY)) {
		if (CheckVictoryConditions(grid->shapes.back())) {
			cout << currentPlayerTurn << " has won!" << endl;
		}
		else SwitchTurn();
	}
}

void GameManager::SwitchTurn()
{
	currentPlayerTurn = currentPlayerTurn == PlayerTeam::TEAM_1 ? PlayerTeam::TEAM_2 : PlayerTeam::TEAM_1;
}

bool GameManager::TryAddShape(PlayerTeam team, int x, int y)
{
	if (!IsLocationAvailable(x, y)) return false;

	PlayerShape* shape = new PlayerShape(team, x, y);
	grid->shapes.push_back(shape);

	return true;
}

bool GameManager::IsLocationAvailable(int x, int y)
{
	for (auto shape : grid->shapes) {
		if (shape->posX == x && shape->posY == y) return false;
	}
	return true;
}

bool GameManager::CheckVictoryConditions(PlayerShape* last)
{
	return false;

	// WIP

	// Try find first neighbour

	Shape* firstNeighbour;
	for (auto shape : grid->shapes) {
		if (shape == last) continue;

		if (shape->posX == last->posX) {

		}

		else if(shape->posY == last->posY) {

		}

		else {

		}
	}

	return false;
}

PlayerShape* GameManager::FindNeighbour(int x, int y)
{
	return nullptr;
}
