/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuleung <chuleung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:32:27 by cofische          #+#    #+#             */
/*   Updated: 2025/04/30 16:46:25 by chuleung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/utils/Server.hpp"

/************************/
/*CONSTRUCTOR/DESTRUCTOR*/
/************************/

Server::Server(int inputID): ID(inputID), keep_alive(false) {
	// std::cout << BOLD YELLOW "Server is starting\nHELLO!\n" RESET;
	
	//As error page must be default if none are given in config file --> add a default error-page setup when creating server and erase if error are id

	
	// addlen = sizeof(this->getAddr());
	// std::cout << "Socketfd in the server class:" << &this->getSocketfd() << ", Socket add:" << this->getAddr() << "\n";
	
	// launch();
	// closeServer();
};
Server::~Server() {
	// std::cout << BOLD RED "Server is closing\nGOODBYE!\n" RESET;
};

/********/
/*SETTER*/
/********/

void Server::setHost(const std::string &inputHost) {
	host = inputHost;
};
void Server::setPort(const std::string &inputPort) {
	std::stringstream ss(inputPort);
	std::string token;

	while (std::getline(ss, token, ' ')) {
    	port.push_back(token);
	}
};
void Server::setErrorDir(const std::string &inputErrorDir) {
	std::stringstream ss(inputErrorDir);
	std::string directory;
	int code;
	char space;
	if (inputErrorDir.find("default") != std::string::npos) {
		code = 0;
		std::string garbage;
		ss >> garbage >> space >> directory;
	} else
		ss >> code >> space >> directory;
	errors_list.insert(std::pair<int, std::string>(code, directory));	
};
void Server::addServerName(const std::string &inputName) {
	std::stringstream ss(inputName);
	std::string token;

	while (std::getline(ss, token, ' ')) {
    	serverNames.push_back(token);
	}
};
void Server::setMaxSize(int inputMaxSize) {
	maxSize = inputMaxSize;
};
void Server::addLocation(const std::string &inputLocation) {
	locations.push_back(new Location(inputLocation));
};
void Server::setKeepAlive(bool inputAlive) {
	keep_alive = inputAlive;	
};

/********/
/*GETTER*/
/********/

std::string &Server::getHost() {
	return host;
};
std::vector<std::string> &Server::getPort() {
	return port;
};
std::map<int,std::string> &Server::getErrorDir() {
	return errors_list;
};
std::vector<std::string> &Server::getServerName() {
	return serverNames;
};
int Server::getMaxSize() {
	return maxSize;
};
std::vector<Location*> &Server::getLocation() {
	return locations;
};
bool Server::getKeepAlive() {
	return keep_alive;	
};


/********/
/*METHOD*/
/********/

// void Server::launch() {
// 	// while(true) {
// 		// std::cout << "+++++++++ WAITING FOR CONNECTTION ++++++++++++++++++" << std::endl;
// 		// if ((new_socket = accept(this->getSocketfd(), reinterpret_cast<sockaddr*>(this->getAddr()), &addlen)) < 0)
// 		// {
// 		// 	std::cout << "Error on accepting connection\n";
// 		// 	return ;			
// 		// }
// 		// char buffer[30000] = {0};
// 		// long valread = read(new_socket, buffer, 30000);
// 		// std::cout << valread << std::endl << buffer << std::endl;
// 		// close(new_socket);
// 	// }
// }

// int Server::closeServer() {
// 	close(this->getSocketfd());
// 	return 0;
// }

// int Server::getNewSocket() const {
// 	return new_socket;
// }

