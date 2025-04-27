/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <cofische@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:32:27 by cofische          #+#    #+#             */
/*   Updated: 2025/04/24 12:38:53 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/utils/Server.hpp"

/*CONSTRUCTORS/DESTRUCTORS*/
Server::Server(int inputID): Socket(), ID(inputID) {
	std::cout << BOLD YELLOW "Server is starting\nHELLO!\n" RESET;
	
	addlen = sizeof(this->getAddr());
	std::cout << ID << std::endl;
	// std::cout << "Socketfd in the server class:" << &this->getSocketfd() << ", Socket add:" << this->getAddr() << "\n";
	
	// launch();
	// closeServer();
}

Server::~Server() {
	std::cout << BOLD RED "Server is closing\nGOODBYE!\n" RESET;
}

/*SETTER FUNCTIONS*/

void Server::setHost(const std::string &inputHost) {
	host = inputHost;
};

void Server::setPort(int inputPort) {
	port = inputPort;
};

void Server::setErrorDir(const std::string &inputErrorDir) {
	errorDir = inputErrorDir;
};

void Server::addServerName(const std::string &inputName) {
	serverNames.push_back(inputName);
};

void Server::setMaxSize(int inputMaxSize) {
	maxSize = inputMaxSize;
};

/*GETTER FUNCTIONS*/

std::string Server::getHost() {
	return host;
};

int Server::getPort() {
	return port;
};

std::string Server::getErrorDir() {
	return errorDir;
};

std::string Server::getServerName() {
	return serverNames.front();
};

int Server::getMaxSize() {
	return maxSize;
};


/*METHOD*/
void Server::launch() {
	// while(true) {
		std::cout << "+++++++++ WAITING FOR CONNECTTION ++++++++++++++++++" << std::endl;
		if ((new_socket = accept(this->getSocketfd(), reinterpret_cast<sockaddr*>(this->getAddr()), &addlen)) < 0)
		{
			std::cout << "Error on accepting connection\n";
			return ;			
		}
		char buffer[30000] = {0};
		long valread = read(new_socket, buffer, 30000);
		std::cout << valread << std::endl << buffer << std::endl;
		close(new_socket);
	// }
}

int Server::closeServer() {
	close(this->getSocketfd());
	return 0;
}

int Server::getNewSocket() const {
	return new_socket;
}

void printServer(Server &server) {
	std::cout << BOLD BLUE << "server name: " << RESET << server.getServerName() << std::endl
	<< BOLD BLUE "server port: " << RESET << server.getPort() << std::endl
	<< BOLD BLUE "server host: " << RESET << server.getHost() << std::endl
	<< BOLD BLUE "server error dir: " << RESET << server.getErrorDir() << std::endl
	<< BOLD BLUE "server maxsize: " << RESET << server.getMaxSize() << std::endl;
}

std::ostream &operator<<(std::ostream &os, Server &server) {
	os << BOLD BLUE << "server name: " << RESET << server.getServerName() << std::endl
	<< BOLD BLUE "server port: " << RESET << server.getPort() << std::endl
	<< BOLD BLUE "server host: " << RESET << server.getHost() << std::endl
	<< BOLD BLUE "server error dir: " << RESET << server.getErrorDir() << std::endl
	<< BOLD BLUE "server maxsize: " << RESET << server.getMaxSize() << std::endl;
	return os;
};

