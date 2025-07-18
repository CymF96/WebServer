/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <cofische@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:26:11 by cofische          #+#    #+#             */
/*   Updated: 2025/07/08 16:25:54 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERMANAGER_HPP
#define SERVERMANAGER_HPP

#include "Server.hpp"
#include "Socket.hpp"
#include "Client.hpp"
#include "HTTPResponse.hpp"
#include "HTTPRequest.hpp"


#define MAX_EVENTS 42
#define MAX_HEADER_SIZE 8192
#define MAX_URI_LENGTH 2048
#define EPOLL_TIMEOUT 10000
#define CLIENT_TIMEOUT 29

// typedef typename std::vector<Server*>::iterator Iterator;
class Server;
class Location;
class Client;
class Socket;
class HTTPRequest;
class HTTPResponse;

class ServerManager {
	public:
		ServerManager();
		ServerManager(const char* config_file);
		~ServerManager();

		void setHostPort();
		void setRunning(int is_running);
		void setHTTPRequest(HTTPRequest *request);
		void setHTTPResponse(HTTPResponse *response);
		
		std::vector<Server*> &getServers();
		std::map<std::string, std::string> &getIPPorts();
		std::vector<Socket*> &getSockets();
		std::vector<int> &getSocketsFD();
		std::map<int,Client*> &getClients();
		HTTPRequest *getHTTPRequest();
		HTTPResponse *getHTTPResponse();
		int getEpollFd();
		
		bool checkDuplicatePort(std::fstream &config_file);
		int	readFile(std::fstream &config_file);
		void parseServer(std::string &line, Server *current_server, std::fstream &config_file);
		void parseLocation(std::string &line, Server *current_server, std::fstream &config_file);
		int startSockets();
		int startEpoll();
		void serverMonitoring();
		void createNewClientConnection();
		void existingClientConnection();
		bool cleanClient(int current_fd);
		void shutdown();
		bool isBlocked(const void *IP);
		bool readClientHeaders();
		bool parseHeadersAndCheckBodySize();
		int readRequestBody(size_t content_length, size_t max_body_size);
		void processAndSendResponse(Server *server_requested, Location *location_requested);
		bool sendResponseBodyFile();
		void cleanHTTPElement(int current_fd_);
		void checkClientTimeouts();
		void send408ErrorResponse(int fd);

		
	private:
		std::vector<Server*> servers_list_;
		std::map<std::string, std::string> IP_ports_list_; // MAY NOT BE USEFUL AS WE GOT SERVER ID 
		std::vector<Socket*> sockets_list_;
		std::vector<int> sockets_fd_list_;
		std::string config_file_name_;
		bool running_;
		HTTPRequest* _http_request;
		HTTPResponse* _http_response;
		// Server *master_server_;

		/*EPOLL INSTANCE ATTRIBUTES*/
		int epoll_fd_;
		int num_events_;
		int current_fd_;
		struct epoll_event events_[MAX_EVENTS];
		std::string header_;
		std::string body_;
		int client_id_;

		/*CLIENT INFORMATION ATTRIBUTES*/
		struct sockaddr_storage temp_client_addr_;
		socklen_t temp_client_addr_len_;
		std::map<int,Client*> clients_list_;
		std::set<const void *> blocked_clients_list_;

		char received_[4096];
		char buffer_[8192];
		int error_code_;

};

size_t maxBodySizeLocation(Server *default_server, Server *server_requested, Location *location_requested);

#endif