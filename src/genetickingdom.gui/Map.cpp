/*
 * Map.cpp
 *
 *  Created on: 11 oct. 2016
 *      Author: gustavo
 */

#include "Map.h"
#include "Player.h"
#include "Tower.h"
#include "Enemy.h"
#include "Button.h"


bool inScope = false;

int TILESIZE;
bool clickOptions = false;
extern volatile int mouse_x;
extern volatile int mouse_y;
extern volatile int mouse_b;
extern volatile int mouse_pos;

Player player = Player();
int costArcN1 = 50;
int costArcN2 = 100;
int costArcN3 = 200;

int costWizN1 = 150;
int costWizN2 = 230;
int costWizN3 = 350;

int costGunN1 = 250;
int costGunN2 = 400;
int costGunN3 = 600;

int ii;
int jj;

Enemy enemyOgre = Enemy();


int scope;

FONT *f;

Map::Map(){}

Map::~Map(){}

void Map::initialize(){
	int w, h;
	get_desktop_resolution(&w, &h);
	TILESIZE = (h / 17)+1;
	scope = 1 * TILESIZE;
	std::cout << TILESIZE << std::endl;
	set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, w, h, 0, 0);
	select_mouse_cursor(MOUSE_CURSOR_ALLEGRO);
	show_mouse(screen);
	enable_triple_buffer();

	/*
	 * Screen
	 */
	buffer = create_bitmap(SCREEN_W, SCREEN_H);
	grid = create_bitmap(TILES_ANCHO * TILESIZE, TILES_ALTO * TILESIZE);
	bufferPanel = create_bitmap(SCREEN_W, SCREEN_H);
	tiles = load_bitmap("resources/tiles.bmp", NULL);
	tiles1 = load_bitmap("resources/tiles1.bmp", NULL);
	tile_bridge = load_bitmap("resources/bridge.bmp", NULL);


	/*
	 * Enemys
	 */

	ogre = load_bitmap("resources/ogreR1.bmp",NULL);


	/*
	 * Towers
	 */
	towerArchersN1 = load_bitmap("resources/towerArcN1.bmp", NULL);
	towerArchersN2 = load_bitmap("resources/towerArcN2.bmp", NULL);
	towerArchersN3 = load_bitmap("resources/towerArcN3.bmp", NULL);

	towerGunnersN1 = load_bitmap("resources/towerGunN1.bmp", NULL);
	towerGunnersN2 = load_bitmap("resources/towerGunN2.bmp", NULL);
	towerGunnersN3 = load_bitmap("resources/towerGunN3.bmp", NULL);

	towerWizardsN1 = load_bitmap("resources/towerWizN1.bmp", NULL);
	towerWizardsN2 = load_bitmap("resources/towerWizN2.bmp", NULL);
	towerWizardsN3 = load_bitmap("resources/towerWizN3.bmp", NULL);

	drawTowerArc = load_bitmap("resources/TwArchers.bmp", NULL);
	drawTowerGun = load_bitmap("resources/TwGunners.bmp", NULL);
	drawTowerWiz = load_bitmap("resources/TwWizards.bmp", NULL);

}


