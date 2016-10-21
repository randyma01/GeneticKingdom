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



class Game {
public:
	Game();
	virtual ~Game();
	void mover(int d);
	void iniciar();
	void startGame();

};




#endif /* GAME_H_ */
