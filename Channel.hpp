/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:08:04 by micarrel          #+#    #+#             */
/*   Updated: 2024/10/02 13:08:04 by micarrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <vector>
#include "Client.hpp"
#include "Server.hpp"

class Channel
{
	private:
		std::string _name;
		std::vector<Client> _clients;
		std::string _topic;
		std::string _mode;
		std::string _password;
		bool _private;

	public:
		Channel();
		~Channel();
		void SetName(std::string name);
		std::string GetName();
		void SetTopic(std::string topic);
		std::string GetTopic();
		void SetMode(std::string mode);
		std::string GetMode();
		void SetPassword(std::string password, bool isPrivate);
		std::string GetPassword();
		void AddClient(Client client);
		void RemoveClient(Client client);
		std::vector<Client> GetClients();
};