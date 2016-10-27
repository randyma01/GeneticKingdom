/*
 * ANode.cpp
 *
 *  Created on: Oct 14, 2016
 *      Author: ricardo
 */

#include "ANode.h"

ANode::ANode() {
	next=NULL;
	posc=0;
	id=0;
	posX=0;
	posY=0;
	parent=NULL;
	free=true;
	G=0;
	H=0;
	F=0;
	dist_between=10;
	up=NULL;
	down=NULL;
	left=NULL;
	right=NULL;
}

ANode::~ANode() {
	// TODO Auto-generated destructor stub
}

