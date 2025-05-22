/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executeScript.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:26:00 by ssottori          #+#    #+#             */
/*   Updated: 2025/05/22 16:20:33 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executeScript.hpp"

ScriptExecutor::ScriptExecutor(const std::string &scriptPath, const RequestData &request) : _scriptPath(scriptPath), _request(request) {}

ScriptExecutor::~ScriptExecutor() {}

std::string ScriptExecutor::runScript()
{
	if (!createOutPipe())
		return errorResponse();
	
	pid_t pid = fork();
	if (pid < 0)
		return errorResponse();
	if (pid == 0)
		runChild();
	else
		return runParent(pid);
	
	return errorResponse();
}

bool ScriptExecutor::createOutPipe()
{
	return pipe(_pipe) == 0;
}

char** ScriptExecutor::createArgv() const
{
	char **av = new char*[3];
	std::string interpreter = getInterpreter();
	av[0] = new char[interpreter.size() + 1];
	std::strcpy(av[0], interpreter.c_str());
	av[1] = new char[_scriptPath.size() + 1];
	std::strcpy(av[1], _scriptPath.c_str());
//-
	return av;
}

void ScriptExecutor::runChild()
{
	dup2(_pipe[1], STDOUT_FILENO); // redirect stdout to pipe
	close(_pipe[0]);
	close(_pipe[1]);

	if (_request.getMethod() == "POST") {
		bodytoStdin(); // handles input + exec
	} else {
		execveScript();
	}

	std::cerr << "Execve failed\n";
	_exit(1);
}

std::string ScriptExecutor::runParent(pid_t pid)
{
	close(_pipe[1]);

	char buff[4096];
	size_t bytesRead;
	while ((bytesRead = read(_pipe[0], buff, sizeof(buff) - 1)) > 0)
	{
		buff[bytesRead] = '\0';
		_response += buff;
	}

	close(_pipe[0]);
	waitpid(pid, NULL, 0);
	return _response;
}

void ScriptExecutor::execveScript()
{
	EnvBuilder envBuilder(_request);
	char** envp = envBuilder.buildEnvArray();
	char** av = createArgv();
	execve(av[0], av, envp);
	std::cerr << "execve failed: " << strerror(errno) << std::endl;
	envBuilder.freeEnvArray(envp);
	///might need to delete?? if i dinamically allocate av
	_exit(1);
}

std::string ScriptExecutor::errorResponse()
{
	return "Status: 500 Internal Server Error\n\n";
}

std::string ScriptExecutor::getInterpreter() const
{
	size_t dot = _scriptPath.rfind('.');
	if (dot == std::string::npos)
		return "";

	std::string ext = _scriptPath.substr(dot);

	if (ext == ".py")
		return "/usr/bin/python3";
	if (ext == ".sh")
		return "/bin/bash";
	return "";
}

void ScriptExecutor::bodytoStdin() // only for POST
{
	int pfd[2];
	if (pipe(pfd) == -1)
	{
		std::cerr << "Failed to create pipe for stdin redirection.\n";
		_exit(1);
	}
	pid_t pid = fork();
	if (pid < 0)
	{
		std::cerr << "Fork failed in ---> bodytoStdin.\n";
		_exit(1);
	}
	if (pid == 0)
	{
		// Child: redirect stdin
		close(pfd[1]);
		dup2(pfd[0], STDIN_FILENO);
		close(pfd[0]);
		execveScript(); //running the scripppttt
		_exit(1);
	}
	else
	{
		// Parent: write body to child
		close(pfd[0]); // close read end
		std::string body = _request.getBody();
		write(pfd[1], body.c_str(), body.size());
		close(pfd[1]);
		waitpid(pid, NULL, 0);
	}
}