void Map::drawMap(){


	initialize();
	enemyOgre = Enemy(TILESIZE, buffer, ogre);
	/*
	 * Bucle principal
	 */
	while(!key[KEY_ESC]){
		drawTower();
		drawPlayerStatistics();
		blit(bufferPanel, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		blit(grid, buffer, 0, 0, 0, 0, TILES_ANCHO * TILESIZE, TILES_ALTO * TILESIZE);
		/*for(int i = 0; i <= 17; i++){
			for(int j = 0; j <= 22; j++){
				if (map[i][j] == 1 && map[i][j] != 0){
					//blit(tiles, grid, tiles->w-TILESIZE ,tiles->h-TILESIZE,j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
					//stretch_blit(tiles, grid, 0, 0, tiles->w, tiles->h, j *TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
					stretch_sprite(grid, tiles, j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
				}if (map[i][j] == 2 && map[i][j] != 0) {
					//blit(tiles1, grid, 0 ,0 ,j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
					stretch_sprite(grid, tiles1, j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
					//stretch_blit(tiles1, grid, 0, 0, tiles1->w, tiles1->h, j *TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
				}if (map[i][j] == 11){
					stretch_sprite(grid, tile_bridge, j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
				}
			}
		}*/
		updateMap();
		//stretch_blit(ogre, buffer, 0, 0, ogre->w, ogre->h, px_array *TILESIZE, py_array * TILESIZE, TILESIZE, TILESIZE);
		textprintf(buffer, font, TILES_ANCHO*TILESIZE + 4, 10, palette_color[14], "Oro disponible: %d", player.getGold());
		textout(buffer , font, "Costo: 50",
				TILES_ANCHO * TILESIZE + TILESIZE, 100+TILESIZE+20+2, palette_color[14]);
		textout(buffer , font, "Costo: 250",
				TILES_ANCHO * TILESIZE + (2*TILESIZE+30), 100+TILESIZE+20+2, palette_color[14]);
		textout(buffer , font, "Costo: 150",
				TILES_ANCHO * TILESIZE + (3*TILESIZE+75), 100+TILESIZE+20+2, palette_color[14]);


		//mover enemigo
		if (key[KEY_ENTER]){
			while(true){
				enemyOgre.startEnemy(mapEnemy);
				inSocopeTower();
				attackTower();
				updateMap();
				if (mapEnemy[enemyOgre.py_current][enemyOgre.px_current+1] == 5){
					enemyOgre = Enemy(TILESIZE, buffer, ogre);
					setMapEnemy();
					break;
				}
				if (key[KEY_Q]){
					break;
				}
			}
			//enemyOgre.drawEnemy();
		}
		acquire_screen();
		blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		release_screen();
		rest(5);
	}
}

void Map::setMapEnemy(){
	mapEnemy[12][7] = 1;
	mapEnemy[11][7] = 1;
	mapEnemy[10][7] = 1;
	mapEnemy[9][7] = 1;
	mapEnemy[8][7] = 1;
	mapEnemy[7][7] = 1;
	mapEnemy[6][7] = 1;
	mapEnemy[5][7] = 1;
	mapEnemy[4][7] = 1;
	mapEnemy[3][7] = 1;

}

void Map::drawTower(){
	stretch_sprite(bufferPanel, drawTowerArc, TILES_ANCHO * TILESIZE + TILESIZE, 100, TILESIZE+20, TILESIZE+20);
	stretch_sprite(bufferPanel, drawTowerGun, TILES_ANCHO * TILESIZE + (2*TILESIZE+30), 100, TILESIZE+20, TILESIZE+20);
	stretch_sprite(bufferPanel, drawTowerWiz, TILES_ANCHO * TILESIZE + (3*TILESIZE+60), 100, TILESIZE+20, TILESIZE+20);

	if (mouse_b & 2){
		int pos_mouse = mouse_pos;
		mouse_x = pos_mouse >> 16;
		mouse_y = pos_mouse & 0x0000ffff;
		instructions = create_bitmap(SCREEN_W - (TILES_ANCHO * TILESIZE), 100);
		if (!clickOptions){
			//crear torre Arqueros
			if (mouse_x >= TILES_ANCHO * TILESIZE + TILESIZE && mouse_x <= TILES_ANCHO * TILESIZE + TILESIZE + TILESIZE+20
					&& mouse_y >= 100 && mouse_y <= 100 + TILESIZE+20){
				clickOptions = true;
				if(clickOptions && costArcN1 <= player.getGold()){
					textout(instructions , font, "Presione click izquierdo en el mapa",
							instructions->x_ofs, instructions->y_ofs+5, palette_color[12]);
					textout(instructions , font, "para crear una torre de Arqueros!",
							instructions->x_ofs, instructions->y_ofs+25, palette_color[12]);
					textout(instructions , font, "Q para cancelar",
							instructions->x_ofs, instructions->y_ofs+50, palette_color[12]);
					blit(instructions, buffer, 0, 0, TILES_ANCHO * TILESIZE+2, 135 + TILESIZE+20, SCREEN_W - (TILES_ANCHO * TILESIZE), 100);
					blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
					drawTowerArchers();
					vsync();
				}
				else{
					textout(instructions , font, "No hay suficiente oro",
							instructions->x_ofs, instructions->y_ofs+5, palette_color[12]);
					blit(instructions, buffer, 0, 0, TILES_ANCHO * TILESIZE+2, 135 + TILESIZE+20, SCREEN_W - (TILES_ANCHO * TILESIZE), 100);
					blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
					rest(2000);
					clickOptions = false;
				}
			}
			//crear torre Artilleros
			if (mouse_x >= TILES_ANCHO * TILESIZE + (2*TILESIZE+30) && mouse_x <= TILES_ANCHO * TILESIZE + (2*TILESIZE+30) + TILESIZE+20
					&& mouse_y >= 100 && mouse_y <= 100 + TILESIZE+20){
				clickOptions = true;
				if(clickOptions && costGunN1 <= player.getGold()){
					textout(instructions , font, "Presione click izquierdo en el mapa",
							instructions->x_ofs, instructions->y_ofs+5, palette_color[12]);
					textout(instructions , font, "para crear una torre de Artilleros!",
							instructions->x_ofs, instructions->y_ofs+25, palette_color[12]);
					textout(instructions , font, "Q para cancelar",
							instructions->x_ofs, instructions->y_ofs+50, palette_color[12]);
					blit(instructions, buffer, 0, 0, TILES_ANCHO * TILESIZE+2, 135 + TILESIZE+20, SCREEN_W - (TILES_ANCHO * TILESIZE), 100);
					blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
					drawTowerGunners();
					vsync();
				}
				else{
					textout(instructions , font, "No hay suficiente oro",
							instructions->x_ofs, instructions->y_ofs+5, palette_color[12]);
					blit(instructions, buffer, 0, 0, TILES_ANCHO * TILESIZE+2, 135 + TILESIZE+20, SCREEN_W - (TILES_ANCHO * TILESIZE), 100);
					blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
					rest(2000);
					clickOptions = false;
				}
			}
			//crear torre Magos
			if (mouse_x >= TILES_ANCHO * TILESIZE + (3*TILESIZE+60) && mouse_x <= TILES_ANCHO * TILESIZE + (3*TILESIZE+60) + TILESIZE+20
					&& mouse_y >= 100 && mouse_y <= 100 + TILESIZE+20){
				clickOptions = true;
				if(clickOptions && costWizN1 <= player.getGold()){
					textout(instructions , font, "Presione click izquierdo en el mapa",
							instructions->x_ofs, instructions->y_ofs+5, palette_color[12]);
					textout(instructions , font, "para crear una torre de Magos!",
							instructions->x_ofs, instructions->y_ofs+25, palette_color[12]);
					textout(instructions , font, "Q para cancelar",
							instructions->x_ofs, instructions->y_ofs+50, palette_color[12]);
					blit(instructions, buffer, 0, 0, TILES_ANCHO * TILESIZE+2, 135 + TILESIZE+20, SCREEN_W - (TILES_ANCHO * TILESIZE), 100);
					blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
					drawTowerWizards();
					vsync();
				}
				else{
					textout(instructions , font, "No hay suficiente oro",
							instructions->x_ofs, instructions->y_ofs+5, palette_color[12]);
					blit(instructions, buffer, 0, 0, TILES_ANCHO * TILESIZE+2, 135 + TILESIZE+20, SCREEN_W - (TILES_ANCHO * TILESIZE), 100);
					blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
					rest(2000);
					clickOptions = false;
				}
			}
		}
	}
}

bool Map::inSocopeTower(){
	if ((enemyOgre.px >= ((ii * TILESIZE) + (TILESIZE/2) - (scope + (TILESIZE/2))))
		&& (enemyOgre.px <= ((ii * TILESIZE) + (TILESIZE/2) + (scope + (TILESIZE/2))))
		&& (enemyOgre.py >= (jj * TILESIZE) + (TILESIZE/2) - (scope + (TILESIZE/2)))
		&&  (enemyOgre.py <= (jj * TILESIZE) + (TILESIZE/2) + (scope + (TILESIZE/2)))){
		inScope = true;
	}
	else{
		inScope = false;
	}
	return inScope;
}

void Map::attackTower(){
	if (inScope){
		ellipsefill(buffer, (ii * TILESIZE) + (TILESIZE/2), (jj * TILESIZE) + (TILESIZE/2), 5, 15, palette_color[4]);
		blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		rest(100);
	}
}

void Map::drawTowerArchers(){
	position_mouse(TILESIZE * 11,TILESIZE  * 8);
	while(true){
		if (mouse_b & 1){
			int pos_mouse = mouse_pos;
			mouse_x = pos_mouse >> 16;
			mouse_y = pos_mouse & 0x0000ffff;
			int i, j;
			i = mouse_x / TILESIZE;
			j = mouse_y / TILESIZE;
			if (map[j][i] == 1){
				setMap(i, j);
				stretch_sprite(grid, towerArchersN1, i * TILESIZE, j * TILESIZE, TILESIZE, TILESIZE);
				circlefill(buffer, (i * TILESIZE) + (TILESIZE/2), (j * TILESIZE) + (TILESIZE/2), scope + (TILESIZE/2), palette_color[11]);
				ii = i;
				jj = j;
				blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
				Tower towerArc  = Tower();
				towerArc.setType("Archers");
				towerArc.setNivel(1);
				mapTower[j][i] = towerArc;
				clickOptions = false;
				//ArchersDraw = false;
				player.setGold(-costArcN1);
				clear_bitmap(instructions);
				destroy_bitmap(instructions);
				clear_bitmap(bufferPanel);
				break;
			}
		}
		if (key[KEY_Q]){
			clear_bitmap(instructions);
			destroy_bitmap(instructions);
			clear_bitmap(bufferPanel);
			clickOptions = false;
			break;
		}
	}
}


void Map::drawTowerWizards(){
	position_mouse(TILESIZE * 10,TILESIZE  * 10);
	while(true){
		if (mouse_b & 1){
			int pos_mouse = mouse_pos;
			mouse_x = pos_mouse >> 16;
			mouse_y = pos_mouse & 0x0000ffff;
			int i, j;
			i = mouse_x / TILESIZE;
			j = mouse_y / TILESIZE;
			if (map[j][i] == 1){
				setMap(i, j);
				stretch_sprite(grid, towerWizardsN1, i * TILESIZE, j * TILESIZE, TILESIZE, TILESIZE);
				circlefill(buffer, (i * TILESIZE) + (TILESIZE/2), (j * TILESIZE) + (TILESIZE/2), scope + (TILESIZE/2), palette_color[12]);
				blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
				Tower towerWiz = Tower();
				towerWiz.setNivel(1);
				towerWiz.setType("Wizards");
				mapTower[j][i] = towerWiz;
				clickOptions = false;
				player.setGold(-costWizN1);
				clear_bitmap(instructions);
				destroy_bitmap(instructions);
				clear_bitmap(bufferPanel);
				break;
			}
		}
		if (key[KEY_Q]){
			clickOptions = false;
			clear_bitmap(instructions);
			destroy_bitmap(instructions);
			clear_bitmap(bufferPanel);
			break;
		}
	}
}



void Map::drawTowerGunners(){
	position_mouse(TILESIZE * 10,TILESIZE  * 10);
	while(true){
		if (mouse_b & 1){
			int pos_mouse = mouse_pos;
			mouse_x = pos_mouse >> 16;
			mouse_y = pos_mouse & 0x0000ffff;
			int i, j;
			i = mouse_x / TILESIZE;
			j = mouse_y / TILESIZE;
			if (map[j][i] == 1){
				setMap(i, j);
				stretch_sprite(grid, towerGunnersN1, i * TILESIZE, j * TILESIZE, TILESIZE, TILESIZE);
				circlefill(buffer, (i * TILESIZE) + (TILESIZE/2), (j * TILESIZE) + (TILESIZE/2), scope + (TILESIZE/2), palette_color[13]);
				blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
				Tower towerGun = Tower();
				towerGun.setNivel(1);
				towerGun.setType("Gunners");
				mapTower[j][i] = towerGun;
				clickOptions = false;
				player.setGold(-costGunN1);
				clear_bitmap(instructions);
				destroy_bitmap(instructions);
				clear_bitmap(bufferPanel);
				break;
			}
		}
		if (key[KEY_Q]){
			clickOptions = false;
			clear_bitmap(instructions);
			destroy_bitmap(instructions);
			clear_bitmap(bufferPanel);
			break;
		}
	}
}


void Map::drawPlayerStatistics(){
	instructions = create_bitmap(SCREEN_W - (TILES_ANCHO * TILESIZE), 200);
	if ((mouse_b & 2) && clickOptions == false){
		int pos_mouse = mouse_pos;
		mouse_x = pos_mouse >> 16;
		mouse_y = pos_mouse & 0x0000ffff;
		int i, j;
		i = mouse_x / TILESIZE;
		j = mouse_y / TILESIZE;
		if (mapTower[j][i].getType() == "Archers"){
			textprintf(instructions, font, instructions->x_ofs, instructions->y_ofs,
					palette_color[15], "Nivel: %i", mapTower[j][i].getNivel());
			textprintf(instructions, font, instructions->x_ofs, instructions->y_ofs+15,
					palette_color[15], "Mejorar:");

			if (mapTower[j][i].getNivel() == 1){
				textprintf(instructions, font, instructions->x_ofs+10, instructions->y_ofs+35,
						palette_color[15], "Costo: %d", costArcN2);
				textout(instructions , font, "Presione 'A'",
						instructions->x_ofs+10, instructions->y_ofs+60, palette_color[15]);
			}
			if (mapTower[j][i].getNivel() == 2){
				textprintf(instructions, font, instructions->x_ofs+10, instructions->y_ofs+35,
						palette_color[15], "Costo: %d", costArcN3);
				textout(instructions , font, "Presione 'A'",
						instructions->x_ofs+10, instructions->y_ofs+60, palette_color[15]);
			}
			if (mapTower[j][i].getNivel() == 3){
				textout(instructions , font, "Nivel Maximo Alcanzado",
					instructions->x_ofs+10, instructions->y_ofs+35, palette_color[15]);
			}
			textout(instructions , font, "Destruir: Presione 'D'",
					instructions->x_ofs, instructions->y_ofs+80, palette_color[15]);
			textout(instructions , font, "Salir: Presione 'Q'",
					instructions->x_ofs, instructions->y_ofs+100, palette_color[15]);
			blit(instructions, buffer, 0, 0, TILES_ANCHO * TILESIZE+2, 135 + TILESIZE+20, SCREEN_W - (TILES_ANCHO * TILESIZE), 200);
			acquire_screen();
			blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
			release_screen();
			while(true){
				/**dibujar
				 * alcance
				 * en torre
				 */
				circle(buffer, (i * TILESIZE) + (TILESIZE/2), (j * TILESIZE) + (TILESIZE/2), scope + (TILESIZE/2), palette_color[11]);
				blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
				if (key[KEY_A]){
					if (mapTower[j][i].getNivel() == 1 && costArcN2 <= player.getGold()){
						mapTower[j][i].setNivel(2);
						setMap(i, j);
						stretch_sprite(grid, towerArchersN2, i * TILESIZE, j * TILESIZE, TILESIZE, TILESIZE);
						player.setGold(-costArcN2);
						break;
					}
					if (mapTower[j][i].getNivel() == 2 && costArcN3 <= player.getGold()){
						mapTower[j][i].setNivel(3);
						setMap(i, j);
						stretch_sprite(grid, towerArchersN3, i * TILESIZE, j * TILESIZE, TILESIZE, TILESIZE);
						player.setGold(-costArcN3);
						break;
					}
					else{
						clear_bitmap(instructions);
						textout(instructions , font, "No hay suficiente oro",
								instructions->x_ofs, instructions->y_ofs+50, palette_color[4]);
						blit(instructions, buffer, 0, 0, TILES_ANCHO * TILESIZE+2, 135 + TILESIZE+20, SCREEN_W - (TILES_ANCHO * TILESIZE), 200);
						acquire_screen();
						blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
						release_screen();
						rest(2000);
						break;
					}
				}
				if (key[KEY_D]){
					if (mapTower[j][i].getNivel() == 1){
						player.setGold(costArcN1/2);
						mapTower[j][i].setNivel(0);
						mapTower[j][i].setType("null");
						map[j][i] = 1;
						clear_bitmap(instructions);
						destroy_bitmap(instructions);
						clear_bitmap(bufferPanel);
						break;
					}
					if (mapTower[j][i].getNivel() == 2){
						player.setGold(costArcN2/2);
						mapTower[j][i].setNivel(0);
						mapTower[j][i].setType("null");
						map[j][i] = 1;
						clear_bitmap(instructions);
						destroy_bitmap(instructions);
						clear_bitmap(bufferPanel);
						break;
					}
					if (mapTower[j][i].getNivel() == 3){
						player.setGold(costArcN3/2);
						mapTower[j][i].setNivel(0);
						mapTower[j][i].setType("null");
						map[j][i] = 1;
						clear_bitmap(instructions);
						destroy_bitmap(instructions);
						clear_bitmap(bufferPanel);
						break;
					}
				}
				if (key[KEY_Q]){
					clear_bitmap(instructions);
					destroy_bitmap(instructions);
					clear_bitmap(bufferPanel);
					break;
				}
			}
		}
		if (mapTower[j][i].getType() == "Wizards"){
			textprintf(instructions, font, instructions->x_ofs, instructions->y_ofs,
					palette_color[15], "Nivel: %i", mapTower[j][i].getNivel());
			textprintf(instructions, font, instructions->x_ofs, instructions->y_ofs+15,
					palette_color[15], "Mejorar:");

			if (mapTower[j][i].getNivel() == 1){
				textprintf(instructions, font, instructions->x_ofs+10, instructions->y_ofs+35,
						palette_color[15], "Costo: %d", costWizN2);
				textout(instructions , font, "Presione 'A'",
						instructions->x_ofs+10, instructions->y_ofs+60, palette_color[15]);
			}
			if (mapTower[j][i].getNivel() == 2){
				textprintf(instructions, font, instructions->x_ofs+10, instructions->y_ofs+35,
						palette_color[15], "Costo: %d", costWizN3);
				textout(instructions , font, "Presione 'A'",
						instructions->x_ofs+10, instructions->y_ofs+60, palette_color[15]);
			}
			if (mapTower[j][i].getNivel() == 3){
				textout(instructions , font, "Nivel Maximo Alcanzado",
					instructions->x_ofs+10, instructions->y_ofs+35, palette_color[15]);
			}
			textout(instructions , font, "Destruir: Presione 'D'",
					instructions->x_ofs, instructions->y_ofs+80, palette_color[15]);
			textout(instructions , font, "Salir: Presione 'Q'",
					instructions->x_ofs, instructions->y_ofs+100, palette_color[15]);
			blit(instructions, buffer, 0, 0, TILES_ANCHO * TILESIZE+2, 135 + TILESIZE+20, SCREEN_W - (TILES_ANCHO * TILESIZE), 200);
			acquire_screen();
			blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
			release_screen();
			while(true){
				/**dibujar
				 * alcance
				 * en torre
				 */
				circle(buffer, (i * TILESIZE) + (TILESIZE/2), (j * TILESIZE) + (TILESIZE/2), scope + (TILESIZE/2), palette_color[12]);
				blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
				if (key[KEY_A]){
					if (mapTower[j][i].getNivel() == 1 && costWizN2 <= player.getGold()){
						mapTower[j][i].setNivel(2);
						setMap(i, j);
						stretch_sprite(grid, towerWizardsN2, i * TILESIZE, j * TILESIZE, TILESIZE, TILESIZE);
						player.setGold(-costWizN2);
						break;
					}
					if (mapTower[j][i].getNivel() == 2 && costWizN3 <= player.getGold()){
						mapTower[j][i].setNivel(3);
						setMap(i, j);
						stretch_sprite(grid, towerWizardsN3, i * TILESIZE, j * TILESIZE, TILESIZE, TILESIZE);
						player.setGold(-costWizN3);
						break;
					}
					else{
						clear_bitmap(instructions);
						textout(instructions , font, "No hay suficiente oro",
								instructions->x_ofs, instructions->y_ofs+50, palette_color[4]);
						blit(instructions, buffer, 0, 0, TILES_ANCHO * TILESIZE+2, 135 + TILESIZE+20, SCREEN_W - (TILES_ANCHO * TILESIZE), 200);
						acquire_screen();
						blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
						release_screen();
						rest(2000);
						break;
					}
				}
				if (key[KEY_D]){
					if (mapTower[j][i].getNivel() == 1){
						player.setGold(costWizN1/2);
						mapTower[j][i].setNivel(0);
						mapTower[j][i].setType("null");
						map[j][i] = 1;
						clear_bitmap(instructions);
						destroy_bitmap(instructions);
						clear_bitmap(bufferPanel);
						break;
					}
					if (mapTower[j][i].getNivel() == 2){
						player.setGold(costWizN2/2);
						mapTower[j][i].setNivel(0);
						mapTower[j][i].setType("null");
						map[j][i] = 1;
						clear_bitmap(instructions);
						destroy_bitmap(instructions);
						clear_bitmap(bufferPanel);
						break;
					}
					if (mapTower[j][i].getNivel() == 3){
						player.setGold(costWizN3/2);
						mapTower[j][i].setNivel(0);
						mapTower[j][i].setType("null");
						map[j][i] = 1;
						clear_bitmap(instructions);
						destroy_bitmap(instructions);
						clear_bitmap(bufferPanel);
						break;
					}
				}
				if (key[KEY_Q]){
					clear_bitmap(instructions);
					destroy_bitmap(instructions);
					clear_bitmap(bufferPanel);
					break;
				}
			}
		}
		if (mapTower[j][i].getType() == "Gunners"){
			textprintf(instructions, font, instructions->x_ofs, instructions->y_ofs,
					palette_color[15], "Nivel: %i", mapTower[j][i].getNivel());
			textprintf(instructions, font, instructions->x_ofs, instructions->y_ofs+15,
					palette_color[15], "Mejorar:");

			if (mapTower[j][i].getNivel() == 1){
				textprintf(instructions, font, instructions->x_ofs+10, instructions->y_ofs+35,
						palette_color[15], "Costo: %d", costGunN2);
				textout(instructions , font, "Presione 'A'",
						instructions->x_ofs+10, instructions->y_ofs+60, palette_color[15]);
			}
			if (mapTower[j][i].getNivel() == 2){
				textprintf(instructions, font, instructions->x_ofs+10, instructions->y_ofs+35,
						palette_color[15], "Costo: %d", costGunN3);
				textout(instructions , font, "Presione 'A'",
						instructions->x_ofs+10, instructions->y_ofs+60, palette_color[15]);
			}
			if (mapTower[j][i].getNivel() == 3){
				textout(instructions , font, "Nivel Maximo Alcanzado",
					instructions->x_ofs+10, instructions->y_ofs+35, palette_color[15]);
			}

			textout(instructions , font, "Destruir: Presione 'D'",
					instructions->x_ofs, instructions->y_ofs+80, palette_color[15]);
			textout(instructions , font, "Salir: Presione 'Q'",
					instructions->x_ofs, instructions->y_ofs+100, palette_color[15]);
			blit(instructions, buffer, 0, 0, TILES_ANCHO * TILESIZE+2, 135 + TILESIZE+20, SCREEN_W - (TILES_ANCHO * TILESIZE), 200);
			acquire_screen();
			blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
			release_screen();

			while(true){
				/**dibujar
				 * alcance
				 * en torre
				 */
				circle(buffer, (i * TILESIZE) + (TILESIZE/2), (j * TILESIZE) + (TILESIZE/2), scope + (TILESIZE/2), palette_color[13]);
				blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
				if (key[KEY_A]){
					if (mapTower[j][i].getNivel() == 1 && costGunN2 <= player.getGold()){
						mapTower[j][i].setNivel(2);
						setMap(i, j);
						stretch_sprite(grid, towerWizardsN2, i * TILESIZE, j * TILESIZE, TILESIZE, TILESIZE);
						player.setGold(-costGunN2);
						break;
					}
					if (mapTower[j][i].getNivel() == 2 && costGunN3 <= player.getGold()){
						mapTower[j][i].setNivel(3);
						setMap(i, j);
						stretch_sprite(grid, towerWizardsN3, i * TILESIZE, j * TILESIZE, TILESIZE, TILESIZE);
						player.setGold(-costGunN3);
						break;
					}
					else{
						clear_bitmap(instructions);
						textout(instructions , font, "No hay suficiente oro",
								instructions->x_ofs, instructions->y_ofs+50, palette_color[4]);
						blit(instructions, buffer, 0, 0, TILES_ANCHO * TILESIZE+2, 135 + TILESIZE+20, SCREEN_W - (TILES_ANCHO * TILESIZE), 200);
						acquire_screen();
						blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
						release_screen();
						rest(2000);
						break;
					}
				}
				if (key[KEY_D]){
					if (mapTower[j][i].getNivel() == 1){
						player.setGold(costGunN1/2);
						mapTower[j][i].setNivel(0);
						mapTower[j][i].setType("null");
						map[j][i] = 1;
						clear_bitmap(instructions);
						destroy_bitmap(instructions);
						clear_bitmap(bufferPanel);
						break;
					}
					if (mapTower[j][i].getNivel() == 2){
						player.setGold(costGunN2/2);
						mapTower[j][i].setNivel(0);
						mapTower[j][i].setType("null");
						map[j][i] = 1;
						clear_bitmap(instructions);
						destroy_bitmap(instructions);
						clear_bitmap(bufferPanel);
						break;
					}
					if (mapTower[j][i].getNivel() == 3){
						player.setGold(costGunN3/2);
						mapTower[j][i].setNivel(0);
						mapTower[j][i].setType("null");
						map[j][i] = 1;
						clear_bitmap(instructions);
						destroy_bitmap(instructions);
						clear_bitmap(bufferPanel);
						break;
					}
				}
				if (key[KEY_Q]){
					clear_bitmap(instructions);
					destroy_bitmap(instructions);
					clear_bitmap(bufferPanel);
					break;
				}
			}
		}
	}
}


void Map::setMap(int i, int j){
	if (map[j][i] == 1){
		map[j][i] = 0;
	}
}


void Map::updateMap(){
	for(int i = 0; i <= 17; i++){
		for(int j = 0; j <= 22; j++){
			if (map[i][j] == 1 && map[i][j] != 0){
				//blit(tiles, grid, tiles->w-TILESIZE ,tiles->h-TILESIZE,j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
				//stretch_blit(tiles, grid, 0, 0, tiles->w, tiles->h, j *TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
				stretch_sprite(grid, tiles, j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
			}if (map[i][j] == 2 && map[i][j] != 0) {
				//blit(tiles1, grid, 0 ,0 ,j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
				stretch_sprite(grid, tiles1, j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
				//stretch_blit(tiles1, grid, 0, 0, tiles1->w, tiles1->h, j *TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
			}if (map[i][j] == 11){
				stretch_sprite(grid, tile_bridge, j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
			}
		}
	}

	blit(bufferPanel, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	blit(grid, buffer, 0, 0, 0, 0, TILES_ANCHO * TILESIZE, TILES_ALTO * TILESIZE);
	//stretch_blit(ogre, buffer, 0, 0, ogre->w, ogre->h, px_array *TILESIZE, py_array * TILESIZE, TILESIZE, TILESIZE);
	textprintf(buffer, font, TILES_ANCHO*TILESIZE + 4, 10, palette_color[14], "Oro disponible: %d", player.getGold());
	textout(buffer , font, "Costo: 50",
			TILES_ANCHO * TILESIZE + TILESIZE, 100+TILESIZE+20+2, palette_color[14]);
	textout(buffer , font, "Costo: 250",
			TILES_ANCHO * TILESIZE + (2*TILESIZE+30), 100+TILESIZE+20+2, palette_color[14]);
	textout(buffer , font, "Costo: 150",
			TILES_ANCHO * TILESIZE + (3*TILESIZE+75), 100+TILESIZE+20+2, palette_color[14]);

	/*
	vsync();
	//acquire_screen();
	blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	//release_screen();
	rest(5);*/
}
