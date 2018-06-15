#pragma once
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class Url
{
	string url;

	string scheme;
	string authority;
	string path;
	string query;
	string fragment;

	string userinfo;
	string host;
	string port;

	string domain;

public:
	Url();
	Url(string _urlstr);
	~Url();

	string getUrl() { return url; }
	string getScheme() { return scheme; }
	string getAuthority() { return authority; }
	string getPath() { return path; }
	string getQuery() { return query; }
	string getFragment() { return fragment; }

	string getUserinfo() { return userinfo; };
	string getHost() { return host; }
	string getPort() { return port; }

	string getDomain() { return domain; }

	string toString();
};

