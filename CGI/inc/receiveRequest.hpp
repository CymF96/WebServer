/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receiveRequest.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:40:39 by ssottori          #+#    #+#             */
/*   Updated: 2025/05/17 22:01:12 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#pragma once

#ifndef RECEIVEREQUEST_HPP
# define RECEIVEREQUEST_HPP

#include <map> //for env vars
#include <string>

//This class is responsible for:
//Holding the raw input from the HTTP request (method, path, body, headers, etc.)
//Providing accessors so the rest of your CGI program can read that info easily

class RequestData
{
	private:
		std::string _method;
		std::string _path;
		std::string _queryString;
		std::map<std::string, std::string> _headers;
		std::string _body;

	public:
		RequestData();
		RequestData(const RequestData& other);
		RequestData& operator=(const RequestData& other);
		~RequestData();
		RequestData(const std::string& method,
					const std::string& path,
					const std::string& queryString,
					const std::map<std::string, std::string>& headers,
					const std::string& body);
		
		//setters
		void setMethod(const std::string& method);
		void setPath(const std::string& path);
		void setQueryString(const std::string& queryString);
		void setHeaders(const std::map<std::string, std::string>& headers);
		void setBody(const std::string& body);

		//getters
		const std::string& getMethod() const;
		const std::string& getPath() const;
		const std::string& getQueryString() const;
		const std::map<std::string, std::string>& getHeaders() const;
		const std::string& getBody() const;
};

#endif
