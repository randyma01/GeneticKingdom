/*
 * Harpy.h
 *
 *  Created on: Oct 17, 2016
 *      Author: randy
 */

#ifndef HARPY_H_
#define HARPY_H_

#include "Enemy.h"
using namespace std;

class Harpy: public Enemy {
public:
	Harpy();
	Harpy(int aResistance, int mResistance, int arResistance, int speed, string name);
	virtual ~Harpy();
};

#endif /* HARPY_H_ */
