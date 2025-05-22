/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receiveRequest.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:12:40 by ssottori          #+#    #+#             */
/*   Updated: 2025/05/14 17:49:52 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "receiveRequest.hpp"

RequestData::RequestData() {}

RequestData::RequestData(const RequestData& other) { *this = other; }

RequestData& RequestData::operator=(const RequestData& other)
{
	if (this != &other) {
		_method = other._method;
		_path = other._path;
		_queryString = other._queryString;
		_headers = other._headers;
		_body = other._body;
	}
	return *this;
}

RequestData::~RequestData() {}

RequestData::RequestData(const std::string& method,
					const std::string& path,
					const std::string& queryString,
					const std::map<std::string, std::string>& headers,
					const std::string& body)
					: _method(method), _path(path), _queryString(queryString), _headers(headers), _body(body) {}

//setters ======================================
void RequestData::setMethod(const std::string& method)
{
	_method = method;
}
void RequestData::setPath(const std::string& path)
{
	_path = path;
}
void RequestData::setQueryString(const std::string& queryString)
{
	_queryString = queryString;
}
void RequestData::setHeaders(const std::map<std::string, std::string>& headers)
{
	_headers = headers;
}
void RequestData::setBody(const std::string& body)
{
	_body = body;
}

//getters ======================================
const std::string& RequestData::getMethod() const
{
	return _method;
}

const std::string& RequestData::getPath() const
{
	return _path;
}

const std::string& RequestData::getQueryString() const
{
	return _queryString;
}

const std::map<std::string, std::string>& RequestData::getHeaders() const
{
	return _headers;
}

const std::string& RequestData::getBody() const
{
	return _body;
}
