/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <cofische@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:26:11 by cofische          #+#    #+#             */
/*   Updated: 2025/04/10 12:27:49 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERMANAGER_HPP
#define SERVERMANAGER_HPP

#include "Webserv.hpp"
#include "Server.hpp"

class ServerManager {
	public:
		ServerManager(const std::string &inputFilename);
		~ServerManager();
		
		int	readFile(std::fstream &configFile);
		void parseLine(std::string &line, Server *currentServer);
		
	private:
		std::vector<Server*> servers;
		// adding a vector that will keep track of the socket fd of each server ? 
		// Servermanager will be in charge of the epoll management
		
		

};


#endif