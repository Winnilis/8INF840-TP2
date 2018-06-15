#include "Url.h"



Url::Url(){}

Url::Url(string _urlstr)
{
	this->url = _urlstr;

	string parser;
	stringstream ss(_urlstr);

	// parse beginning of the url
	getline(ss, this->scheme, ':');

	// remove "://"
	getline(ss, parser, '/');
	getline(ss, parser, '/');
	parser.clear();

	//parse authority
	getline(ss, parser, '/');
	this->authority = parser;

	stringstream ssAuth(parser);
	if (parser.find(':') != string::npos)
	{
		if (parser.find('@'))
			getline(ssAuth, this->userinfo, '@');
		
		getline(ssAuth, this->host, ':');
		getline(ssAuth, this->port, '/');

	}
	else {
		if (parser.find('@') != string::npos)
			getline(ssAuth, this->userinfo, '@');

		getline(ssAuth, this->host, '/');
	}

	
	// parse end of the url
	getline(ss, this->path, '?');
	getline(ss, this->query, '#');
	getline(ss, this->fragment, ' ');

	//TODO domain ??

}


Url::~Url(){}

string Url::toString()
{
	//return string("[" + scheme + "][" + userinfo + "][" + host + "][" + port + "][" + path +"][" + query + "][" + fragment + "]");
	return url;
}
