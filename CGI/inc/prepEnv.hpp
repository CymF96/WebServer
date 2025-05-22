/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepEnv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:44:08 by ssottori          #+#    #+#             */
/*   Updated: 2025/05/14 17:54:52 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PREPENV_HPP
#define PREPENV_HPP

#include <cstdlib> // for getenv
#include <cstring> // for strdup
#include <vector>
#include <map> //env vars
#include <string>
#include "receiveRequest.hpp"

//Envbuilder is going to ""translate all the data received.
//It is responsible for turning the request infor into proper CGI env variables
//which are passed to the script via "execve"

class EnvBuilder
{
	private:
		std::map<std::string, std::string> _env;
		void initFromRequest(const RequestData& request);

	public:
		EnvBuilder();
		EnvBuilder(const RequestData& request);
		EnvBuilder(const EnvBuilder& other);
		EnvBuilder& operator=(const EnvBuilder& other);
		~EnvBuilder();

		std::map<std::string, std::string> getEnvMap() const;
		char** buildEnvArray() const;
		void freeEnvArray(char** env) const;
};

#endif
