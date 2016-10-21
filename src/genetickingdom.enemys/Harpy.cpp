/*
 * Harpy.cpp
 *
 *  Created on: Oct 17, 2016
 *      Author: randy
 */

#include "Harpy.h"

Harpy::Harpy() {
	this->life = 6;
	this->speed = 5;
	this->arrowResistance = 5;
	this->magicResistance = 5;
	this->artilleryResistance = 10;
	this->name = "Harpy";
}


Harpy::Harpy(int aResistance, int mResistance, int arResistance, int speed, string name){
	this->arrowResistance = aResistance;
	this->magicResistance = mResistance;
	this->artilleryResistance = arResistance;
	this->speed = speed;
	this->name = name;
	this->life = 6;
}

Harpy::~Harpy() {
}

