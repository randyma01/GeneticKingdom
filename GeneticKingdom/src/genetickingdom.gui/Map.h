/*
 * Map.h
 *
 *  Created on: 11 oct. 2016
 *      Author: gustavo
 */

#ifndef MAP_H_
#define MAP_H_

#include <iostream>
#include <stdio.h>
#include <string>
#include <allegro.h>


#include "Enemy.h"

#include "Player.h"
#include "Tower.h"
#include "Button.h"



//#define TILESIZE      40
#define TILES_ANCHO   22
#define TILES_ALTO    17



class Map {
public:
	Map();
	virtual ~Map();
	void drawMap();
	void drawTower();
	void updateMap();
	void initialize();


	void *enemyMove(void *parameter);

private:
	void initializeEnemys();
	void setMap(int i, int j);
	void drawTowerArchers();
	void drawTowerGunners();
	void drawTowerWizards();
	void drawPlayerStatistics();
	bool inSocopeTower();
	void attackTower();
	void setMapEnemy();

public:

	int TILESIZE;
	/*
	 * Screen
	 */
	BITMAP *buffer;
	BITMAP *grid;
	BITMAP *instructions;
	BITMAP *bufferPanel;
	BITMAP *playerStatistics;
	BITMAP *tiles;
	BITMAP *tiles1;
	BITMAP *tile_bridge;


	/*
	 * Enemys
	 */
	BITMAP *ogre;
	BITMAP *darkElf;
	BITMAP *harpy;
	BITMAP *mercenary;


	/*
	 * tomwer image
	 */
	BITMAP *towerArchersN1;
	BITMAP *towerArchersN2;
	BITMAP *towerArchersN3;
	BITMAP *towerGunnersN1;
	BITMAP *towerGunnersN2;
	BITMAP *towerGunnersN3;
	BITMAP *towerWizardsN1;
	BITMAP *towerWizardsN2;
	BITMAP *towerWizardsN3;

	BITMAP *drawTowerArc;
	BITMAP *drawTowerGun;
	BITMAP *drawTowerWiz;


	Tower towerMap;

	/*
	 * Map [21](i/y) [32](j/x)
	 *
	 */
	int map[17][22] = {
			{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,  2 },
			{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  2 },
			{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  2 },
			{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  2 },
			{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  2 },
			{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  2 },
			{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  2 },
			{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  2 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 11 },
			{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  2 },
			{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  2 },
			{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  2 },
			{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  2 },
			{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  2 },
			{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  2 },
			{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  2 },
			{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,  2 }
	};

	int mapEnemy[17][22] = {
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  5 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0 }
		};
	Tower mapTower[17][22] = {
			{ towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap },
			{ towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap },
			{ towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap },
			{ towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap },
			{ towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap },
			{ towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap },
			{ towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap },
			{ towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap },
			{ towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap },
			{ towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap },
			{ towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap },
			{ towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap },
			{ towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap },
			{ towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap },
			{ towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap },
			{ towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap },
			{ towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap, towerMap },
	};
};

#endif /* MAP_H_ */
