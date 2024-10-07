/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:35:53 by micarrel          #+#    #+#             */
/*   Updated: 2024/10/01 17:35:53 by micarrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "Client.hpp"
#include "Server.hpp"

void joinCommand(Client *client)
{
	std::string message = client->GetMessage();
	if (client->GetNickname().empty()) {
		std::string sendmsg = ":server 451 : You have not registered\r\n";
		send (client->GetFd(), sendmsg.c_str(), sendmsg.length(), 0);
		return;
	}
	
}

void userCommand(Client *client)
{
	std::cout << "Client nick is" << client->GetNickname() << std::endl;
	std::string sendmsg = "Welcome to the server " + client->GetNickname() + "!";
	send (client->GetFd(), sendmsg.c_str(), sendmsg.length(), 0);
}

void nickCommand(Client *client)
{
	client->SetNickname(client->GetMessage());
	std::string message = client->GetMessage();
	std::cout << "Client <" << client->GetFd() << "> changed nickname to \"" << message << "\"" << std::endl;
}

std::string trimNewline(std::string str) {
	if (!str.empty() && str[str.length() - 1] == '\n') {
		str.erase(str.length() - 1);
	}
	return str;
}
