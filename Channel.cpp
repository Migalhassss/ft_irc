/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:08:03 by micarrel          #+#    #+#             */
/*   Updated: 2024/10/02 13:08:03 by micarrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel()
{
}

Channel::~Channel()
{
}

void Channel::SetName(std::string name)
{
	this->_name = name;
}

std::string Channel::GetName()
{
	return (this->_name);
}

void Channel::SetTopic(std::string topic)
{
	this->_topic = topic;
}

std::string Channel::GetTopic()
{
	return (this->_topic);
}

void Channel::SetMode(std::string mode)
{
	this->_mode = mode;
}

std::string Channel::GetMode()
{
	return (this->_mode);
}

void Channel::SetPassword(std::string password, bool isPrivate)
{
	this->_private = isPrivate;
	if (isPrivate)
		this->_password = password;
}

std::string Channel::GetPassword()
{
	return (this->_password);
}

void Channel::AddClient(Client client)
{
	this->_clients.push_back(client);
}

void Channel::RemoveClient(Client client)
{
	for (size_t i = 0; i < this->_clients.size(); i++)
	{
		if (this->_clients[i].GetFd() == client.GetFd())
		{
			this->_clients.erase(this->_clients.begin() + i);
			break;
		}
	}
}

