/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   returnOutput.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 22:11:48 by ssottori          #+#    #+#             */
/*   Updated: 2025/05/18 00:44:26 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>
#include <sstream>

class ReturnOutput
{
	private:
		std::string _rawOutput;
		std::string _headerSection;
		std::string _body;
		std::map<std::string, std::string> _headers;
		void parseOutput();
		void parseHeaders();
		void splitHeaderBody();

	public:
		ReturnOutput(const std::string &output);
		std::string getBody() const;
		std::map<std::string, std::string> getHeaders() const;
};
