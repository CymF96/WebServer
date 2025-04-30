/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <cofische@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:48:24 by cofische          #+#    #+#             */
/*   Updated: 2025/04/28 14:32:36 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/MasterHeader.hpp"

int main(int ac, char **av) {
	if (ac > 2) {
		std::cerr << "ERROR\n";
		return (-1);
	}
	std::string filename;
	if (ac > 1) {
		filename = av[1];
	} else
		filename = "configuration/default.conf";
	//Start the ServerManager Object that will handle all the HTTP connections
	ServerManager masterServer(filename);

	return 0;
}

/**************************/
/********DEBUGGING*********/
/**************************/

// #include <string>
// #include <iostream>

// int main() {
// 	size_t pos;
// 	std::string name;
// 	std::string line = "location /api-back:";
// 	if (line.find("location") != std::string::npos) {
// 		if ((pos = line.rfind('/')) != std::string::npos)
// 			name = line.substr(pos);
// 		std::cout << "name before change: " << name << "\n";
// 		name.erase(name.end() - 1);
// 		std::cout << "name after change: " << name << "\n";
// 	}
// }
