/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <cofische@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:28:29 by cofische          #+#    #+#             */
/*   Updated: 2025/04/10 13:28:35 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "Webserv.hpp"
#include "Socket.hpp"
#include "Location.hpp"


class Server : public Socket{
	public:
		Server(int inputID);
		~Server();
	
		//setter functions
		void setHost(const std::string &inputHost);
		void setPort(int inputPort);
		void setErrorDir(const std::string &inputErrorDir);
		void addServerName(const std::string &inputName);
		void setMaxSize(int inputMaxSize);
		/*Add something for the Location object as locatino will be parsed in several lines*/

		
		int getNewSocket() const;
		void launch();
		int closeServer();
		
	private:
		//For configuration purpose
		int ID;
		std::string host;
		int port;
		std::string errorDir; //check if final version as it may be a separate class 
		std::vector<std::string> serverNames;
		int maxSize;
		
		//location info
		std::vector<Location*> locations;
		
		// For server setup
		int new_socket;
		socklen_t addlen;
		Socket mainSocket;
};

#endif