/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <cofische@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:37:06 by cofische          #+#    #+#             */
/*   Updated: 2025/04/29 10:22:26 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/utils/Location.hpp"

/************************/
/*CONSTRUCTOR/DESTRUCTOR*/
/************************/

Location::Location(const std::string &inputPath) : pathPattern(inputPath), directories(false), upload_enable(false),
cgi_enabled(false), redirect_enable(false) {
	upload_store = "";
	max_body_size = 0;
	redirect_code = -1;
	redirect_url = "";
};
Location::~Location() {};

/********/
/*SETTER*/
/********/

/*******BASIC INFO********/
void Location::setRoot(const std::string &inputRoot) {
	root = inputRoot;
};
void Location::setMethod(const std::string &inputMethod) {
	std::stringstream ss(inputMethod);
	std::string token;
	while (std::getline(ss, token, ' ')) {
		if (token == "GET")
			method.push_back(GET);
		else if (token == "POST")
			method.push_back(POST);
		else if (token == "DELETE")
			method.push_back(DELETE);
	}
};
void Location::setIndex(const std::string &inputIndex) {
	index = inputIndex;
};
void Location::setDirectories(bool inputAIndex) {
	directories = inputAIndex;
};

/*******UPLOAD INFO********/
void Location::setUpload(bool inputUpload) {
	upload_enable = inputUpload;
};
void Location::setUploadDir(const std::string &inputDir) {
	upload_store = inputDir;
};
void Location::setMaxBodySize(size_t inputSize) {
	max_body_size = inputSize;
};

/*******CGI INFO********/
void Location::setCGI(bool inputCGI) {
	cgi_enabled = inputCGI;
};
void Location::setCGIExt(const std::string &inputExt) {
	std::stringstream ss(inputExt);
	std::string token;

	while (std::getline(ss, token, ' ')) {
    	cgi_extensions.push_back(token);
	}
};

/*******REDIRECT INFO********/
void Location::setRedirect(bool inputRedirect) {
	redirect_enable = inputRedirect;
};
void Location::setRedirectCode(int inputCode) {
	redirect_code = inputCode;
};
void Location::setRedirectURL(const std::string &inputURL) {
	redirect_url = inputURL;
};

/********/
/*GETTER*/
/********/

/*******BASIC INFO********/
std::string &Location::getRoot() {
	return root;
};
std::vector<MET> &Location::getMethod() {
	return method;
};
std::string &Location::getIndex() {
	return index;
};
bool Location::getAutoIndex() {
	return directories;
};
std::string &Location::getPath() {
	return pathPattern;
};

/*******UPLOAD INFO********/
bool Location::getUpload() {
	return upload_enable;
};
std::string &Location::getUploadDir() {
	return upload_store;
};
size_t Location::getMaxSize() {
	return max_body_size;
};

/*******CGI INFO********/
bool Location::getCGI() {
	return cgi_enabled;
};
std::vector<std::string> &Location::getCGIExt() {
	return cgi_extensions;
};

/*******REDIRECT INFO********/
bool Location::getRedirect() {
	return redirect_enable;
};
int Location::getRedirectCode() {
	return redirect_code;
};
std::string &Location::getRedirectURL() {
	return redirect_url;
};

/********/
/*METHOD*/
/********/
