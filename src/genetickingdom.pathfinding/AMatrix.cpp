/*
 * AMatrix.cpp
 *
 *  Created on: Oct 11, 2016
 *      Author: ricardo
 */

#include "AMatrix.h"

AMatrix::AMatrix() {
	// TODO Auto-generated constructor stub

}
AMatrix::AMatrix(int i, int j) {
	//apartando espacio para la matriz, segun los parametros dados (i,j)
	this->filas=i;
	this->columnas=j;
	matrix = (ANode **) malloc(sizeof(ANode *) * j);
	for(int a = 0; a <j; a++) {
	    matrix[a] = (ANode *) malloc(sizeof(ANode) * i);
	}

	//inicializando los ids de los nodos de la matriz
	//Nota personal: podria inicializar los otros atributos free, posX, posY. Pero todavia no se si se van a utilizar
	int id=1;
	for(int y = 0; y< this->filas; y++){
		for(int x=0; x< this->columnas; x++){
			matrix[x][y].id= id;
			//cout<< matrix[x][y].id;
			id++;
			//cout<< "   ";
		}
		//cout<<"\n";
	}
	//cout<<"-----------------------"<<endl;
}

void AMatrix::printMat(){
	for(int y = 0; y< this->filas; y++){
			for(int x=0; x< this->columnas; x++){
				cout<< matrix[x][y].id;
				cout<< "   ";
			}
			cout<<"\n";
		}
		cout<<"-----------------------"<<endl;
}

void AMatrix::setHeuristic(int iEnd, int jEnd){
	if((iEnd<0 || iEnd>=this->filas) || (jEnd<0 || jEnd>=this->columnas) ){
		cout<<"ERROR en los valores dados"<<endl;
		return;
	}

	int heuristic;
	for(int y=0; y< this->filas; y++){
		for(int x=0; x< this->columnas ;x++){
			heuristic= (abs(jEnd - x)+abs(iEnd - y));
			matrix[y][x].H=heuristic;
			cout<< matrix[y][x].H;
			cout<< "  ";
		}
		cout<<"\n";
	}
	cout<<"=========================="<<endl;
}

void AMatrix::setNeighbors(){
	ANode* temp;
	for(int y=0; y< this->filas; y++){
		for(int x=0; x< this->columnas ;x++){
			if (x>0){
				temp=&matrix[x-1][y];
				matrix[x][y].left=temp;
			}
			if (x<columnas-1){
				temp=&matrix[x+1][y];
				matrix[x][y].right=temp;
			}
			if (y>0){
				temp=&matrix[x][y-1];
				matrix[x][y].up=temp;
			}
			if (y<filas-1){
				temp=&matrix[x][y+1];
				matrix[x][y].down=temp;
			}
		}
	}
}

AMatrix::~AMatrix() {
	// TODO Auto-generated destructor stub
}
