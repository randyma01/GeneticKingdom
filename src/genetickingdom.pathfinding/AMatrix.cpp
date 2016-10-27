/*
 * AMatrix.cpp
 *
 *  Created on: Oct 11, 2016
 *      Author: ricardo
 */

#include "AMatrix.h"

AMatrix::AMatrix() {


}

/**
 * Constructor of the class, starts the matrix with the given values and starts
 * every position in the nodes and their id's
 */
AMatrix::AMatrix(int i, int j) {
	//almacenando espacio para la matriz, segun los parametros dados (i,j)
	this->filas=i;
	this->columnas=j;
	matrix = (ANode **) malloc(sizeof(ANode *) * i);
	for(int a = 0; a <i; a++) {
	    matrix[a] = (ANode *) malloc(sizeof(ANode) * j);
	}

	//inicializando los ids y posiciones de los nodos de la matriz
	cout<<"ID's : "<<endl;
	int id=1;
	for(int y = 0; y< this->filas; y++){
		for(int x=0; x< this->columnas; x++){
			matrix[y][x].posY=y;
			matrix[y][x].posX=x;//Estas posiciones se usan para reconstruir el camino
			matrix[y][x].id= id;
			matrix[y][x].free=true;
			cout<< matrix[y][x].id;
			id++;
			cout<< "   ";
		}
		cout<<"\n";
	}
	cout<<"-----------------------"<<endl;
}

/**
 * Prints the matrix
 */
void AMatrix::printMat(){
	cout<<"Printing matrix: "<<endl;
	for(int y = 0; y< this->filas; y++){
		for(int x=0; x< this->columnas; x++){
			cout<< &matrix[y][x];
			cout<< "   ";
		}
		cout<<"\n";
	}
	cout<<"-----------------------"<<endl;
}

/**
 * Sets the heuristic for every node in the matrix
 */
