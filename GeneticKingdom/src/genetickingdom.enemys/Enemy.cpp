/*
 * Enemy.cpp
 *
 *  Created on: Oct 17, 2016
 *      Author: randy
 */

#include "Enemy.h"


bool UP     =  false;
bool DOWN   =  false;
bool LEFT   =  false;
bool RIGHT  =  false;

int dirX = 0;
int dirY = 0;
int dir_X = 0;
int dir_Y = 0;

int velocidadEnemy = 8;


Enemy::Enemy(){};

Enemy::Enemy(int aResistance, int mResistance, int arResistance, int speed, string name, int tilesize, BITMAP *buffer){
	this->arrowResistance = aResistance;
	this->magicResistance = mResistance;
	this->artilleryResistance = arResistance;
	this->speed = speed;
	this->name = name;

	this->px = 0;
	this->py = tilesize*8;
	this->TILESIZE = tilesize;
	this->px_current = 0;
	this->py_current = 8;
	this->buffer = buffer;
	if (name == "O"){
		enemy = load_bitmap("genetickingdom.gui/resources/ogreR1.bmp", NULL);
	}//else if (name == "D"){

//	}
	else if (name == "H"){
		enemy = load_bitmap("genetickingdom.gui/resources/harpyR1.bmp", NULL);
	}//else if (name == "M"){

	//}
	stretch_blit(enemy, enemy, 0, 0, enemy->w, enemy->h, 0, 0, TILESIZE, TILESIZE);
	masked_blit(enemy, buffer, 0, 0, px_current, py_current * TILESIZE, TILESIZE, TILESIZE);
	blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}

Enemy::~Enemy() {}




void Enemy::drawEnemy(){

	//clear_to_color(buffer, 0xFFFFFF);
	//set_trans_blender(255, 0, 255, 240);
	//draw_trans_sprite(buffer, enemy, px, py_current*TILESIZE);
	//mapa.updateMap();
	if (RIGHT){
		if (dirX%2 == 0){
			if (name == "O"){
				enemy = load_bitmap("genetickingdom.gui/resources/ogreR1.bmp", NULL);
			}else if (name == "D"){

			}else if (name == "H"){
				enemy = load_bitmap("genetickingdom.gui/resources/harpyR1.bmp", NULL);
			}else if (name == "M"){

			}
			stretch_blit(enemy, enemy, 0, 0, enemy->w, enemy->h, 0, 0, TILESIZE, TILESIZE);
			masked_blit(enemy, buffer, 0, 0, px, py, TILESIZE, TILESIZE);
			blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
			rest(50);
			vsync();
		}
		else{
			if (name == "O"){
				enemy = load_bitmap("genetickingdom.gui/resources/ogreR2.bmp", NULL);
			}else if (name == "D"){

			}else if (name == "H"){
				enemy = load_bitmap("genetickingdom.gui/resources/harpyR1.bmp", NULL);
			}else if (name == "M"){

			}
			stretch_blit(enemy, enemy, 0, 0, enemy->w, enemy->h, 0, 0, TILESIZE, TILESIZE);
			masked_blit(enemy, buffer, 0, 0, px, py, TILESIZE, TILESIZE);
			blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
			rest(50);
			vsync();
		}
	}
	if (DOWN){
		if (dirY%2 == 0){
			if (name == "O"){
				enemy = load_bitmap("genetickingdom.gui/resources/ogreD1.bmp", NULL);
			}else if (name == "D"){

			}else if (name == "H"){
				enemy = load_bitmap("genetickingdom.gui/resources/harpyR1.bmp", NULL);
			}else if (name == "M"){

			}
			stretch_blit(enemy, enemy, 0, 0, enemy->w, enemy->h, 0, 0, TILESIZE, TILESIZE);
			masked_blit(enemy, buffer, 0, 0, px, py, TILESIZE, TILESIZE);
			blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
			rest(50);
			vsync();
		}
		else{
			if (name == "O"){
				enemy = load_bitmap("genetickingdom.gui/resources/ogreD2.bmp", NULL);
			}else if (name == "D"){

			}else if (name == "H"){
				enemy = load_bitmap("genetickingdom.gui/resources/harpyR1.bmp", NULL);
			}else if (name == "M"){

			}
			stretch_blit(enemy, enemy, 0, 0, enemy->w, enemy->h, 0, 0, TILESIZE, TILESIZE);
			masked_blit(enemy, buffer, 0, 0, px, py, TILESIZE, TILESIZE);
			blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
			rest(50);
			vsync();
		}
	}
	if (UP){
		if (dir_Y%2 == 0){
			if (name == "O"){
				enemy = load_bitmap("genetickingdom.gui/resources/ogreU1.bmp", NULL);
			}else if (name == "D"){

			}else if (name == "H"){
				enemy = load_bitmap("genetickingdom.gui/resources/harpyR1.bmp", NULL);
			}else if (name == "M"){

			}
			stretch_blit(enemy, enemy, 0, 0, enemy->w, enemy->h, 0, 0, TILESIZE, TILESIZE);
			masked_blit(enemy, buffer, 0, 0, px, py, TILESIZE, TILESIZE);
			blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
			rest(50);
			vsync();
		}
		else{
			if (name == "O"){
				enemy = load_bitmap("genetickingdom.gui/resources/ogreU2.bmp", NULL);
			}else if (name == "D"){

			}else if (name == "H"){
				enemy = load_bitmap("genetickingdom.gui/resources/harpyR1.bmp", NULL);
			}else if (name == "M"){

			}
			stretch_blit(enemy, enemy, 0, 0, enemy->w, enemy->h, 0, 0, TILESIZE, TILESIZE);
			masked_blit(enemy, buffer, 0, 0, px, py, TILESIZE, TILESIZE);
			blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
			rest(50);
			vsync();
		}
	}
	if (LEFT){
		if (dir_X%2 == 0){
		}
		else{
		}
	}


}

