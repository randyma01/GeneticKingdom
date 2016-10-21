/*
 * Mercenary.h
 *
 *  Created on: Oct 17, 2016
 *      Author: randy
 */

#ifndef MERCENARY_H_
#define MERCENARY_H_

#include "Enemy.h"
using namespace std;

class Mercenary: public Enemy {
public:
	Mercenary();
	Mercenary(int aResistance, int mResistance, int arResistance, int speed, string name);
	virtual ~Mercenary();
};

#endif /* MERCENARY_H_ */
