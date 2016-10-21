/*
 * Enemy.cpp
 *
 *  Created on: Oct 17, 2016
 *      Author: randy
 */

#include "Enemy.h"

Enemy::Enemy() {

}

Enemy::Enemy(int aResistance, int mResistance, int arResistance, int speed, string name){
	this->arrowResistance = aResistance;
	this->magicResistance = mResistance;
	this->artilleryResistance = arResistance;
	this->speed = speed;
	this->name = name;
}

Enemy::~Enemy() {

}

