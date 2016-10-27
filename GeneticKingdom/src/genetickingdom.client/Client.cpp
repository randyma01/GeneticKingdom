/*
 * Client.cpp
 *
 *  Created on: 10 oct. 2016
 *      Author: gustavo
 */

#include "Client.h"

Client::Client() {
	// TODO Auto-generated constructor stub
		/**
		 * Web Server
		 */

		FILE * wfp = fopen("parameter.xml", "w+");

		CURL *curl;
		curl_global_init(CURL_GLOBAL_ALL); //pretty obvious
		curl = curl_easy_init();
		curl_easy_setopt(curl, CURLOPT_URL, "http://172.26.108.188:9080/Server2/rest/hello/xml");


		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, wfp);
		//curl_easy_setopt(curl, CURLOPT_VERBOSE,1L);


		curl_easy_perform(curl);

		cout << "data: " << data << endl;
		cin.get();

	    curl_easy_cleanup(curl);
	    curl_global_cleanup();
}

Client::~Client() {
	// TODO Auto-generated destructor stub
}

