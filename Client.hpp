/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:04:35 by micarrel          #+#    #+#             */
/*   Updated: 2024/10/01 12:04:35 by micarrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <vector> //-> for vector
#include <sys/socket.h> //-> for socket()
#include <sys/types.h> //-> for socket()
#include <netinet/in.h> //-> for sockaddr_in
#include <fcntl.h> //-> for fcntl()
#include <unistd.h> //-> for close()
#include <arpa/inet.h> //-> for inet_ntoa()
#include <poll.h> //-> for poll()
#include <csignal> //-> for signal()
#include <cerrno>
#include <cstring>

class Client
{
	private:
		std::string _ip;
		int _fd;
		int _port;
		std::string _nickname;
		std::string _username;
		std::string _host;
		std::string _message;
		bool authenticated;
	public:
		Client();
		~Client();
		void SetIp(std::string ip);
		void SetFd(int fd);
		void SetPort(int port);
		std::string GetIp();
		int GetFd();
		int GetPort();
		void SetNickname(std::string nickname);
		void SetUsername(std::string username);
		void SetMessage(std::string message);
		void SetHost(std::string host);
		std::string GetNickname();
		std::string GetUsername();
		std::string GetMessage();
		std::string GetHost();

};

#endif

