/*
 * Button.h
 *
 *  Created on: 12 oct. 2016
 *      Author: gustavo
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include <iostream>
#include <stdio.h>
#include <string>
#include <allegro.h>





class Button {


public:
	Button();
	virtual ~Button();
	void createButton(const char *pathImage, const char*Image, BITMAP *buffer1);
	void isClick();

public:
	BITMAP *buffer;
	int x;
	int y;
	const char *path;
	BITMAP *imageButton;
	BITMAP *imageButton1;

};

#endif /* BUTTON_H_ */
