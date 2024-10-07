/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:33:52 by micarrel          #+#    #+#             */
/*   Updated: 2024/10/01 13:33:52 by micarrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client()
{
}

Client::~Client()
{
}

void Client::SetMessage(std::string message)
{
	this->_message = message;
}

std::string Client::GetMessage()
{
	return (this->_message);
}

void Client::SetNickname(std::string nickname)
{
	this->_nickname = nickname;
}

void Client::SetUsername(std::string username)
{
	this->_username = username;
}

void Client::SetHost(std::string host)
{
	this->_host = host;
}


std::string Client::GetNickname()
{
	return (this->_nickname);
}

std::string Client::GetUsername()
{
	return (this->_username);
}

std::string Client::GetHost()
{
	return (this->_host);
}

void Client::SetIp(std::string ip)
{
	this->_ip = ip;
}

void Client::SetFd(int fd)
{
	this->_fd = fd;
}

void Client::SetPort(int port)
{
	this->_port = port;
}

std::string Client::GetIp()
{
	return (this->_ip);
}

int Client::GetFd()
{
	return (this->_fd);
}

int Client::GetPort()
{
	return (this->_port);
}
