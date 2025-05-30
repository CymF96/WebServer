/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequest_copy.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuleung <chuleung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:18:48 by chuleung          #+#    #+#             */
/*   Updated: 2025/05/29 16:00:17 by chuleung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUEST_COPY_HPP
#define HTTPREQUEST_COPY_HPP

#include "Content_copy.hpp"

// METHOD PATH HTTP/VERSION
// Header1: Value1
// Header2: Value2
// ...
// Host: example.com

// [optional body data]
class Content;

struct Accept
{
	Accept(std::string type, std::string subtype, float piority);
	~Accept();

	static int global_index_; //dun know if it is useful
	int instance_index_;
	std::string type_;
	std::string subtype_;
	float piority_;

};

// struct Sec_Fetch
// {
//         std::string sec_fetch_dect_;
//         std::string sec_fetch_mode_;
//         std::string sec_fetch_site_;
//         std::string sec_fetch_user_;
// };




class HTTPRequest {
	public:
		HTTPRequest();
		virtual ~HTTPRequest();

		//Setters:
		void setMet(const std::string& method);
		void setContentFlag(const bool flag);
		void setBoundaryIndex(int index);
		void setIsInTheBodyFlag(const bool flag);
		void setCGIFlag(const bool flag);
		void setCGIType(const std::string cgi_type);
		void setPath(const std::string& path);
		void setVersion(const std::string& version);
		void setHost(std::string& host);
		void setUserAgent(const std::string& agent);
		void setAccept(const std::string& media_type);
		void setAcceptLanguage(const std::string& languages);
		void setAcceptEncoding(const std::string& encoding);
		void setConnection(const std::string& connection);
		// void setCookie(const std::string& version);
		void setReferer(const std::string& refer);
		void setAuthorization(const std::string& version);
		void setContent(const std::string& content);
		void setUnknown(const std::string& buffer);

		//Getters
		MET getMethod();
		bool getIsInTheBody();
		const std::string& getPath() const;
		const std::string& getVersion();
		const std::string& getHost() const;
		const std::map<std::string, std::string>& getUserAgent();
		const std::vector<Accept>& getAccept();
		const std::vector<std::string>& getAcceptEncoding();
		const std::map<std::string, float>& getAcceptLanguage();
		bool getConnection();
		const std::string& getReferer();
		const std::pair<std::string, std::string>& getAuthorisation();
		const Content& getContent();
		const std::map <std::string, std::string>& getUnknown();
		bool getCGIFlag();

		//Parser
		void parseContent(const std::string& body_line);
		void parseRequestHeader(std::istringstream& stream);
		void parseRequestLine(const std::string& request_line);
		void parseRequest(const std::string& request);

		//CGI
		std::string getMethodAsStr() const;
		std::string getQueryStr() const;
		std::string getRawBody() const;
		//std::string getcgiPath();
		std::map<std::string, std::string> getHeaders() const;



	private:
		static int global_index_; //dun know if it is useful
		int instance_index_;
		MET method_;

	// Common (GET, DELETE)
		std::string path_; // / //path/file.html
		std::string version_; //HTTP1.1
		std::string host_; //Host: example.com
		std::map<std::string, std::string> user_agent_; //User-Agent identifies the client software
		std::vector<Accept> accept_list_; //Accept: media types the client can process
		std::string referer_;
		std::map<std::string, float> accept_language_; //Accept-language:  en-US,en;q=0.5
		std::vector<std::string> accept_encoding_; //Accept-encoding: gzip, deflate, br, zstd
		bool connection_; // Connection: keep-alive
		// std::string cookie_; //Cookie: session=abc123; user=john
		
		// Sec_Fetch fetch_data_;
		std::vector<std::string> priority;
		std::pair<std::string, std::string> authorisation_; //Authorization: Bearer p@sswoRd

	// POST
		bool content_flag_;
		bool is_in_the_body_flag_;
		int boundary_index_;
		std::string cgi_type_;
		bool cgi_flag_;
		Content content_;
		std::map <std::string, std::string> unknown_; 

	// CGI
		std::string query_string_;
		std::map<std::string, std::string> headers_;  //map to store headers for cgi
	

};

#endif

//-1 0


//0 +1 1

//1 - 0