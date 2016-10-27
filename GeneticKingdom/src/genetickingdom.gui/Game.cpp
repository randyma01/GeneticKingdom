 /*
 * GUI.cpp
 *
 *  Created on: 10 oct. 2016
 *      Author: gustavo
 */


#include "Game.h"
#include <pthread.h>


int i = 0;


Game::Game() {
	allegro_init();
	install_keyboard();
	install_mouse();
	install_timer();
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
	enable_hardware_cursor();
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 700, 600, 0, 0);
	select_mouse_cursor(MOUSE_CURSOR_ALLEGRO);
	set_window_title("GK");
	show_mouse(screen);
}

Game::~Game() {

}


static void* funcion(void *parameter){
	while(1){
	i++;
	printf ("Hilo  : %d\n", i);
	}
}

void Game::startGame(){
	sound = load_sample("genetickingdom.gui/resources/sound.wav");
	buffer = create_bitmap(SCREEN_W,SCREEN_H);
	buffer1 = create_bitmap(SCREEN_W,SCREEN_H);
	background = load_bitmap("genetickingdom.gui/resources/backMenu.bmp", NULL);

	Button buttonStart = Button();
	Button buttonAbout = Button();
	buttonStart.x = 10;
	buttonStart.y = 35;
	buttonAbout.x = 550;
	buttonAbout.y = 550;
	stretch_blit(background, buffer1, 0, 0, background->w, background->h, 0, 0, SCREEN_W, SCREEN_H+17);
	blit(buffer1, buffer, 0, 0, 0, 0, 700, 600);

	buttonStart.createButton("genetickingdom.gui/resources/buttonStart.bmp", "genetickingdom.gui/resources/buttonStartPressed.bmp", buffer);
	buttonAbout.createButton("genetickingdom.gui/resources/buttonAbout.bmp", "genetickingdom.gui/resources/buttonAboutPressed.bmp", buffer);

	play_sample(sound, 255, 128, 1000, 1);
	blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

	int y = 0;
	while (!key[KEY_ESC]){

		if (mouse_b & 1){
			int pos_mouse = mouse_pos;
			mouse_x = pos_mouse >> 16;
			mouse_y = pos_mouse & 0x0000ffff;
			if (mouse_x >= buttonStart.x && mouse_x <= buttonStart.x+120 &&
					mouse_y >= buttonStart.y && mouse_y <= buttonStart.y+40){
				buttonStart.isClick();
				rest(200);
				select_mouse_cursor(MOUSE_CURSOR_BUSY);
				show_mouse(screen);
				rest(1500);
				//destroy_sample(sound);
				destroy_bitmap(buffer);
				map.drawMap();
			}
			if (mouse_x >= buttonAbout.x && mouse_x <= buttonAbout.x+120 &&
					mouse_y >= buttonAbout.y && mouse_y <= buttonAbout.y+40){
				buttonAbout.isClick();
				rest(100);
				while(true){
					viewAbout();
					if (mouse_b & 1){
						int pos_mouse = mouse_pos;
						mouse_x = pos_mouse >> 16;
						mouse_y = pos_mouse & 0x0000ffff;
						if (mouse_x >= 496 && mouse_x <= 526 &&
								mouse_y >= 202 && mouse_y <= 239){
							clear_bitmap(about);
							destroy_bitmap(about);
							rest(100);
							break;
						}
					}
					if (mouse_z > y && mouse_z < 350){
						mouse_z-=8;
						//std::cout << (mouse_z) << std::endl;key[KEY_DOWN] &&
						y+=9;
					}
					if (mouse_z < y && mouse_z > 0){
						mouse_z+=8;
						//std::cout << (mouse_z) << std::endl;key[KEY_UP] && mouse_z < 0
						y-=9;
					}
					blit(about, buffer, 0, y, 150, 200, 400, 800);
					blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
				}
				stretch_blit(background, buffer1, 0, 0, background->w, background->h, 0, 0, SCREEN_W, SCREEN_H+17);
				blit(buffer1, buffer, 0, 0, 0, 0, 700, 600);
				buttonStart.createButton("genetickingdom.gui/resources/buttonStart.bmp", "genetickingdom.gui/resources/buttonStartPressed.bmp", buffer);
				buttonAbout.createButton("genetickingdom.gui/resources/buttonAbout.bmp", "genetickingdom.gui/resources/buttonAboutPressed.bmp", buffer);
			}
		}
		text_mode(-1);
		textout(buffer, font, "Press the key ESC to exit", 240, 300, palette_color[0]);
		acquire_screen();
		blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		release_screen();
		rest(30);
	}
}


void Game::viewAbout(){

	about = create_bitmap(400, 800);
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
	textout_justify(about, font, "Genetic Kingdom", 135, 475, 50, 100, pallete_color[10]);
	textout(about, font, "Produced by:", 50, 180, pallete_color[10]);
	textout(about, font, "Ricardo Chang", 80, 200, pallete_color[10]);
	textout(about, font, "Gustavo Fallas", 80, 220, pallete_color[10]);
	textout(about, font, "Randy Martinez", 80, 240, pallete_color[10]);
	textout(about, font, "Fernanda Reyes", 80, 260, pallete_color[10]);
	textout(about, font, "II Semestre, 2016", 80, 280, pallete_color[10]);


	textout(about, font, "", 70, 300, pallete_color[10]);
	textout(about, font, "", 70, 320, pallete_color[10]);
	textout(about, font, "", 70, 340, pallete_color[10]);
	textout(about, font, "", 70, 360, pallete_color[10]);
	textout(about, font, "", 70, 380, pallete_color[10]);
	textout(about, font, "", 70, 400, pallete_color[10]);
	textout(about, font, "", 70, 420, pallete_color[10]);
	textout(about, font, "", 70, 440, pallete_color[10]);
	textout(about, font, "", 70, 460, pallete_color[10]);
	textout(about, font, "END!", 70, 680, pallete_color[10]);


	polygon(about, 12, point, pallete_color[4]);
	blit(about, buffer, 0, 0, 150, 200, 400, 800);


}




