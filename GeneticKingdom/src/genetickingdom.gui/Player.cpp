/*
 * Player.cpp
 *
 *  Created on: 16 oct. 2016
 *      Author: gustavo
 */

#include "Player.h"


Player::Player() {
	gold = 8000;
}

Player::~Player() {
}

void Player::setGold(int amount){
	gold += amount;
}

int Player::getGold(){
	return gold;
}

