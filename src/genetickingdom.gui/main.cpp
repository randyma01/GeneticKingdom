/*
 * main.cpp
 *
 *  Created on: 6 oct. 2016
 *      Author: gustavo
 */

#include <iostream>
#include <stdio.h>
#include <string>
#include <curl/curl.h>


#include "Game.h"




int main(){

	Game game = Game();
	game.startGame();
    return 0;
}



