/*
 * Ogres.cpp
 *
 *  Created on: Oct 17, 2016
 *      Author: randy
 */

#include "Ogres.h"

Ogres::Ogres() {
	this->life = 5;
	this->speed = 2;
	this->arrowResistance = 7;
	this->magicResistance = 3;
	this->artilleryResistance = 3;
	this->name = "Ogre";

}

Ogres::Ogres(int aResistance, int mResistance, int arResistance, int speed, string name){
	this->arrowResistance = aResistance;
	this->magicResistance = mResistance;
	this->artilleryResistance = arResistance;
	this->speed = speed;
	this->name = name;
	this->life = 5;
}

Ogres::~Ogres() {
}

