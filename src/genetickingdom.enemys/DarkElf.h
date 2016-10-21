/*
 * DarkElf.h
 *
 *  Created on: Oct 18, 2016
 *      Author: randy
 */

#ifndef GENETICKINGDOM_ENEMYS_DARKELF_H_
#define GENETICKINGDOM_ENEMYS_DARKELF_H_

#include "Enemy.h"
using namespace std;

class DarkElf: public Enemy {
public:
	DarkElf();
	DarkElf(int aResistance, int mResistance, int arResistance, int speed, string name);
	virtual ~DarkElf();
};

#endif /* GENETICKINGDOM_ENEMYS_DARKELF_H_ */
