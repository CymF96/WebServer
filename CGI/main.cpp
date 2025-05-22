/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 20:57:59 by ssottori          #+#    #+#             */
/*   Updated: 2025/05/22 16:28:38 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executeScript.hpp"
#include "receiveRequest.hpp"
#include "prepEnv.hpp"
#include <iostream>

void testEnvMap(std::map<std::string, std::string> headers)
{
	//testing CGI environment variable map
	//RequestData request("POST", "./www/cgi-bin/totally_not_a_virus.py", "download=yes", headers, "screaming=internally&chaos=100%");
	RequestData request("GET", "./www/cgi-bin/totally_not_a_virus.py", "download=yes", headers, "screaming=internally&chaos=100%");

	EnvBuilder envBuilder(request);
	char** envp = envBuilder.buildEnvArray();

	std::cout << "== CGI ENVIRONMENT VARIABLES ==" << std::endl;
	for (size_t i = 0; envp[i]; ++i)
		std::cout << envp[i] << std::endl;

	envBuilder.freeEnvArray(envp);
}

void testingExecutor(std::map<std::string, std::string> headers)
{
	RequestData request("GET", "./cgi-bin/test.py", "", headers, "");
	//RequestData request("POST", "./cgi-bin/test.py", "", headers, "birthday=13-11");
	ScriptExecutor executor("./cgi-bin/test.py", request);

	std::string output = executor.runScript();
	std::cout << "[CGI OUTPUT] ===\n" << output << std::endl;
}

int main() {
	std::map<std::string, std::string> headers;
	headers["Content-Type"] = "application/testing-cgi-modules";
	headers["Content-Length"] = "42";

	testEnvMap(headers);
	//testingExecutor(headers);

	return 0;
}
