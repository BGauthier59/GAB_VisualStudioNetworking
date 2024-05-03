#include <SFML/Graphics.hpp>
#include "GameManager.h"

#include "PlayerShape.h"
#include <iostream>

using namespace std;
using namespace sf;

int main() {

	RenderWindow window(VideoMode(500, 500), "SFML works!");

	GameManager* manager = new GameManager();

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			else if (event.type == Event::MouseButtonPressed) {
			
				Vector2i mousePos = Mouse::getPosition(window);
				manager->ClickOnScreen(mousePos.x, mousePos.y);
			}
		}

		window.clear();

		manager->Update();
		manager->Draw(window);

		window.display();
	}

	return 0;
}