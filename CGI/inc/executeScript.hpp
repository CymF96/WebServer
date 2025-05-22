/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executeScript.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:27:11 by ssottori          #+#    #+#             */
/*   Updated: 2025/05/17 19:36:06 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
#include <map>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <cerrno>

#include "prepEnv.hpp"
#include "receiveRequest.hpp"
#include "receiveRequest.hpp"

class ScriptExecutor
{
	private:
		std::string _scriptPath;
		RequestData _request;
		std::string _response;
		int _pipe[2];

		char** createArgv() const;
		std::string getInterpreter() const;
		void runChild();
		std::string runParent(pid_t pid);
		void bodytoStdin(); //POST only
		void execveScript();
		bool createOutPipe();
		std::string errorResponse();

	public:
		ScriptExecutor(const std::string &scriptPath, const RequestData &request);
		~ScriptExecutor();

		std::string runScript();
};
