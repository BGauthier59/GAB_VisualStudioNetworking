#include "GameManager.h"

#include "iostream"
using namespace std;

GameManager::GameManager(bool team)
{
	playerTeam = team ? TEAM_2 : TEAM_1;
	SetInputEnable(false);
	cout << "You are " << (team ? "TEAM 2" : "TEAM 1") << endl;
	grid = new Grid("grid.png");
}

void GameManager::Update()
{
}

void GameManager::Draw(RenderWindow& w)
{
	grid->Draw(w);
}

char* GameManager::ClickOnScreen(int mousePosX, int mousePosY)
{
	char buffer[3] = { -1, -1, -1 };
	if (!isRunning) return buffer;
	if (!isMyTurn) return buffer;

	// Find the hit box

	int gridSize = 500;

	int hitX = mousePosX < gridSize / 3.0f ? 0 : mousePosX < gridSize / 1.5f ? 1 : 2;
	int hitY = mousePosY < gridSize / 3.0f ? 0 : mousePosY < gridSize / 1.5f ? 1 : 2;

	bool correct = IsLocationAvailable(hitX, hitY);
	buffer[0] = hitX;
	buffer[1] = hitY;
	buffer[2] = correct ? playerTeam : -1;

	return buffer;


	//
	if (AddShape(currentPlayerTurn, hitX, hitY)) {

		SetInputEnable(false);

		if (CheckVictoryConditions(grid->shapes.back())) {
			cout << currentPlayerTurn << " has won!" << endl;
			isRunning = false;
		}
	}
}

void GameManager::SetInputEnable(bool enable)
{
	if(enable)	cout << "Your turn" << endl;
	isMyTurn = enable;
}

bool GameManager::AddShape(PlayerTeam team, int x, int y)
{
	PlayerShape* shape = new PlayerShape(team, x, y);
	grid->shapes.push_back(shape);

	if (CheckVictoryConditions(grid->shapes.back())) {
		cout << currentPlayerTurn << " has won!" << endl;
		isRunning = false;
		return true;
	}

	return false;
}

PlayerTeam GameManager::GetTeam()
{
	return playerTeam;
}

bool GameManager::IsInputEnable()
{
	return isMyTurn;
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
