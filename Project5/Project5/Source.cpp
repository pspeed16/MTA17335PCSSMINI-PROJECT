#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")
//#include <thread>


#include <Ws2tcpip.h>
#include <WinSock2.h>
#include <string>
#include <iostream>

//SOCKET newConnection;
SOCKET Connection[10];
int ConnectionCounter = 0;


int main()
{
	//WinSock Startup
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0) //If WSAStartup returns anything other than 0, then that means an error has occured in the WinSock Startup.
	{
		MessageBoxA(NULL, "WinSock startup failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	//Different internet settings are specified
	SOCKADDR_IN addr; //Address that we will bind our listening socket to
	int addrlen = sizeof(addr); //length of the address (required for accept call)
	addr.sin_addr.s_addr = htonl(INADDR_ANY); // Looking for any connection trying to connect
											  //addr.sin_addr.s_addr = inet_addr("192.168.43.65"); //Broadcast locally
	addr.sin_port = htons(1111); //Port
	addr.sin_family = AF_INET; //IPv4 Socket add 6 after af_inet for ipv6

							   //Looking for a client to connect
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL); //Create socket to listen for new connections
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr)); //Bind the address to the socket
	listen(sListen, SOMAXCONN); //Places sListen socket in a state in which it is listening for an incoming connection. Note:SOMAXCONN = Socket Oustanding Max Connections

								// A new client connect
	SOCKET newConnection; //Socket to hold the client's connection
	for (int i = 0; i < 100; i++)
	{
		newConnection = accept(sListen, (SOCKADDR*)&addr, &addrlen); //Accept a new connection
		if (newConnection == 0) //If accepting the client connection failed
		{
			std::cout << "Failed to accept the client's connection." << std::endl;
		}
		else //If client connection properly accepted
		{
#define _WINSOCK_DEPRECATED_NO_WARNINGS
			//messege the client receives 
			std::cout << "Client Connected!  " << "Number " << i + 1 << std::endl;
			char MOTD[256] = "ØLAKT!"; //Create buffer with message of the day
			send(newConnection, MOTD, sizeof(MOTD), NULL); //Send MOTD buffer
		}
	}
}