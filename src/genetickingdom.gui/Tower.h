/*
 * Tower.h
 *
 *  Created on: 17 oct. 2016
 *      Author: gustavo
 */

#ifndef TOWER_H_
#define TOWER_H_

#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

class Tower {

protected:
	string type;
	int nivel;

public:
	Tower();
	virtual ~Tower();
	void setType(string type);
	void setNivel(int nivel);
	string getType();
	int getNivel();
};

#endif /* TOWER_H_ */
