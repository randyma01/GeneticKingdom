/*
 * GUI.h
 *
 *  Created on: 10 oct. 2016
 *      Author: gustavo
 */

#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <stdio.h>
#include <string>
#include <allegro.h>


#include "Map.h"
#include "Button.h"




class Game {
public:
	Game();
	virtual ~Game();
	void mover(int d);
	void iniciar();
	void startGame();
	void viewAbout();

	Map map;
	SAMPLE *sound;
	BITMAP *buffer;
	BITMAP *buffer1;
	BITMAP *background;
	BITMAP *about;

	const int point[24] = {
					350, 0,
					360, 15,
					370, 0,
					375, 5,
					365, 20,
					375, 35,
					370, 40,
					360, 25,
					350, 40,
					345, 35,
					355, 20,
					345, 5
		};

};




#endif /* GAME_H_ */
