/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <cofische@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:54:18 by cofische          #+#    #+#             */
/*   Updated: 2025/06/04 18:25:55 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Webserv.hpp"

class Client {
	public:
		Client(int inputClientFd, struct sockaddr_storage &inputClientAddr, socklen_t inputClientAddrLen);
		~Client();

		int getClientFd();
		const void* getClientIP();
		uint16_t getClientPort();
		struct sockaddr_storage &getClientAddr();
		socklen_t getClientAddrLen();
		bool getError();
		
	private:
		bool error_;
		int client_fd_;
		struct sockaddr_storage client_addr_;
		socklen_t client_addr_len_;
		int flags_;
		char ip_str_[INET6_ADDRSTRLEN];
		const void *ip_;
		uint16_t port_;
};

#endif