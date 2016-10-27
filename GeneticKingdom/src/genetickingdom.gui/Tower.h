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
	int level;
	int damage;
	int scope;
	int velocity;
	int timeRecharge;
	int timeRegeneration;

public:
	Tower();
	virtual ~Tower();

	void setType(string type);
	string getType();

	int getDamage();
	void setDamage(int damage);

	int getLevel();
	void setLevel(int level);

	int getScope();
	void setScope(int scope);

	int getTimeRecharge();
	void setTimeRecharge(int timeRecharge);

	int getTimeRegeneration();
	void setTimeRegeneration(int timeRegeneration);

	int getVelocity();
	void setVelocity(int velocity);
};

#endif /* TOWER_H_ */
