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
	if (!isRunning) return;
	// Find the hit box

	int gridSize = 500;

	int hitX = mousePosX < gridSize / 3.0f ? 0 : mousePosX < gridSize / 1.5f ? 1 : 2;
	int hitY = mousePosY < gridSize / 3.0f ? 0 : mousePosY < gridSize / 1.5f ? 1 : 2;

	if (TryAddShape(currentPlayerTurn, hitX, hitY)) {
		if (CheckVictoryConditions(grid->shapes.back())) {
			cout << currentPlayerTurn << " has won!" << endl;
			isRunning = false;
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
	int x = last->posX;
	int y = last->posY;

	// Check row

	PlayerShape* row_down = GetShape(0, y);
	PlayerShape* row_middle = GetShape(1, y);
	PlayerShape* row_up = GetShape(2, y);
	bool sameTeam;

	if (row_down != nullptr && row_middle != nullptr && row_up != nullptr) {

		sameTeam = row_down->playerTeam == row_middle->playerTeam && row_middle->playerTeam == row_up->playerTeam;

		if (sameTeam) {
			cout << last->playerTeam << " has won by row" << endl;
			return true;
		}
	}

	// Check collumn

	PlayerShape* column_down = GetShape(x, 0);
	PlayerShape* column_middle = GetShape(x, 1);
	PlayerShape* column_up = GetShape(x, 2);

	if (column_down != nullptr && column_middle != nullptr && column_up != nullptr) {

		sameTeam = column_down->playerTeam == column_middle->playerTeam && column_middle->playerTeam == column_up->playerTeam;

		if (sameTeam) {
			cout << last->playerTeam << " has won by column" << endl;
			return true;
		}
	}

	// Check diagonales

	/*
	
		X
			X
				X
	
	*/

	PlayerShape* diagonale_left_up = GetShape(0, 0);
	PlayerShape* diagonale_center = GetShape(1, 1);
	PlayerShape* diagonale_right_down = GetShape(2, 2);

	if (diagonale_left_up != nullptr && diagonale_center != nullptr && diagonale_right_down != nullptr) {

		sameTeam = diagonale_left_up->playerTeam == diagonale_center->playerTeam && diagonale_center->playerTeam == diagonale_right_down->playerTeam;

		if (sameTeam) {
			cout << last->playerTeam << " has won by diagonale" << endl;
			return true;
		}
	}

	/*

				X
			X
		X

	*/

	PlayerShape* diagonale_left_down = GetShape(0, 2);
	PlayerShape* diagonale_right_up = GetShape(2, 0);

	if (diagonale_left_down != nullptr && diagonale_center != nullptr && diagonale_right_up != nullptr) {

		sameTeam = diagonale_left_down->playerTeam == diagonale_center->playerTeam && diagonale_center->playerTeam == diagonale_right_up->playerTeam;

		if (sameTeam) {
			cout << last->playerTeam << " has won by diagonale" << endl;
			return true;
		}
	}
	return false;
}

PlayerShape* GameManager::GetShape(int x, int y)
{
	if (x > 2 || y > 2) return nullptr;

	for (auto shape : grid->shapes) {
		if (shape->posX == x && shape->posY == y) return shape;
	}

	return nullptr;
}
