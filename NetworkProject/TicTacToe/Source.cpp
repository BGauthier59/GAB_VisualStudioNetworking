#include <SFML/Graphics.hpp>
#include "GameManager.h"

#include "PlayerShape.h"
#include <iostream>

#include <sys/types.h>
#include <winsock2.h>

using namespace std;
using namespace sf;

int main() {

	// creating socket 
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	// specifying the address 
	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(8080);
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	// binding socket
	bind(serverSocket, (struct sockaddr*)&serverAddress,
		sizeof(serverAddress));

	// listening to the assigned socket 
	listen(serverSocket, 5);

	// accepting connection request 
	int clientSocket
		= accept(serverSocket, nullptr, nullptr);



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

	delete manager;

	return 0;
}