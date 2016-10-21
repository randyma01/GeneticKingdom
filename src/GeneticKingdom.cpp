//============================================================================
// Name        : GeneticKingdom.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <iostream>
#include <stdio.h>
#include <string>
#include "genetickingdom.enemys/Factory.h"


int main() {

	Factory factory = Factory();
	Enemy array[2];
	array[0] = factory.makeEnemy("O");

	std::cout << "[0]: " << array[0].name << std::endl;

	return 0;
}
