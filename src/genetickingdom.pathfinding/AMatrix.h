/*
 * AMatrix.h
 *
 *  Created on: Oct 11, 2016
 *      Author: ricardo
 */

#ifndef AMATRIX_H_
#define AMATRIX_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "ANode.h"
#include "AList.h"
using namespace std;

class AMatrix {

public:
	AMatrix();
	AMatrix(int i, int j);
	void printMat();
	void setHeuristic(int iEnd, int jEnd);
	void setNeighbors();

	void addObstacle(int i, int j);

	void getNeighborList(vector<ANode*> *lista, ANode* nodo);

	int** reconstructPath(ANode* end);
	int** AStar(int iStart,int jStart,int iEnd,int jEnd);
	int filas;
	int columnas;
	ANode** matrix;

	ANode* getSmallerFnode(vector<ANode*> *lista);
	void deleteNodeinList(vector<ANode*> *lista, ANode* nodo);
	bool isInList(vector<ANode*> *lista, ANode* nodo);
	virtual ~AMatrix();
};

#endif /* AMATRIX_H_ */
