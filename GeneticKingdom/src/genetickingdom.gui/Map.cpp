/*
 * Map.cpp
 *
 *  Created on: 11 oct. 2016
 *      Author: gustavo
 */

#include "Map.h"

#include <vector>

#include <pthread.h>




bool inScope = false;
bool clickOptions = false;

/*
 * Mouse
 */
extern volatile int mouse_x;
extern volatile int mouse_y;
extern volatile int mouse_b;
extern volatile int mouse_pos;

/*
 * Player, Contains gold
 */
Player player = Player();

/*
 * Cost Tower Archers
 */
int costArcN1 = 50;
int costArcN2 = 100;
int costArcN3 = 200;
/*
 * Cost Tower Wizards
 */
int costWizN1 = 150;
int costWizN2 = 230;
int costWizN3 = 350;
/*
 * Cost Tower Gunners
 */
int costGunN1 = 250;
int costGunN2 = 400;
int costGunN3 = 600;


vector<Enemy> enemyAr;


Map::Map(){}

Map::~Map(){}

void Map::initialize(){
	int w, h;
	get_desktop_resolution(&w, &h);
	TILESIZE = (h / 17)+1;
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
	tiles = load_bitmap("genetickingdom.gui/resources/tiles.bmp", NULL);
	tiles1 = load_bitmap("genetickingdom.gui/resources/tiles1.bmp", NULL);
	tile_bridge = load_bitmap("genetickingdom.gui/resources/bridge.bmp", NULL);


	/*
	 * Images Towers
	 */
	towerArchersN1 = load_bitmap("genetickingdom.gui/resources/towerArcN1.bmp", NULL);
	towerArchersN2 = load_bitmap("genetickingdom.gui/resources/towerArcN2.bmp", NULL);
	towerArchersN3 = load_bitmap("genetickingdom.gui/resources/towerArcN3.bmp", NULL);

	towerGunnersN1 = load_bitmap("genetickingdom.gui/resources/towerGunN1.bmp", NULL);
	towerGunnersN2 = load_bitmap("genetickingdom.gui/resources/towerGunN2.bmp", NULL);
	towerGunnersN3 = load_bitmap("genetickingdom.gui/resources/towerGunN3.bmp", NULL);

	towerWizardsN1 = load_bitmap("genetickingdom.gui/resources/towerWizN1.bmp", NULL);
	towerWizardsN2 = load_bitmap("genetickingdom.gui/resources/towerWizN2.bmp", NULL);
	towerWizardsN3 = load_bitmap("genetickingdom.gui/resources/towerWizN3.bmp", NULL);

	drawTowerArc = load_bitmap("genetickingdom.gui/resources/TwArchers.bmp", NULL);
	drawTowerGun = load_bitmap("genetickingdom.gui/resources/TwGunners.bmp", NULL);
	drawTowerWiz = load_bitmap("genetickingdom.gui/resources/TwWizards.bmp", NULL);

}

void Map::initializeEnemys(){

	enemyAr.push_back(Enemy(4, 2, 6, 8,  "O", TILESIZE, buffer));
	enemyAr.push_back(Enemy(4, 2, 6, 14, "O", TILESIZE, buffer));
	enemyAr.push_back(Enemy(4, 2, 6, 4,  "O", TILESIZE, buffer));
}

static void* funcion(void *parameter){
	printf ("Hilo  : %d\n", enemyAr.at(1));
}

