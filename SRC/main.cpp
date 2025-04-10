/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <cofische@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:48:24 by cofische          #+#    #+#             */
/*   Updated: 2025/04/10 14:05:13 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/MasterHeader.hpp"

// int main(int ac, char **av) {
// 	if (ac > 2) {
// 		std::cerr << "ERROR\n";
// 		return (-1);
// 	}
// 	std::string filename;
// 	if (ac < 1)
// 		filename = "../configuration/default.conf";
// 	else
// 		filename = av[1];
// 	//Start the ServerManager Object that will handle all the HTTP connections
// 	ServerManager masterServer(filename);

// 	return 0;
// }

int main() {
	std::string line = "\thost: 127.0.0.1";
	std::string host;
	size_t pos;
	if (line.find("host") != std::string::npos) {
		if ((pos = line.rfind(":")) != std::string::npos)
			host = line.substr(pos + 2);
	}
	std::cout << line << "\n" << host << std::endl;
}