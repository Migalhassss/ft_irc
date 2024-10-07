/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:35:18 by micarrel          #+#    #+#             */
/*   Updated: 2024/10/01 13:35:18 by micarrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"
#include "Commands.hpp"

bool Server::Signal = false;

Server::Server()
{
	this->SerSocket = -1;
}

Server::~Server()
{
	this->CloseFds();
}

void Server::setPort(int port)
{
	this->port = port;
}

int Server::getPort()
{
	return (this->port);
}

void Server::setPassword(std::string password)
{
	this->Password = password;
}

std::string Server::getPassword()
{
	return (this->Password);
}

void Server::SignalHandler(int signum)
{
	(void)signum;
	Server::Signal = true;
}

Client* Server::getClient(int fd) {
	for (std::vector<Client>::iterator it = ClientsList.begin(); it != ClientsList.end(); ++it) {
		if (it->GetFd() == fd) {
			return &(*it);
		}
	}
	std::cout << "Client <" << fd << "> not found" << std::endl;
	return NULL;
}

void Server::CloseClient(int fd) {
	for (size_t i = 0; i < this->ClientsList.size(); i++) {
		if (this->ClientsList[i].GetFd() == fd) {
			std::cout << "Client <" << fd << "> Disconnected" << std::endl;
			this->ClientsList.erase(this->ClientsList.begin() + i);
			epoll_ctl(epollFd, EPOLL_CTL_DEL, fd, NULL);
			close(fd);
			break;
		}
	}
}

void Server::CloseFds() {
	for (size_t i = 0; i < this->ClientsList.size(); i++) {
		int fd = this->ClientsList[i].GetFd();
		if (fd != -1)
			close(fd);
	}
	if (this->SerSocket != -1)
		close(this->SerSocket);
}

void Server::AcceptNewClient()
{
	Client NewClient; // Create new client
	struct sockaddr_in clientAddr; // Create client address
	struct epoll_event clientEvent; // Create new epoll event
	socklen_t len = sizeof(clientAddr); // Set length of client address

	int newClientSocket = accept(SerSocket, (struct sockaddr *)&clientAddr, &len); // Accept new client
	if (newClientSocket == -1) {
		std::cout << "Failed to accept new client" << std::endl;
		return;
	}
	if (fcntl(newClientSocket, F_SETFL, O_NONBLOCK) == -1) {
		std::cout << "Failed to set socket to non-blocking" << std::endl;
		return;
	}

	clientEvent.data.fd = newClientSocket; // Set file descriptor
	clientEvent.events = EPOLLIN; // Set events to epoll
	if (epoll_ctl(epollFd, EPOLL_CTL_ADD, newClientSocket, &clientEvent) == -1) {
		std::cout << "Failed to add client socket to epoll" << std::endl;
		close(newClientSocket);
		return;
	}

	NewClient.SetFd(newClientSocket); // Set client id
	NewClient.SetIp(inet_ntoa(clientAddr.sin_addr)); // Set client IP
	NewClient.SetPort(ntohs(clientAddr.sin_port)); // Set client port
	ClientsList.push_back(NewClient); // Add client to list

	std::cout << "New client connected: " << newClientSocket << std::endl;
}

void Server::menageData(char *buffer, int fd)
{
	std::string data = buffer;
	std::string command = data.substr(0, data.find(" "));
	std::string message = data.substr(data.find(" ") + 1);

	execCommand(command, message, fd);
}

void Server::execCommand(std::string command, std::string message, int fd)
{
	 std::cout << "Executing command: " << command << " with message: " << message << " from client <" << fd << ">" << std::endl;
	std::string CmdList[] = 
	{
		"NICK",
		"USER",
		"JOIN",
		// "PART",
		// "PRIVMSG",
		// "QUIT",
		// "KICK",
		// "MODE",
		// "TOPIC",
		// "PASS",
		// "CAP",
		// "WHO",
		// "INVITE",
	};

	void (*CmdFunctions[])(Client *client) = {
		nickCommand,
		userCommand,
		joinCommand,
		// partCommand,
		// privmsgCommand,
		// quitCommand,
		// kickCommand,
		// modeCommand,
		// topicCommand,
		// passCommand,
		// capCommand,
		// whoCommand,
		// inviteCommand
	};
	message = trimNewline(message);
	command = trimNewline(command);
	Client *client;
	client = getClient(fd);
	if (client == NULL)
		return;
	client->SetMessage(message);
	for (size_t i = 0; i < sizeof(CmdList) / sizeof(CmdList[0]); i++)
	{
		if (command == CmdList[i])
		{
			CmdFunctions[i](client); // Call the corresponding function
			break;
		}
	}
}

void Server::ReceiveNewData(int fd)
{
	char buffer[1024]; // Create buffer
	memset(buffer, 0, sizeof(buffer)); // Clear buffer

	ssize_t bytesRead = recv(fd, buffer, sizeof(buffer) - 1, 0); // Receive data

	if (bytesRead <= 0)
	{
		std::cout << "Client <" << fd << "> Disconnected" << std::endl;
		CloseClient(fd);
		close(fd);
	}
	else
	{
		buffer[bytesRead] = '\0';
		std::cout << "Received data from client <" << fd << ">: " << buffer << std::endl;
		menageData(buffer, fd);
	}
}

void Server::ServerSocket()
{
	struct sockaddr_in serverAddr;
	struct epoll_event event;

	serverAddr.sin_family = AF_INET; // Address family = Internet
	serverAddr.sin_port = htons(this->port); // Set port
	serverAddr.sin_addr.s_addr = INADDR_ANY; // Set IP address to localhost

	SerSocket = socket(AF_INET, SOCK_STREAM, 0); // Create server socket
	if (SerSocket == -1)
		throw std::runtime_error("Failed to create server socket");
	
	int enable = 1;
	if (setsockopt(SerSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) // Set socket options
		throw std::runtime_error("Failed to set socket options");
	if (fcntl(SerSocket, F_SETFL, O_NONBLOCK) == -1) // Set socket to non-blocking
		throw std::runtime_error("Failed to set socket to non-blocking");
	if (bind(SerSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) // Bind socket to address
		throw std::runtime_error("Failed to bind server socket");
	if (listen(SerSocket, 10) == -1) // Listen for incoming connections
		throw std::runtime_error("Failed to listen for incoming connections");
	
	epollFd = epoll_create1(0); // Create epoll instance
	if (epollFd == -1)
		throw std::runtime_error("Failed to create epoll instance");

	event.data.fd = SerSocket;
	event.events = EPOLLIN;
	if (epoll_ctl(epollFd, EPOLL_CTL_ADD, SerSocket, &event) == -1)
		throw std::runtime_error("Failed to add server socket to epoll");
}

void Server::ServerInit()
{
	this->port = 4444;
	ServerSocket();
	std::cout << "Server initialized successfully." << std::endl;
	std::cout << "Server <" << SerSocket << "> Connected" << std::endl;
	std::cout << "Waiting to accept a connection...\n";

	events.resize(10);

	while (!Server::Signal)
	{
		int eventCount = epoll_wait(epollFd, events.data(), events.size(), -1);
		if (eventCount == -1 && Server::Signal == false) {
			if (errno == EINTR) // Interrupted by signal
				continue;
			std::cerr << "epoll_wait failed: " << std::strerror(errno) << std::endl;
			throw std::runtime_error("epoll_wait failed");
		}
		for (int i = 0; i < eventCount; ++i) {
			if (events[i].events & EPOLLIN)
			{
				if (events[i].data.fd == SerSocket) {
					// Handle new client
					AcceptNewClient();
				} else {
					// Handle client data
					char buffer[1024];
					int bytesRead = recv(events[i].data.fd, buffer, sizeof(buffer) - 1, 0);
					if (bytesRead <= 0) {
						if (bytesRead == 0) {
							std::cout << "Client disconnected: " << events[i].data.fd << std::endl;
						} else {
							std::cerr << "Error reading from client: " << events[i].data.fd << std::endl;
						}

						close(events[i].data.fd);
						epoll_ctl(epollFd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
					} else {
						buffer[bytesRead] = '\0';
						std::cout << "Received data from client <" << events[i].data.fd << ">: " << buffer << std::endl;
						menageData(buffer, events[i].data.fd);
					}
				}
			} 
			else if (events[i].events & (EPOLLHUP | EPOLLERR))
			{
				std::cout << "Client disconnected or error: " << events[i].data.fd << std::endl;
				close(events[i].data.fd);
				epoll_ctl(epollFd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
			}
		}
	}
}
