/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <cofische@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:26:11 by cofische          #+#    #+#             */
/*   Updated: 2025/04/30 14:44:47 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERMANAGER_HPP
#define SERVERMANAGER_HPP

#include "Webserv.hpp"
#include "Server.hpp"

// typedef typename std::vector<Server*>::iterator Iterator;

class ServerManager {
	public:
		ServerManager(const std::string &inputFilename);
		~ServerManager();
		
		int	readFile(std::fstream &configFile);
		void parseServer(std::string &line, Server *currentServer, std::fstream &configFile);
		void parseLocation(std::string &line, Server *currentServer, std::fstream &configFile);
		// void setHostPort();
		// void ServerManager::startSockets();

		std::vector<Server*> &getServers();
		std::map<int, std::string> &getHostPort();
		std::vector<Socket*> &getSocket();
		
	private:
		std::vector<Server*> servers;
		std::map<int, std::string> host_port; // MAY NOT BE USEFUL AS WE GOT SERVER ID 
		std::vector<Socket*> sockets;
		// adding a vector that will keep track of the socket fd of each server ? 
		// Servermanager will be in charge of the epoll management
		
		

};


#endif