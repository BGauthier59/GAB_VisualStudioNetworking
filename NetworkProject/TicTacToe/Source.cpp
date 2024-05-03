#include <SFML/Graphics.hpp>
#include "GameManager.h"

#include "PlayerShape.h"

using namespace std;
using namespace sf;

int main() {

	RenderWindow window(VideoMode(500, 500), "SFML works!");

	GameManager* manager = new GameManager();

	manager->TryAddShape(PlayerTeam::TEAM_1, 0, 0);
	manager->TryAddShape(PlayerTeam::TEAM_2, 1, 1);
	manager->TryAddShape(PlayerTeam::TEAM_1, 2, 2);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();

		manager->Update();
		manager->Draw(window);

		window.display();
	}

	return 0;
}