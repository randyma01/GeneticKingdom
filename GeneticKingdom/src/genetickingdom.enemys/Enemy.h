/*
 * Enemy.h
 *
 *  Created on: Oct 17, 2016
 *      Author: randy
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#include <iostream>
#include <stdio.h>
#include <string>

#include <allegro.h>


#define I 17
#define J 22


using namespace std;

class Enemy{
public:
	Enemy();
	Enemy(int aResistance, int mResistance, int arResistance, int speed, string name, int tilesize, BITMAP *buffer);
	virtual ~Enemy();
	void startEnemy(int map[I][J]);
	void setTB(int tilesize, BITMAP *buffer);

public:
	int	px_current;
	int	py_current;
	int px;
	int	py;

	string name;
	double life; //static
	int arrowResistance;
	int magicResistance;
	int artilleryResistance;
	int speed;

	int TILESIZE;
	BITMAP *buffer;

	BITMAP *enemy;
	void moveEnemy();
	void drawEnemy();



};
#endif /* ENEMY_H_ */
