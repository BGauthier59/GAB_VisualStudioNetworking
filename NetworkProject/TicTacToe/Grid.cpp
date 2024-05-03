#include "Grid.h"

#include <iostream>
using namespace std;

Grid::Grid(string file)
{
	cout << "Grid created" << endl;

	texture.loadFromFile(file);
	sprite.setTexture(texture);
}

void Grid::Draw(RenderWindow& w)
{
	w.draw(sprite);

	for (auto shape : shapes) {

		shape->Draw(w);
	}
}
