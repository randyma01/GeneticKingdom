/*
 * Factory.cpp
 *
 *  Created on: Oct 17, 2016
 *      Author: randy
 */


#include "Factory.h"



Factory::Factory() {
}

Factory::~Factory() {
}

Enemy Factory::makeEnemy(string newEnemyType){
	if (newEnemyType == "D"){
		return DarkElf();
	} else
	if (newEnemyType == "O"){
		return Ogres();
	}else
	if (newEnemyType == "H"){
		return Harpy();
	}else
	if (newEnemyType == "M"){
		return Mercenary();
	}
}

Enemy Factory::makeEnemyEvolved(string newEnemyType,int aResis, int mResis, int arResis, int speed, string name){
	if (newEnemyType == "D"){
		return  DarkElf(aResis, mResis, arResis, speed, name);
	} else
	if (newEnemyType == "O"){
		return Ogres(aResis, mResis, arResis, speed, name);
	}else
	if (newEnemyType == "H"){
		return Harpy(aResis, mResis, arResis, speed, name);
	}else
	if (newEnemyType == "M"){
		return Mercenary(aResis, mResis, arResis, speed, name);
	}
}


