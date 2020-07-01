#include <stdio.h>
#include <winsock2.h>
#pragma warning(disable:4996)

#pragma comment(lib,"ws2_32.lib") //Winsock Library

int main(int argc, char* argv[])
{
	WSADATA wsa;
	int retCode = 0;

	// Initierar Winsock Version 2.2
	retCode = WSAStartup(MAKEWORD(2, 2), &wsa);

	if (retCode != 0) {
		printf("WSAStartup failed to initialize, error %d\n", retCode);
	}
	else {
		printf("The Winsock .dll was found!\n");
		printf("Current status: %s.\n", wsa.szSystemStatus);
	}

	// Create a socket called m_socket;
	SOCKET m_socket;

	// Call the socket function and return its value to the m_socket variable
	// Using Internet address family, streaming sockets, and the TCP/IP protocol.
	// Using AF_INET family, TCP socket type and protocol of the AF_INET - IPv4
	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// Check for errors to ensure that the socket is a valid socket
	if (m_socket == INVALID_SOCKET) {
		printf("Error at m_socket: %ld\n", WSAGetLastError());
	}
	else
		printf("m_socket is OK!\n");

	// bind()
	// Create a sockaddr_in object and set its values.
	SOCKADDR_IN service;

	// AF_INET is the Internet address family.
	service.sin_family = AF_INET;
	// "127.0.0.1" is the local IP address to which the socket will be bound.
	service.sin_addr.s_addr = inet_addr("127.0.0.1");
	// 55555 is the port number to wich the socket will be bound.
	service.sin_port = htons(55555);

	// Call the bind function, passing the created socket and the sockaddr_in structure as parameters.
	// Check for general errors.
	if (bind(m_socket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
		printf("bind() failed, %ld.\n", WSAGetLastError());
	}
	else
		printf("bind() was successfull!\n");

	// Call the listen function, passing the created socket and the maximum number of
	// allowed connections to accept as parameters. Check for general errors.

	if (listen(m_socket, 1) == SOCKET_ERROR) {
		printf("listen() failed, %ld.\n", WSAGetLastError());
	}
	else
		printf("listen() is OK, waiting for connections...\n");
	
	closesocket(m_socket);
	WSACleanup();

	return 0;
}