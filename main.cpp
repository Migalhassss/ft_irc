/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:31:46 by micarrel          #+#    #+#             */
/*   Updated: 2024/10/01 13:31:46 by micarrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"

int main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cerr << "/IRCServer Port Password " << std::endl;
		return (1);
	}
	Server server;
	server.setPort(atoi(av[1]));
	server.setPassword(av[2]);
	try {
		signal(SIGINT, Server::SignalHandler); //-> catch signal (CTRL + C)
		signal(SIGQUIT, Server::SignalHandler); //-> catch signal (CTRL + \)
		server.ServerInit();
	}
	catch (std::exception &e) {
		server.CloseFds();
		std::cerr << e.what() << std::endl;
	}
	return (0);
}