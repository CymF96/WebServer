/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <cofische@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:26:00 by cofische          #+#    #+#             */
/*   Updated: 2025/04/30 15:44:57 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

bool server_flag = false;

#include "../INC/utils/ServerManager.hpp"

/************************/
/*CONSTRUCTOR/DESTRUCTOR*/
/************************/

ServerManager::ServerManager(const std::string &inputFilename) {
	std::cout << BOLD RED "Starting MasterServer\n" RESET;
	std::fstream configFile(inputFilename.c_str());
	readFile(configFile);
	setHostPort();
	startSockets();
	//check on error of the config file (ex: incorrect format, missing essential elements) 
	// --> can be place before the call of the object in main ??
	// --> Write an information on how to write a config file for our server (README.md?)

	/********DEBUGGING*********/
	//Printing the server object to ensure they are well connected	
	// std::vector<Server*>::iterator beg = servers.begin();
	// std::vector<Server*>::iterator end = servers.end();
	// for (; beg != end; ++beg)
	// 	printServer(**beg);
	// std::cout << "\n\n";
	std::map<std::string, std::string>::iterator start = host_port.begin();
	std::map<std::string, std::string>::iterator finish = host_port.end();
	for (; start != finish; ++start) {	
		std::cout << start->first << " " << start->second << std::endl; 
	}
	
	// std::cout << line << std::endl;
	/********DEBUGGING*********/
	
	//start epoll for listening
	
	//stop epoll
	
	//clear all the resources

}

ServerManager::~ServerManager() {
	std::cout << BOLD RED "Closing MasterServer\n" RESET;
}

/********/
/*SETTER*/
/********/


void ServerManager::setHostPort() {
	std::vector<Server*>::iterator start = servers.begin();
	std::vector<Server*>::iterator end = servers.end();
	for (; start != end; ++start) {
		if (*start != NULL) {
			std::vector<std::string>::iterator port_beg = (*start)->getPort().begin();
			std::vector<std::string>::iterator port_end = (*start)->getPort().end();
			for (; port_beg != port_end; ++port_beg) {
				host_port.insert(std::pair<std::string, std::string>(*port_beg, (*start)->getHost()));
			}
		} else
			return ;
	}
}

/********/
/*GETTER*/
/********/

std::vector<Server*> &ServerManager::getServers() {
	return servers;
};
// std::map<int, std::string> &ServerManager::getHostPort() {
// 	return host_port;
// };
std::vector<Socket*> &ServerManager::getSocket() {
	return sockets;
};


/********/
/*METHOD*/
/********/

/****************/
/* READFILE purpose is to read each line of the configFile and initiate a new Server Object when needed */
/****************/
int	ServerManager::readFile(std::fstream &configFile) {
	Server *currentServer =  NULL;
	std::string line;
	int serverCount = 1000; //Set an ID for new servers (MAY NOT BE USEFUL?)
	if (configFile.is_open()) {
		while (std::getline(configFile, line)) {
			// std::cout << line << std::endl;
			if (line.find("server {") != std::string::npos || server_flag == true) {				
				servers.push_back(new Server(serverCount++)); // newServerObj will return a pointer to a new Server object that is created
				currentServer = servers.back();
				server_flag = false;
				// create a new server object that will parse each line in a sub ServerConfig object.
			} else {
				parseServer(line, currentServer, configFile);
			}
		}
		configFile.close();
	} else {
		std::cout << BOLD RED "file incorrect\n" RESET;
	}
	return 0;
}


/****************/
/* PARSESERVER purpose is to parse information in the current server structure (like host, port, etc...)*/
/* if a location word is found, it call parseLocation to create an fill in Location object*/
/****************/
void ServerManager::parseServer(std::string &line, Server *currentServer, std::fstream &configFile) {
	size_t pos = 0;
	if (line.find("host") != std::string::npos) {
		if ((pos = line.rfind(":")) != std::string::npos)
			currentServer->setHost(line.substr(pos + 2));
	} else if (line.find("port") != std::string::npos) {
		if ((pos = line.rfind(":")) != std::string::npos)
			currentServer->setPort(line.substr(pos + 2));
	} else if (line.find("server_name") != std::string::npos) {
		if ((pos = line.rfind(":")) != std::string::npos)
			currentServer->addServerName(line.substr(pos + 2));
	} else if (line.find("error_pages") != std::string::npos) {
		while (std::getline(configFile, line) && line.find("}") == std::string::npos) {
			currentServer->setErrorDir(line);	
		}
	} else if (line.find("keep_alive") != std::string::npos) {
		if (line.find("on") != std::string::npos)
			currentServer->setKeepAlive(true);
	} else if (line.find("client_max_body_size") != std::string::npos) { // limit for the HTTP request body info
		if ((pos = line.rfind(":")) != std::string::npos) {
			std::string newLine = line.substr(pos + 2);
			newLine.erase(newLine.end() - 1);
			currentServer->setMaxSize(convertInt(newLine));
		}
	} else if (line.find("location") != std::string::npos) {
		parseLocation(line, currentServer, configFile);
		if (line.find("server") != std::string::npos)
			server_flag = true;
	} else
		return; // PRINTING ERROR AS UNKNOW CONFIG ELEMENT FOUND
}

