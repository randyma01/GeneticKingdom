/*
 * Button.cpp
 *
 *  Created on: 12 oct. 2016
 *      Author: gustavo
 */

#include "Button.h"




Button::Button() {}

Button::~Button() {}



void Button::isClick(){
	clear_bitmap(imageButton);
	imageButton = load_bitmap(path, NULL);
	stretch_blit(imageButton, buffer, 0, 0, imageButton->w, imageButton->h, x, y, 120, 40);
	blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

}

void Button::createButton(const char *pathImage, const char*Image, BITMAP *buffer1){
	buffer = buffer1;
	this->path = Image;
	imageButton = load_bitmap(pathImage, NULL);
	stretch_blit(imageButton, buffer, 0, 0, imageButton->w, imageButton->h, x, y, 120, 40);
	blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}
