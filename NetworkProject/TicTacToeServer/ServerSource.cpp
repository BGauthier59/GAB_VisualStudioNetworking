// Server App

#include <stdafx.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>

using namespace std;

int main() {

	#pragma region Setup Socket

	// Step 1: Set up DLL
		SOCKET serverSocket, acceptSocket_1, acceptSocket_2;
		int port = 55555;
		WSADATA wsaData;
		int wsaerr;
		WORD wVersionRequested = MAKEWORD(2, 2);
		wsaerr = WSAStartup(wVersionRequested, &wsaData);

		if (wsaerr != 0) {
			cout << "Didn't find Winsock dll" << endl;
			return 0;
		}
		else {
			cout << "Found Winsock dll" << endl;
		}

		// Step 2: Set up Server Socket
		serverSocket = INVALID_SOCKET;
		serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (serverSocket == INVALID_SOCKET) {
			cout << "Error at socket: " << WSAGetLastError() << endl;
			WSACleanup();
			return 0;
		}
		else {
			cout << "Socket is OK!" << endl;
		}

		// Step 3: Bind Socket
		sockaddr_in service;
		service.sin_family = AF_INET;
		InetPton(AF_INET, TEXT("10.51.0.241"), &service.sin_addr.s_addr);
		service.sin_port = htons(port);
		if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {

			cout << "Bind failed: " << WSAGetLastError() << endl;
			closesocket(serverSocket);
			WSACleanup();
			return 0;
		}
		else {
			cout << "Bind is OK!" << endl;
		}

		// Step 4: Initiate Listen
		if (listen(serverSocket, 2) == SOCKET_ERROR) {
			cout << "Error listening on socket: " << WSAGetLastError() << endl;
		}
		else {
			cout << "Listen is OK!" << endl;
		}

		// Step 5: Accept Connection
		acceptSocket_1 = accept(serverSocket, NULL, NULL);
		if (acceptSocket_1 == INVALID_SOCKET) {
			cout << "Accept failed: " << WSAGetLastError() << endl;
			WSACleanup();
			return -1;
		}

		cout << "Accepted connection" << endl;

		acceptSocket_2 = accept(serverSocket, NULL, NULL);
		if (acceptSocket_2 == INVALID_SOCKET) {
			cout << "Accept failed: " << WSAGetLastError() << endl;
			WSACleanup();
			return -1;
		}

		cout << "Accepted connection" << endl;
	#pragma endregion


	// Step 6: Receive data from client
	char buffer[1] = { 0 };
	int byteCount = send(acceptSocket_1, buffer, 1, 0);
	buffer[0] = 1;
	byteCount = send(acceptSocket_2, buffer, 1, 0);

	char turnBuffer[3] = { -1, -1, 0 };
	int currentTeam = 0;


	// Donner le contrôle à un joueur puis à l'autre
	while (true) {

		// (x, y, playerTurn);
		int byteCount = send(acceptSocket_1, turnBuffer, 3, 0);
		byteCount = send(acceptSocket_2, turnBuffer, 3, 0);
		
		byteCount = recv(currentTeam == 0 ? acceptSocket_1 : acceptSocket_2, turnBuffer, 3, 0);

		// Check victory

		currentTeam = currentTeam == 0 ? 1 : 0;
	}

	system("pause");

	// Step 7: Close Socket
	closesocket(acceptSocket_1);

	cout << "Client left" << endl;

	system("pause");
	WSACleanup();

	return 0;
}