void AMatrix::setHeuristic(int iEnd, int jEnd){
	if((iEnd<0 || iEnd>=this->filas) || (jEnd<0 || jEnd>=this->columnas) ){
		cout<<"ERROR en los valores dados"<<endl;
		return;
	}

	cout<<"Heuristicas: "<<endl;
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

/**
 * Sets the neighbors of every node in the matrix
 */
void AMatrix::setNeighbors(){
	ANode* temp;
	for(int y=0; y< this->filas; y++){
		for(int x=0; x< this->columnas ;x++){
			if (x>0){
				temp=&matrix[y][x-1];
				matrix[y][x].left= temp; //x,y
			}
			if (x<columnas-1){
				temp=&matrix[y][x+1];
				matrix[y][x].right=temp;
			}
			if (y>0){
				temp=&matrix[y-1][x];
				matrix[y][x].up=temp;
			}
			if (y<filas-1){
				temp=&matrix[y+1][x];
				matrix[y][x].down=temp;
			}
		}
	}
}

void AMatrix::addObstacle(int i, int j){
	matrix[i][j].free=false;
}
/**
 * Creates a list of neighbors of the given node
 */
void AMatrix::getNeighborList(vector<ANode*> *lista, ANode* nodo){
	cout<<"el nodo que entra al getNL es :  "<<nodo<<endl;

	if (nodo->left != NULL && nodo->left->free==true){
		lista->push_back(nodo->left);
		cout<<"añadido vecino left"<< nodo->left <<endl;
	}
	if (nodo->right != NULL && nodo->right->free==true){
		lista->push_back(nodo->right);
		cout<<"añadido vecino right"<< nodo->right <<endl;
		}
	if (nodo->up != NULL && nodo->up->free==true){
		cout<<"añadiendo vecino up"<<endl;
		lista->push_back(nodo->up);
		cout<<"añadido vecino up"<< nodo->up <<endl;
		}
	if (nodo->down != NULL && nodo->down->free==true){
		lista->push_back(nodo->down);
		cout<<"añadido vecino down" << nodo->down<<endl;
		}
}
bool AMatrix::isInList(vector<ANode*> *lista, ANode* nodo){
	ANode *temp=lista->operator [](0);
	if (temp==nodo){	//si esta al principio
		return true;
	}
	for(int i=1; i < int(lista->size()); i++){	//y si no, busque
		temp=lista->operator [](i);
		if (temp==nodo){
			return true;
		}
	}
	return false;
}

void AMatrix::deleteNodeinList(vector<ANode*> *lista, ANode* nodo){
	ANode *temp=lista->operator [](0);
	if (temp==nodo){	//si esta al principio
		lista->erase(lista->begin());
		cout<<"deleted  "<<nodo<<endl;
		return;
	}
	for(int i=1; i < int(lista->size()); i++){	//y si no
		temp=lista->operator [](i);
		if (temp==nodo){
			lista->erase(lista->begin()+i);
			cout<<"deleted  "<<nodo<<endl;
			break;
		}
	}
}
ANode* AMatrix::getSmallerFnode(vector<ANode*>* lista){
	ANode *temp;
	ANode *resp=lista->operator [](0);
	int smaller=resp->F;
	for(int i=0; i < int(lista->size()); i++){
		temp=lista->operator [](i);
		if (temp->F < smaller){
			resp = temp; //era &*temp
			smaller=temp->F;
		}
	}
	return resp;
}
/**
 * Implement the A* Algorithm to get to the goal node, then returns a function to
 * reconstruct the path in a matrix of 1's and 0's
 */
int** AMatrix::AStar(int iStart,int jStart,int iEnd,int jEnd){
	ANode* goal;
	goal= &matrix[iEnd][jEnd];
	cout<<"mi goal: "<< goal<<endl;

	this->setHeuristic(iEnd, jEnd);
	this->setNeighbors();

	vector<ANode*> OpenList;
	vector<ANode*> *OpenListptr=&OpenList;

	vector<ANode*> ClosedList;
	vector<ANode*> *ClosedListptr=&ClosedList;

	vector<ANode*> neighborList;
	vector<ANode*>* neighborListptr=&neighborList;

	ANode* current= &matrix[iStart][jStart];
	OpenList.push_back(current);

	while( OpenList.empty() == false ){
		current=getSmallerFnode(OpenListptr);
		cout<<"current is: "<< current<<endl;
		if (current==goal){	//condicion de parada
			cout<<"PARAADAAAAAAAAAAAAAA!!!!!!   ";
			cout<<current<<endl;
			return reconstructPath(goal);
		}

		deleteNodeinList(OpenListptr,current);
		ClosedList.push_back(current);

		cout<<"antes del nwighbor"<<endl;


		neighborList.clear();
		getNeighborList(neighborListptr,current);

		cout<<"despues del nwighbor"<<endl;
		for(int i=0; i<int(neighborListptr->size()); i++){
			cout<<"en el for de AStar"<<endl;

			ANode* neighbor;
			neighbor=neighborListptr->operator [](i);

			if (isInList(ClosedListptr,neighbor)){
				continue;
			}

			int tentative_gScore;
			tentative_gScore= current->G + 10;
			cout<< "CURRRENTTTT  GGGGGG>>>>   "<< current->G<<endl ;
			cout<<"tentativeScore:   "<<tentative_gScore<<endl;

			if (! isInList(OpenListptr,neighbor)){
				OpenList.push_back(neighbor);
			}
			else if (tentative_gScore >= neighbor->G){
				continue;		// This is not a better path.
			}

			cout<<"adding.... things..."<<neighbor<<"   and   his parent>>  "<<current<<endl;
			neighbor->parent= current;
			neighbor->G= tentative_gScore;
			neighbor->F= neighbor->G + neighbor->H;
		}
	}

	cout<<"ERROR en el pathfinding A*"<<endl;
	return NULL;
}

/**
 * Reconstruct the path by the given node and returns a matrix of 1's and 0's
 * being the 1's the path and the only 5 the end  of it
 */
int** AMatrix::reconstructPath(ANode* end){
	int** table = new int*[filas];
	for (int i = 0; i < filas; ++i)
	{
	   table[i] = new int[columnas];
	}



	for(int y = 0; y< this->filas; y++){
		for(int x=0; x< this->columnas; x++){
			table[y][x]=0;
		}
	}

	ANode* temp;
	temp= end->parent;

	table[end->posY][end->posX]=5;	//es el final, lo adapto para el codigo de tavo

	while(temp!=NULL){
		table[temp->posY][temp->posX]=1;
		temp=temp->parent;
	}

	cout<<"The path is:  "<<endl;
	for(int ym = 0; ym< this->filas; ym++){
		for(int xn=0; xn< this->columnas; xn++){
			cout<< table[ym][xn];
			cout<< "   ";
		}
		cout<<"\n";
	}
	cout<<"-----------------------"<<endl;
	return table;
}

AMatrix::~AMatrix() {

}

