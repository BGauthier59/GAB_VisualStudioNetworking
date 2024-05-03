#pragma once

#include <SFML/Graphics.hpp>

#include "Enums.h"
#include <string>

using namespace std;
using namespace sf;

class PlayerShape
{
public:
	PlayerShape(PlayerTeam team, int x, int y);
	void Draw(RenderWindow& w);

	PlayerTeam playerTeam;
	int posX;
	int posY;

	/* COORDS ARE
	
		X = 0 1 2

		Y = 0
			1
			2
	
	*/

	Texture texture;
	Sprite sprite;
};

