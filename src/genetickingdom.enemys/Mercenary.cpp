/*
 * Mercenary.cpp
 *
 *  Created on: Oct 17, 2016
 *      Author: randy
 */

#include "Mercenary.h"

Mercenary::Mercenary() {
	this->life = 6;
	this->speed = 5;
	this->arrowResistance = 7;
	this->magicResistance = 3;
	this->artilleryResistance = 7;
	this->name = "Mercenary";
}


Mercenary::Mercenary(int aResistance, int mResistance, int arResistance, int speed, string name){
	this->arrowResistance = aResistance;
	this->magicResistance = mResistance;
	this->artilleryResistance = arResistance;
	this->speed = speed;
	this->name = name;
	this->life = 6;
}
Mercenary::~Mercenary() {

}