/****************/
/* PARSELOCATION purpose is to initiate a new Location object in the current server object when needed or,*/
/* if already in the location block, just parse information in the location structure (like root, index, cgi_enable, etc...)*/
/****************/
void ServerManager::parseLocation(std::string &line, Server *currentServer, std::fstream &configFile) {
	size_t pos;
	std::string name;
	Location *currentLocation = NULL;
	if ((pos = line.rfind("/")) != std::string::npos)
		name = line.substr(pos);
	name.erase(name.end() - 1);
	currentServer->addLocation(name);
	currentLocation = currentServer->getLocation().back();
			//////////////////////////////////
	while (std::getline(configFile, line) && line.find("server") == std::string::npos) {
		if (line.find("location") != std::string::npos) {
			if ((pos = line.rfind(":")) != std::string::npos)
				name = line.substr(pos);
			currentServer->addLocation(name);
			currentLocation = currentServer->getLocation().back();
		} else if (line.find("method") != std::string::npos) {
			if ((pos = line.rfind(":")) != std::string::npos)
				currentLocation->setMethod(line.substr(pos + 2));
		} else if (line.find("root") != std::string::npos) {
			if ((pos = line.rfind(":")) != std::string::npos)
				currentLocation->setRoot(line.substr(pos + 2));
		} else if (line.find("index") != std::string::npos) {
			if ((pos = line.rfind(":")) != std::string::npos)
				currentLocation->setIndex(line.substr(pos + 2));
		} else if (line.find("directories") != std::string::npos) {
			if (line.find("on") != std::string::npos)
				currentLocation->setDirectories(true);
				//////////////////////////////////
		} else if (line.find("upload:") != std::string::npos) {
			if (line.find("on") != std::string::npos)
				currentLocation->setUpload(true);
		} else if (line.find("upload_store") != std::string::npos) {
			if ((pos = line.rfind(":")) != std::string::npos)
				currentLocation->setUploadDir(line.substr(pos + 2));
		} else if (line.find("max_body_size") != std::string::npos) {
			if ((pos = line.rfind(":")) != std::string::npos) {
				std::string newLine = line.substr(pos + 2);
				newLine.erase(newLine.end() - 1);
				currentLocation->setMaxBodySize(static_cast<size_t>(convertInt(newLine)));
			}
				/////////////////////////////////
		} else if (line.find("cgi:") != std::string::npos) {
			if (line.find("on") != std::string::npos)
				currentLocation->setCGI(true);
		} else if (line.find("cgi_extensions") != std::string::npos) {
			if ((pos = line.rfind(":")) != std::string::npos)
				currentLocation->setCGIExt(line.substr(pos + 2));	
				/////////////////////////////////
		} else if (line.find("redirect:") != std::string::npos) {
			if (line.find("on") != std::string::npos)
				currentLocation->setRedirect(true);
		} else if (line.find("redirect_code") != std::string::npos) { // do I need a redirect code or can I simply redirect to a default webpage?
			if ((pos = line.rfind(":")) != std::string::npos)
				currentLocation->setRedirectCode(convertInt(line.substr(pos + 2)));
		} else if (line.find("redirect_url") != std::string::npos) {
			if ((pos = line.find(":")) != std::string::npos)
				currentLocation->setRedirectURL(line.substr(pos + 2));
		} else if (line.find("}") != std::string::npos)
			;
		else
			return; // PRINTING ERROR AS UNKNOW CONFIG ELEMENT FOUND
	}	
}

/****************/
/* StartSockets purpose is to initiate the socket_fd per unique host:port combination that are saved in the attribute host_port*/
/* Each of the socket_fd will start a Socket object that will test the IP address, bind it and start listening*/
/****************/
void ServerManager::startSockets() {
	std::map<std::string, std::string>::iterator beg = host_port.begin();
	std::map<std::string, std::string>::iterator end = host_port.end();
	for (; beg != end; ++beg) {
		sockets.push_back(new Socket(beg->second, beg->first));	
	}

	// Now we got a vector that has all the socket_fd active and ready to listen. We are able to start the epoll after this function
}