void Map::drawMap(){

	initialize();
	initializeEnemys();

	/*
	 * Bucle principal
	 */
	while(!key[KEY_ESC]){
		drawTower();
		drawPlayerStatistics();
		blit(bufferPanel, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		blit(grid, buffer, 0, 0, 0, 0, TILES_ANCHO * TILESIZE, TILES_ALTO * TILESIZE);
		updateMap();
		/*
		 * muestra el oro disponible
		 * y los costos de cada torre
		 */
		textprintf(buffer, font, TILES_ANCHO*TILESIZE + 4, 10, palette_color[14],
				"Oro disponible: %d", player.getGold());
		textout(buffer , font, "Costo: 50",
				TILES_ANCHO * TILESIZE + TILESIZE, 100+TILESIZE+20+2, palette_color[14]);
		textout(buffer , font, "Costo: 250",
				TILES_ANCHO * TILESIZE + (2*TILESIZE+30), 100+TILESIZE+20+2, palette_color[14]);
		textout(buffer , font, "Costo: 150",
				TILES_ANCHO * TILESIZE + (3*TILESIZE+75), 100+TILESIZE+20+2, palette_color[14]);

		//mover enemigo

//		pthread_t hilo1;
//
//		if (key[KEY_ENTER]){
//			pthread_create(&hilo1, NULL, funcion, NULL);
//		}


		acquire_screen();
		blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		release_screen();
		rest(5);
	}
}

//
//void *Map::enemyMove(void *parameter){
//
//	while(true){
//		for (int i = 0; i < int(enemyAr.size()); i++){
//			enemyAr.operator [](i).startEnemy(mapEnemy);
//			updateMap();
//		}
//		if (key[KEY_Q]){
//			break;
//		}
//	}
//}




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
				blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
				Tower towerArc  = Tower();
				towerArc.setType("Archers");
				towerArc.setLevel(1);
				towerArc.setDamage(1);
				towerArc.setScope(3*TILESIZE);
				mapTower[j][i] = towerArc;
				clickOptions = false;
				player.setGold(-costArcN1);
				clear_bitmap(instructions);
				destroy_bitmap(instructions);
				clear_bitmap(bufferPanel);
				break;
			}
		}
		if (key[KEY_Q]){
			/*
			 * por si el jugador
			 * ya no quiere construir
			 * ese tipo de torre
			 */
			clear_bitmap(instructions);
			destroy_bitmap(instructions);
			clear_bitmap(bufferPanel);
			clickOptions = false;
			break;
		}
	}
}

void Map::drawTowerWizards(){
	position_mouse(TILESIZE * 11,TILESIZE  * 10);
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
				blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
				Tower towerWiz = Tower();
				towerWiz.setType("Wizards");
				towerWiz.setLevel(1);
				towerWiz.setDamage(3);
				towerWiz.setScope(2*TILESIZE);
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
			/*
			 * por si el jugador
			 * ya no quiere construir
			 * ese tipo de torre
			 */
			clickOptions = false;
			clear_bitmap(instructions);
			destroy_bitmap(instructions);
			clear_bitmap(bufferPanel);
			break;
		}
	}
}

