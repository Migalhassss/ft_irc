/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:09:04 by micarrel          #+#    #+#             */
/*   Updated: 2024/10/01 12:09:04 by micarrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <vector> //-> for vector
#include <sys/socket.h> //-> for socket()
#include <sys/types.h> //-> for socket()
#include <netinet/in.h> //-> for sockaddr_in
#include <fcntl.h> //-> for fcntl()
#include <unistd.h> //-> for close()
#include <arpa/inet.h> //-> for inet_ntoa()
#include <sys/epoll.h> //-> for poll()
#include <csignal> //-> for signal()
#include <cerrno> 
#include <cstring>
#include <cstdlib>
#include <map>
#include "Client.hpp"

class Server
{
	private:
		int port;
		int SerSocket;
		static bool Signal;
		std::string Password;
		std::vector<Client> ClientsList;
		std::vector<struct epoll_event> events;
		int epollFd;
		struct sockaddr_in serverAddr;
	public:
		Server();
		~Server();
		void setPort(int port);
		int getPort();
		void setPassword(std::string password);
		std::string getPassword();
		void ServerInit();
		void ServerSocket();
		void AcceptNewClient();
		void ReceiveNewData(int fd);
		void menageData(char *buffer, int fd);
		static void SignalHandler(int signum);
		Client* getClient(int fd);	
		void execCommand(std::string command, std::string message, int fd);
		void CloseFds();
		void CloseClient(int fd);
};

#endif