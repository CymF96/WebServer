/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <cofische@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:28:29 by cofische          #+#    #+#             */
/*   Updated: 2025/04/24 12:39:22 by cofische         ###   ########.fr       */
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
		std::string getHost();
		int getPort();
9
		int closeServer();
		
		
	private:
		//For configuration purpose
		int ID; //A unique identifer for the seerver instance
		std::string host; //hostname or IP address of the server. For example, it could be "127.0.0.1" or "localhost"
		int port;//**should be a array, because it can to montior more than 1 port; stores the port number on which the server listen for incoming connections.
		std::string errorDir; //check if final version as it may be a separate class 
		std::vector<std::string> serverNames; //store a list of serve names or alli
		int maxSize; //HTTP:: store the maximum size (in bytes) for the body of incoming HTTP request. 
		
		//location info
		std::vector<Location*> locations; 
		A location typically refers to specifc path or route on th server that has it own config.
		// For example:
		// 	api: A route for handling API requests.
		// 	static: Adiectory for serving static files like
		// The root directory for the route
		// Allowed HTTP methods (e.g. GET, POST).
		// Custom error pages for the route
		// Access permissions or restrictions
		// Location* apiLocation = new Location("/api", "/var/www/api", {"GET", "POST"});
		// locations.push_back(apiLocation);

		// Location* staticLocation = new Location("/static", "/var/www/static", {"GET"});
		// locations.push_back(staticLocation);	

		
		// For server setup
		int new_socket; 
		//**should be more than one???? usually one socket/one client*/
		//stores the file descriptor for
		//a newly acceopted client connection.
		//This returned by the accept() system call 
		//when a client connects to the server.
		// new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
		// if (new_socket < 0) {
		// 	std::cerr << "Error accepting connection" << std::endl;
		// }
	
		socklen_t addlen; 
		// socklen)t addlen is typically used to store the size of
		// a socket address structure, and in the context of your question,
		// it could indeed represent the size of a struct sockaddr_storage.

		// what is sockaddr_storage?
		// sockaddr_storage is generic generic structure designed to hold
		// socket address information for any protocol family (e.g. IPv4, IPv6).
		// before a system call like accept() or recvfrom():
		// addlen is initialized to the dize of the socket address 
		// structure being used (e.g., sizeof(sockaddr_storage)).
		// after the system call:
		// the kernel updates addlen to reflect the actual size of 
		// the address structure used.
		Socket mainSocket; //mainSocket is used to mange
};

std::ostream &operator<<(std::ostream &os, Server &server);
void printServer(Server &server); 

#endif

