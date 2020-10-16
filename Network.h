#pragma once
#ifdef __linux__ || __APPLE__
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#elif defined(_WIN32)
#include <winsock2.h>
#include <ws2tcpip.h>
#else
printf("submit your OS to the distributor and wait for another update to go online.")
#endif
#include <string>
#include <stdio.h>
#include <iostream>
#include <atomic>
#include <memory>

class Connection
{
private:

public:
	int sock = 0, valread;
	char buffer[1024] = { 0 };
	int CreateSocket(int PORT, std::string IP) {
		struct sockaddr_in serv_addr;

#ifdef _WIN32
		WSADATA wsaData;
		WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

		if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
			printf("\n Socket creation error \n");
			return -1;
		}
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(PORT);

		if (inet_pton(AF_INET, IP.c_str(), &serv_addr.sin_addr) <= 0)
		{
			printf("\nInvalid address/ Address not supported \n");
			return -1;
		}

		if (connect(sock, (struct sockaddr*) & serv_addr, sizeof(serv_addr)) < 0)
		{
			printf("\nConnection Failed \n");
			return -1;
		}
		return 0;
	}

	void SendData(std::string message) {
		send(sock, message.c_str(), strlen(message.c_str()), 0);
	}

	void fetchIncomingData(std::atomic<bool>* closed) {
		while (!closed->load()) {
#ifdef __LINUX__ || __APPLE__
			struct timeval timeout;
			timeout.tv_sec = 2;
			timeout.tv_usec = 0;
			setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
			valread = read(sock, buffer, 1024);
#elif defined(_WIN32)
			DWORD timeout = 2 * 1000;
			setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));

			if ((valread = recv(sock, buffer, 1024, 0)) == SOCKET_ERROR) {
				int err = WSAGetLastError();
				switch (err)
				{
				case(WSAETIMEDOUT): {break; }
				case(WSAEMSGSIZE): {std::cout << "ERROR GETTING MESSAGE: MESSAGE TOO BIG" << std::endl; break; }
				case(WSAENOTCONN): {
					std::cout << "CONNECTION CLOSED" << std::endl;
					break;
				}
				case(WSAECONNABORTED): {
					std::cout << "CONNECTION CLOSED" << std::endl;
					break;
				}
				}
			}
#endif
			if (valread > 0) {
				std::cout << buffer << std::endl;
				if (std::string(buffer).compare("HELLO")) {
					std::cout << "Connected" << std::endl;
				}
				else {
					std::cout << std::string(buffer) << std::endl;
				}
			}
		}
	}

	int cleanup() {
#ifdef _WIN32
		shutdown(this->sock, 0);
		closesocket(this->sock);
		WSACleanup();
#endif
		std::cout << "Socket cleaned up" << std::endl;
		return 0;
	}
};