void Enemy::startEnemy(int map[I][J]){
	//puede avanzar en x
	//while(true){
		if (map[py_current][px_current + 1] == 1 && UP == false && DOWN == false){
			RIGHT = true;
			UP = false;
			DOWN = false;
			LEFT = false;
			moveEnemy();
			drawEnemy();
		}
		//puede avanzar en y si ya no hay avance en x, ni retroceso en y
		if (map[py_current + 1][px_current] == 1 && UP == false && RIGHT == false){
			DOWN = true;
			UP = false;
			RIGHT = false;
			LEFT = false;
			moveEnemy();
			drawEnemy();
		}
		//puede retroceder en x
		if (map[py_current][px_current - 1] == 1){

			}
		//puede retroceder en y i ya no hay avance en x, ni en y
		if (map[py_current - 1][px_current] == 1  && DOWN == false && RIGHT == false){
			UP = true;
			DOWN = false;
			RIGHT = false;
			LEFT = false;
			//map[py_current][px_current] = 0;
			moveEnemy();
			drawEnemy();
		}
		/*
		if (map[py_current][px_current + 1] == 5){
		break;
		}
		*/
		else{
			DOWN = false;
			UP = false;
			RIGHT = false;
			LEFT = false;
		}
	//}
}

void Enemy::moveEnemy(){
	//mueve el enemigo
		if (RIGHT){
			px += TILESIZE/speed;
			dirX += 1;
			if ((px%TILESIZE) == 0){
				px_current = px/TILESIZE;
			}
		}
		if (DOWN){
			py += TILESIZE/speed;
			dirY += 1;
			if ((py%TILESIZE) == 0){
				py_current = py/TILESIZE;
			}
		}
		if (LEFT){
			px -= TILESIZE/speed;
			dir_X += 1;
			if ((px%TILESIZE) != px && (px%TILESIZE) >= 0){
				px_current = px/TILESIZE;
			}
		}
		if (UP){
			py -= TILESIZE/speed;
			dir_Y += 1;
			if ((py%TILESIZE) == 0){
				py_current = py/TILESIZE;
			}
		}
}
