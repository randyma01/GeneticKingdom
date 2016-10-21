 /*
 * GUI.cpp
 *
 *  Created on: 10 oct. 2016
 *      Author: gustavo
 */


#include <pthread.h>

#include "Game.h"
#include "Map.h"
#include "Button.h"




Game::Game() {
}

Game::~Game() {

}


void Game::startGame(){
	allegro_init();
	install_keyboard();
	install_mouse();
	install_timer();
	enable_hardware_cursor();
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 700, 600, 0, 0);
	select_mouse_cursor(MOUSE_CURSOR_ALLEGRO);
	set_window_title("Crazy Genetic Kingdom");

	show_mouse(screen);

	Map map;
	BITMAP *buffer;
	buffer = create_bitmap(SCREEN_W,SCREEN_H);
	Button buttonStart = Button();
	Button buttonAbout = Button();
	buttonStart.x = 280;
	buttonStart.y = 210;
	buttonAbout.x = 280;
	buttonAbout.y = 310;
	buttonStart.createButton("resources/buttonStart.bmp", "resources/buttonStartPressed.bmp", buffer);
	buttonAbout.createButton("resources/buttonAbout.bmp", "resources/buttonAboutPressed.bmp", buffer);
	blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);


	while (!key[KEY_ESC]){
		if (mouse_b & 1){
			int pos_mouse = mouse_pos;
			mouse_x = pos_mouse >> 16;
			mouse_y = pos_mouse & 0x0000ffff;
			if (mouse_x >= 280 && mouse_x <= 280+135 && mouse_y >= 210 && mouse_y <= 210+45){
				buttonStart.isClick();
				rest(200);
				select_mouse_cursor(MOUSE_CURSOR_BUSY);
				show_mouse(screen);
				rest(1500);
				destroy_bitmap(buffer);
				map.drawMap();
			}
			if (mouse_x >= 280 && mouse_x <= 280+135 && mouse_y >= 310 && mouse_y <= 310+45){
				textout(buffer, font, "About", 10, 10, palette_color[3]);
				buttonAbout.isClick();
			}

		}
		acquire_screen();
		blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		release_screen();
		rest(30);

	}

}


