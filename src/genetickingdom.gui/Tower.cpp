/*
 * Tower.cpp
 *
 *  Created on: 17 oct. 2016
 *      Author: gustavo
 */

#include "Tower.h"

Tower::Tower() {
}

Tower::~Tower() {
}


void Tower::setType(string typeT){
	this->type = typeT;
}

void Tower::setNivel(int nivelT){
	this->nivel = nivelT;
}

string Tower::getType(){
	return this->type;
}

int Tower::getNivel(){
	return this->nivel;
}

