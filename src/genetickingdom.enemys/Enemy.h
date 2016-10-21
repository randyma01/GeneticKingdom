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
#include <stdlib.h>
#include <string>
using namespace std;

class Enemy{
public:

	Enemy();
	Enemy(int aResistance, int mResistance, int arResistance, int speed, string name);
	virtual ~Enemy();


	void setName(string name){this->name = name;}
	void setArrowResistance(int arrowResistance){this->arrowResistance = arrowResistance;}
	void setMagicResistance(int magicResistance){this->magicResistance = magicResistance;}
	void setArtilleryResistance(int artilleryResistance){this->artilleryResistance = artilleryResistance ;}
	void setSpeed(int speed){this->speed = speed;}


	string getName(){ return name;}
	int getlife() {return life;}
	int getArrowResistance(){ return arrowResistance;}
	int getMagicResistance(){ return magicResistance;}
	int getArtilleryResistance(){ return artilleryResistance;}
	int getSpeed(){ return speed;}

	int move();
	void lowResistance();

public:
	string name;
	double life; //static
	int arrowResistance;
	int magicResistance;
	int artilleryResistance;
	int speed;


};
#endif /* ENEMY_H_ */
