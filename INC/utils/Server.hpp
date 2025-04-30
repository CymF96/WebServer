/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <cofische@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:28:29 by cofische          #+#    #+#             */
/*   Updated: 2025/04/29 11:25:53 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "Webserv.hpp"
#include "Socket.hpp"
#include "Location.hpp"

class Location;
class Errors;

class Server {
	public:
		Server(int inputID);
		~Server();
	
		//SETTER//
		void setHost(const std::string &inputHost);
		void setPort(int inputPort);
		void setErrorDir(const std::string &inputErrorDir);
		void addServerName(const std::string &inputName);
		void setMaxSize(int inputMaxSize);
		void addLocation(const std::string &inputLocation);

		//GETTER//
		std::string &getHost();
		int getPort();
		std::map<int, std::string> &getErrorDir();
		std::vector<std::string> &getServerName();
		int getMaxSize();
		std::vector<Location*> &getLocation();
		
		//METHOD//
		int getNewSocket() const;
		void launch();
		int closeServer();
		
		
	private:
		// Config settings
		int ID;
		std::string host;
		int port;
		std::vector<std::string> serverNames;
		int maxSize;

		// error_pages settings
		std::map<int, std::string> errors_list;
		
		// location settings
		std::vector<Location*> locations;
		
		// socket settings
		// int new_socket;
		// socklen_t addlen;
		// Socket mainSocket;
};

void printServer(Server &server); 

#endif