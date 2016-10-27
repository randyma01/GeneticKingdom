/*
 * Client.h
 *
 *  Created on: 10 oct. 2016
 *      Author: gustavo
 */

#ifndef CLIENT_H_
#define CLIENT_H_



#include <iostream>
#include <stdio.h>
#include <string>

#include <curl/curl.h>


using namespace std;

string data;

class Client {
public:

	Client();
	virtual ~Client();
	static size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up){
		//callback must have this declaration
	    //buf is a pointer to the data that curl has for us
	    //size*nmemb is the size of the buffer

		for (int c = 0; c<size*nmemb; c++)
		{
			data.push_back(buf[c]);
		}
		return size*nmemb; //tell curl how many bytes we handled
	}


};

#endif /* CLIENT_H_ */
