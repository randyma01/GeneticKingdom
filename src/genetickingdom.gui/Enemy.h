/*
 * Enemy.h
 *
 *  Created on: 17 oct. 2016
 *      Author: gustavo
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#include <iostream>
#include <stdio.h>
#include <string>
#include <allegro.h>

#define I 17
#define J 22


class Enemy {
public:
	Enemy();
	Enemy(int TILESIZEe, BITMAP *buffer, BITMAP *enemy);
	virtual ~Enemy();
	void startEnemy(int map[I][J]);
	void drawEnemy();
	int	px_current;
	int	py_current;
	int px;
	int	py;

protected:
	int TILESIZE;
	BITMAP *enemy;
	BITMAP *buffer;
	BITMAP *bufferEnemy;
	void moveEnemy();
};

#endif /* ENEMY_H_ */
