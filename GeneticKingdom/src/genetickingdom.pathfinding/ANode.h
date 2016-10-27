/*
 * ANode.h
 *
 *  Created on: Oct 14, 2016
 *      Author: ricardo
 */

#ifndef ASTAR_ANODE_H_
#define ASTAR_ANODE_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class ANode {
public:
	ANode();
	//LISTA
	ANode *next;
	int posc;
	//----------
	//MATRIX

	int id;
	int posX;
	int posY;
	//-----------
	//A* Algorithm
	ANode* parent;
	bool free;
	int G;//distance from this node to starting node
	int H;//distance from end node
	int F;// H+Gs
	int dist_between;	//distance betwen this and a neighbor, any neighbor cuz fuck you!!
	ANode* up=NULL;
	ANode* down=NULL;
	ANode* left=NULL;
	ANode* right=NULL;

	virtual ~ANode();
};

#endif /* ASTAR_ANODE_H_ */
