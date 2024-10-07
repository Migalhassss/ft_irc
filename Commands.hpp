/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:35:50 by micarrel          #+#    #+#             */
/*   Updated: 2024/10/01 17:35:50 by micarrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
#define COMMANDS_HPP

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
#include "Client.hpp"
#include "Server.hpp"

void		execCommand(std::string command, std::string message, int fd);
Client*		getClient(Server *server, int const client_fd);
std::string	trimNewline(std::string str);
void		nickCommand(Client *client);
void		userCommand(Client *client);
void		joinCommand(Client *client);

#endif