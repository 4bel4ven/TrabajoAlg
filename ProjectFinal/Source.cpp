#include <iostream>
#include "Libreria.hpp"
#include <cstdlib>

void main() {
	Clibreria nuevo;

//	nuevo.pedirdatos();
	nuevo.from_csv("Arrests5.csv", 1, ',');
	system("CLS");
	nuevo.tiposdevalor();
	system("CLS");
	nuevo.imprimir();
	nuevo.indexar();
};