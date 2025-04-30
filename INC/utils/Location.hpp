/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <cofische@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:36:56 by cofische          #+#    #+#             */
/*   Updated: 2025/04/29 10:22:07 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
#define LOCATION_HPP

#include "Webserv.hpp"

enum MET {
	GET,
	POST,
	DELETE
};

class Location {
	public:
		Location(const std::string &inputName);
		~Location();

		//SETTER//
		/***BASIC INFO***/
		void setRoot(const std::string &inputRoot);
		void setMethod(const std::string &inputMethod);
		void setIndex(const std::string &inputIndex);
		void setDirectories(bool inputAIndex);
		
		/***UPLOAD INFO***/
		void setUpload(bool inputUpload);
		void setUploadDir(const std::string &inputDir);
		void setMaxBodySize(size_t inputSize);

		/***CGI INFO***/
		void setCGI(bool inputCGI);
		void setCGIExt(const std::string &inputExt);

		/***REDIRECTION INFO***/		
		void setRedirect(bool inputRedirect);
		void setRedirectCode(int inputCode);
		void setRedirectURL(const std::string &inputURL);
		
		//GETTER//
		/***BASIC INFO***/
		std::string &getRoot();
		std::vector<MET> &getMethod();
		std::string &getIndex();
		bool getAutoIndex();
		std::string &getPath();
		
		/***UPLOAD INFO***/
		bool getUpload();
		std::string &getUploadDir();
		size_t getMaxSize();

		/***CGI INFO***/
		bool getCGI();
		std::vector<std::string> &getCGIExt();

		/***REDIRECTION INFO***/		
		bool getRedirect();
		int getRedirectCode();
		std::string &getRedirectURL();

		//METHOD//

	private:
		// Basic settings
		std::string pathPattern; 	// name will be used to find a matching path when server receive the HTTP request
		std::string root; 			// location of the folder
		std::vector<MET> method; 	// methods allow for this location
		std::string index; 			// set a default file to server when the request is for the directory
		bool directories; 			// set if directory is listed or not 

		// Upload settings
		bool upload_enable;			// Whether uploads are permitted
		std::string upload_store; 	// Directory where uploaded files are stored
		size_t max_body_size;		// Maximum upload size in bytes

		// CGI handling
		bool cgi_enabled; 			// Whether CGI is enabled for this location
		std::vector<std::string> cgi_extensions; // Map file extensions to handlers (.php -> php-cgi)

		// Redirection
		bool redirect_enable;		// Whether redirect is permitted or if automatically send an error
		int redirect_code;			// 301 ex, to identify where to redirect in case of file not found
		std::string redirect_url; 	// location of the redirect folder (ex Homepage)


		/************************************************/
		/***NOT MANDATORY -- TO COMPLETE LATER IF TIME***/
		/************************************************/
		/* Authentication
		bool auth_required;			// Basic auth required?
		std::string auth_type;		// "Basic", etc.
		std::string auth_user_file; // Path to credentials file
		*/
};

#endif