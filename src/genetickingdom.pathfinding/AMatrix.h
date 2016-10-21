/*
 * AMatrix.h
 *
 *  Created on: Oct 11, 2016
 *      Author: ricardo
 */

#ifndef SRC_GENETICKINGDOM_PATHFINDING_AMATRIX_H_
#define SRC_GENETICKINGDOM_PATHFINDING_AMATRIX_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

class AMatrix {

	struct ANode{
		int id;
		int posX;
		int posY;
		//-----------
		bool free;
		ANode* parent;
		int G;//distance from start node
		int H;//distance from end node
		int F;// H+Gs
		ANode* up=NULL;
		ANode* down=NULL;
		ANode* left=NULL;
		ANode* right=NULL;
	};
public:
	AMatrix();
	AMatrix(int i, int j);
	void printMat();
	void setHeuristic(int iEnd, int jEnd);
	void setNeighbors();
	int filas;
	int columnas;
	ANode** matrix;
	virtual ~AMatrix();
};

#endif /* SRC_GENETICKINGDOM_PATHFINDING_AMATRIX_H_ */