void Map::drawTowerGunners(){
	position_mouse(TILESIZE * 11,TILESIZE  * 10);
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
				blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
				Tower towerGun = Tower();
				towerGun.setType("Gunners");
				towerGun.setLevel(1);
				towerGun.setDamage(4);
				towerGun.setScope(1*TILESIZE);
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
			/*
			 * por si el jugador
			 * ya no quiere construir
			 * ese tipo de torre
			 */
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
					palette_color[15], "Nivel: %i", mapTower[j][i].getLevel());
			textprintf(instructions, font, instructions->x_ofs, instructions->y_ofs+15,
					palette_color[15], "Mejorar:");

			if (mapTower[j][i].getLevel() == 1){
				textprintf(instructions, font, instructions->x_ofs+10, instructions->y_ofs+35,
						palette_color[15], "Costo: %d", costArcN2);
				textout(instructions , font, "Presione 'A'",
						instructions->x_ofs+10, instructions->y_ofs+60, palette_color[15]);
			}
			if (mapTower[j][i].getLevel() == 2){
				textprintf(instructions, font, instructions->x_ofs+10, instructions->y_ofs+35,
						palette_color[15], "Costo: %d", costArcN3);
				textout(instructions , font, "Presione 'A'",
						instructions->x_ofs+10, instructions->y_ofs+60, palette_color[15]);
			}
			if (mapTower[j][i].getLevel() == 3){
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
				circle(buffer, (i * TILESIZE) + (TILESIZE/2), (j * TILESIZE) + (TILESIZE/2), mapTower[j][i].getScope() + (TILESIZE/2), palette_color[11]);
				blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
				if (key[KEY_A]){
					if (mapTower[j][i].getLevel() == 1 && costArcN2 <= player.getGold()){
						mapTower[j][i].setLevel(2);
						mapTower[j][i].setDamage(2);
						mapTower[j][i].setScope(4*TILESIZE);
						setMap(i, j);
						stretch_sprite(grid, towerArchersN2, i * TILESIZE, j * TILESIZE, TILESIZE, TILESIZE);
						player.setGold(-costArcN2);
						break;
					}
					if (mapTower[j][i].getLevel() == 2 && costArcN3 <= player.getGold()){
						mapTower[j][i].setLevel(3);
						mapTower[j][i].setDamage(3);
						mapTower[j][i].setScope(5*TILESIZE);
						setMap(i, j);
						stretch_sprite(grid, towerArchersN3, i * TILESIZE, j * TILESIZE, TILESIZE, TILESIZE);
						player.setGold(-costArcN3);
						break;
					}
					if (mapTower[j][i].getLevel() == 3){
						clear_bitmap(instructions);
						textout(instructions , font, "No hay Mejora",
								instructions->x_ofs, instructions->y_ofs+50, palette_color[10]);
						blit(instructions, buffer, 0, 0, TILES_ANCHO * TILESIZE+2, 135 + TILESIZE+20, SCREEN_W - (TILES_ANCHO * TILESIZE), 200);
						acquire_screen();
						blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
						release_screen();
						rest(2000);
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
					if (mapTower[j][i].getLevel() == 1){
						player.setGold(costArcN1/2);
						mapTower[j][i] = Tower();
						map[j][i] = 1;
						clear_bitmap(instructions);
						destroy_bitmap(instructions);
						clear_bitmap(bufferPanel);
						break;
					}
					if (mapTower[j][i].getLevel() == 2){
						player.setGold(costArcN2/2);
						mapTower[j][i] = Tower();
						map[j][i] = 1;
						clear_bitmap(instructions);
						destroy_bitmap(instructions);
						clear_bitmap(bufferPanel);
						break;
					}
					if (mapTower[j][i].getLevel() == 3){
						player.setGold(costArcN3/2);
						mapTower[j][i] = Tower();
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
					palette_color[15], "Nivel: %i", mapTower[j][i].getLevel());
			textprintf(instructions, font, instructions->x_ofs, instructions->y_ofs+15,
					palette_color[15], "Mejorar:");

			if (mapTower[j][i].getLevel() == 1){
				textprintf(instructions, font, instructions->x_ofs+10, instructions->y_ofs+35,
						palette_color[15], "Costo: %d", costWizN2);
				textout(instructions , font, "Presione 'A'",
						instructions->x_ofs+10, instructions->y_ofs+60, palette_color[15]);
			}
			if (mapTower[j][i].getLevel() == 2){
				textprintf(instructions, font, instructions->x_ofs+10, instructions->y_ofs+35,
						palette_color[15], "Costo: %d", costWizN3);
				textout(instructions , font, "Presione 'A'",
						instructions->x_ofs+10, instructions->y_ofs+60, palette_color[15]);
			}
			if (mapTower[j][i].getLevel() == 3){
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
				circle(buffer, (i * TILESIZE) + (TILESIZE/2), (j * TILESIZE) + (TILESIZE/2), mapTower[j][i].getScope() + (TILESIZE/2), palette_color[12]);
				blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
				if (key[KEY_A]){
					if (mapTower[j][i].getLevel() == 1 && costWizN2 <= player.getGold()){
						mapTower[j][i].setLevel(2);
						mapTower[j][i].setDamage(4);
						mapTower[j][i].setScope(3*TILESIZE);
						setMap(i, j);
						stretch_sprite(grid, towerWizardsN2, i * TILESIZE, j * TILESIZE, TILESIZE, TILESIZE);
						player.setGold(-costWizN2);
						break;
					}
					if (mapTower[j][i].getLevel() == 2 && costWizN3 <= player.getGold()){
						mapTower[j][i].setLevel(3);
						mapTower[j][i].setDamage(5);
						mapTower[j][i].setScope(4*TILESIZE);
						setMap(i, j);
						stretch_sprite(grid, towerWizardsN3, i * TILESIZE, j * TILESIZE, TILESIZE, TILESIZE);
						player.setGold(-costWizN3);
						break;
					}
					if (mapTower[j][i].getLevel() == 3){
						clear_bitmap(instructions);
						textout(instructions , font, "No hay Mejora",
								instructions->x_ofs, instructions->y_ofs+50, palette_color[10]);
						blit(instructions, buffer, 0, 0, TILES_ANCHO * TILESIZE+2, 135 + TILESIZE+20, SCREEN_W - (TILES_ANCHO * TILESIZE), 200);
						acquire_screen();
						blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
						release_screen();
						rest(2000);
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
					if (mapTower[j][i].getLevel() == 1){
						player.setGold(costWizN1/2);
						mapTower[j][i] = Tower();
						map[j][i] = 1;
						clear_bitmap(instructions);
						destroy_bitmap(instructions);
						clear_bitmap(bufferPanel);
						break;
					}
					if (mapTower[j][i].getLevel() == 2){
						player.setGold(costWizN2/2);
						mapTower[j][i] = Tower();
						map[j][i] = 1;
						clear_bitmap(instructions);
						destroy_bitmap(instructions);
						clear_bitmap(bufferPanel);
						break;
					}
					if (mapTower[j][i].getLevel() == 3){
						player.setGold(costWizN3/2);
						mapTower[j][i] = Tower();
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
					palette_color[15], "Nivel: %i", mapTower[j][i].getLevel());
			textprintf(instructions, font, instructions->x_ofs, instructions->y_ofs+15,
					palette_color[15], "Mejorar:");

			if (mapTower[j][i].getLevel() == 1){
				textprintf(instructions, font, instructions->x_ofs+10, instructions->y_ofs+35,
						palette_color[15], "Costo: %d", costGunN2);
				textout(instructions , font, "Presione 'A'",
						instructions->x_ofs+10, instructions->y_ofs+60, palette_color[15]);
			}
			if (mapTower[j][i].getLevel() == 2){
				textprintf(instructions, font, instructions->x_ofs+10, instructions->y_ofs+35,
						palette_color[15], "Costo: %d", costGunN3);
				textout(instructions , font, "Presione 'A'",
						instructions->x_ofs+10, instructions->y_ofs+60, palette_color[15]);
			}
			if (mapTower[j][i].getLevel() == 3){
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
				circle(buffer, (i * TILESIZE) + (TILESIZE/2), (j * TILESIZE) + (TILESIZE/2), mapTower[j][i].getScope() + (TILESIZE/2), palette_color[13]);
				blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
				if (key[KEY_A]){
					if (mapTower[j][i].getLevel() == 1 && costGunN2 <= player.getGold()){
						mapTower[j][i].setLevel(2);
						mapTower[j][i].setDamage(6);
						mapTower[j][i].setScope(2*TILESIZE);
						setMap(i, j);
						stretch_sprite(grid, towerGunnersN2, i * TILESIZE, j * TILESIZE, TILESIZE, TILESIZE);
						player.setGold(-costGunN2);
						break;
					}
					if (mapTower[j][i].getLevel() == 2 && costGunN3 <= player.getGold()){
						mapTower[j][i].setLevel(3);
						mapTower[j][i].setDamage(8);
						mapTower[j][i].setScope(2*TILESIZE);
						setMap(i, j);
						stretch_sprite(grid, towerGunnersN3, i * TILESIZE, j * TILESIZE, TILESIZE, TILESIZE);
						player.setGold(-costGunN3);
						break;
					}
					if (mapTower[j][i].getLevel() == 3){
						clear_bitmap(instructions);
						textout(instructions , font, "No hay Mejora",
								instructions->x_ofs, instructions->y_ofs+50, palette_color[10]);
						blit(instructions, buffer, 0, 0, TILES_ANCHO * TILESIZE+2, 135 + TILESIZE+20, SCREEN_W - (TILES_ANCHO * TILESIZE), 200);
						acquire_screen();
						blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
						release_screen();
						rest(2000);
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
					if (mapTower[j][i].getLevel() == 1){
						player.setGold(costGunN1/2);
						mapTower[j][i] = Tower();
						map[j][i] = 1;
						clear_bitmap(instructions);
						destroy_bitmap(instructions);
						clear_bitmap(bufferPanel);
						break;
					}
					if (mapTower[j][i].getLevel() == 2){
						player.setGold(costGunN2/2);
						mapTower[j][i] = Tower();
						map[j][i] = 1;
						clear_bitmap(instructions);
						destroy_bitmap(instructions);
						clear_bitmap(bufferPanel);
						break;
					}
					if (mapTower[j][i].getLevel() == 3){
						player.setGold(costGunN3/2);
						mapTower[j][i] = Tower();
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
		mapEnemy[j][i] = 0;
	}
}

void Map::updateMap(){
	for(int i = 0; i <= 17; i++){
		for(int j = 0; j <= 22; j++){
			if (map[i][j] == 1 && map[i][j] != 0){
				stretch_sprite(grid, tiles, j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
			}if (map[i][j] == 2 && map[i][j] != 0) {
				stretch_sprite(grid, tiles1, j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
			}if (map[i][j] == 11){
				stretch_sprite(grid, tile_bridge, j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
			}
		}
	}
	blit(bufferPanel, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	blit(grid, buffer, 0, 0, 0, 0, TILES_ANCHO * TILESIZE, TILES_ALTO * TILESIZE);
	textprintf(buffer, font, TILES_ANCHO*TILESIZE + 4, 10, palette_color[14], "Oro disponible: %d", player.getGold());
	textout(buffer , font, "Costo: 50",
			TILES_ANCHO * TILESIZE + TILESIZE, 100+TILESIZE+20+2, palette_color[14]);
	textout(buffer , font, "Costo: 250",
			TILES_ANCHO * TILESIZE + (2*TILESIZE+30), 100+TILESIZE+20+2, palette_color[14]);
	textout(buffer , font, "Costo: 150",
			TILES_ANCHO * TILESIZE + (3*TILESIZE+75), 100+TILESIZE+20+2, palette_color[14]);
}
