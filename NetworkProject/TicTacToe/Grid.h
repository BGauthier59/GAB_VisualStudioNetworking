#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "PlayerShape.h"

using namespace sf;
using namespace std;

class Grid
{
public:
	Grid(string file);

	void Draw(RenderWindow &w);

	Texture texture;
	Sprite sprite;

	vector<PlayerShape*> shapes;
};

