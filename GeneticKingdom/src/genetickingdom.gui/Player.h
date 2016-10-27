/*
 * Player.h
 *
 *  Created on: 16 oct. 2016
 *      Author: gustavo
 */

#ifndef PLAYER_H_
#define PLAYER_H_

class Player {

public:
	int gold;

public:
	Player();
	virtual ~Player();
	void setGold(int amount);
	int getGold();
};

#endif /* PLAYER_H_ */
