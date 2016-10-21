/*
 * Factory.h
 *
 *  Created on: Oct 17, 2016
 *      Author: randy
 */

#ifndef FACTORY_H_
#define FACTORY_H_

#include "Enemy.h"
#include "DarkElf.h"
#include "Harpy.h"
#include "Mercenary.h"
#include "Ogres.h"

using namespace std;

class Factory {
public:
	Factory();
	Enemy makeEnemy(string newEnemyType);
	Enemy makeEnemyEvolved(string newEnemyType,int aResis, int mResis, int arResis, int speed, string name);
	virtual ~Factory();

protected:
	DarkElf darkElf;

};

#endif /* FACTORY_H_ */
