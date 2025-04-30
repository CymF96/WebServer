/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuleung <chuleung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:28:29 by cofische          #+#    #+#             */
/*   Updated: 2025/04/30 17:05:52 by chuleung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "Webserv.hpp"
#include "Location.hpp"

class Location;
class Errors;

class Server {
	public:
		Server(int inputID);
		~Server();
	
		//SETTER//
		void setHost(const std::string &inputHost);
		void setPort(const std::string &inputPort);
		void setErrorDir(const std::string &inputErrorDir);
		void addServerName(const std::string &inputName);
		void setMaxSize(int inputMaxSize);
		void addLocation(const std::string &inputLocation);
		void setKeepAlive(bool inputAlive);

		//GETTER//
		std::string &getHost();
		std::vector<std::string> &getPort();
		std::map<int, std::string> &getErrorDir();
		std::vector<std::string> &getServerName();
		int getMaxSize();
		std::vector<Location*> &getLocation();
		bool getKeepAlive();
		
		//METHOD//
		int getNewSocket() const;
		void launch();
		int closeServer();
		
		
	private:
		// Config settings
		int ID;
		std::string host;
		std::vector<std::string> port;
		std::vector<std::string> serverNames;
		int maxSize;
		bool keep_alive;

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