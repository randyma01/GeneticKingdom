/*
 * Ogres.h
 *
 *  Created on: Oct 17, 2016
 *      Author: randy
 */

#ifndef OGRES_H_
#define OGRES_H_

#include "Enemy.h"
using namespace std;

class Ogres: public Enemy {
public:
	Ogres();
	Ogres(int aResistance, int mResistance, int arResistance, int speed, string name);
	virtual ~Ogres();
};

#endif /* OGRES_H_ */
