#include <SFML/Graphics.hpp>
#include "GameManager.h"

#include "PlayerShape.h"
#include <iostream>

#include <stdafx.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

using namespace std;
using namespace sf;

int SetupSocket(SOCKET& clientSocket);
int closeSocket(SOCKET& clientSocket);

int main() {

	SOCKET clientSocket;
	int output = SetupSocket(clientSocket);
	if (output == -1) {
		cout << "Error with socket setup" << endl;
		return 0;
	}

	RenderWindow window(VideoMode(500, 500), "SFML works!");

	GameManager* manager = new GameManager(output);

	char turnBuffer[3];
	recv(clientSocket, turnBuffer, 3, 0);
	manager->TryAddShape(turnBuffer[2] == 0 ? TEAM_1 : TEAM_2, (int)turnBuffer[0], (int)turnBuffer[1]);
	manager->SetInputEnable((int) turnBuffer[2] == manager->GetTeam());

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			else if (event.type == Event::MouseButtonPressed) {
			
				Vector2i mousePos = Mouse::getPosition(window);
				char* buffer = manager->ClickOnScreen(mousePos.x, mousePos.y);
				if (buffer[2] == -1) {
					cout << "Incorrect input" << endl;
				}
				else {
					send(clientSocket, buffer, 3, 0);
					manager->SetInputEnable(false);
				}
			}
		}

		if (!manager->IsInputEnable()) {

			recv(clientSocket, turnBuffer, 3, 0);
			manager->TryAddShape((int)turnBuffer[2] == 0 ? TEAM_1 : TEAM_2, (int)turnBuffer[0], (int)turnBuffer[1]);
			manager->SetInputEnable((int)turnBuffer[2] != manager->GetTeam());
		}

		window.clear();

		manager->Update();
		manager->Draw(window);

		window.display();
	}

	closeSocket(clientSocket);

	return 0;
}

int SetupSocket(SOCKET& clientSocket)
{
	// Step 1: Set up DLL
	clientSocket;
	int port = 55555;
	WSADATA wsaData;
	int wsaerr;
	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);

	if (wsaerr != 0) {
		cout << "Didn't find Winsock dll" << endl;
		return -1;
	}
	else {
		cout << "Found Winsock dll" << endl;
	}

	// Step 2: Set up Client Socket

	clientSocket = INVALID_SOCKET;
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET) {
		cout << "Error at socket: " << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}
	else {
		cout << "Socket is OK!" << endl;
	}

	// Step 3: Connect with Server
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	InetPton(AF_INET, TEXT("10.51.0.241"), &clientService.sin_addr.s_addr);
	clientService.sin_port = htons(port);
	if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {

		cout << "Client failed to connect" << endl;
		WSACleanup();
		return -1;
	}
	else {
		cout << "Client connected" << endl;
	}

	// Step 4: Send data to Server
	// RECEVOIR TEAM
	char buffer[1];
	int byteCount = recv(clientSocket, buffer, 1, 0);
	cout << (int) buffer[0] << endl;
	
	return (int) buffer[0];
}

int closeSocket(SOCKET& clientSocket)
{
	// Step 5: Close Socket
	closesocket(clientSocket);

	cout << "End of discussion" << endl;
	WSACleanup();
	return 1;
}
