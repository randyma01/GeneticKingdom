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


void Tower::setType(string type){
	this->type = type;
}

string Tower::getType(){
	return this->type;
}

int Tower::getDamage(){
	return damage;
}

void Tower::setDamage(int damage) {
	this->damage = damage;
}

int Tower::getLevel(){
	return level;
}

void Tower::setLevel(int level) {
	this->level = level;
}

int Tower::getScope(){
	return scope;
}

void Tower::setScope(int scope) {
	this->scope = scope;
}

int Tower::getTimeRecharge(){
	return timeRecharge;
}

void Tower::setTimeRecharge(int timeRecharge) {
	this->timeRecharge = timeRecharge;
}

int Tower::getTimeRegeneration(){
	return timeRegeneration;
}

void Tower::setTimeRegeneration(int timeRegeneration) {
	this->timeRegeneration = timeRegeneration;
}

int Tower::getVelocity(){
	return velocity;
}

void Tower::setVelocity(int velocity) {
	this->velocity = velocity;
}
