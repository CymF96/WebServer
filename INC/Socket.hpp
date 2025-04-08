/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <cofische@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:08:06 by cofische          #+#    #+#             */
/*   Updated: 2025/04/08 09:36:03 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
#define SOCKET_HPP

#include "WebServer.hpp"

/*
struct sockaddr_in 
{ 
	__uint8_t         sin_len; 
	sa_family_t       sin_family; 
	in_port_t         sin_port; 
	struct in_addr    sin_addr; 
	char              sin_zero[8]; 
};
*/

class Socket {
	public:
		Socket();
		Socket(int domain, int type, int protocol, int port, int backlog);
		~Socket();

		int getSocketfd() const ;
		struct sockaddr_in *getAddr();
		// void setSocketfd();
		
		class SOCKERROR: public std::exception {
			private:
				const char *message;
			public:
				SOCKERROR(const char *msg);
				virtual const char *what() const throw();
		};
		
	private:
		int socketfd;
		struct sockaddr_in add;
		
		
		
};

#endif