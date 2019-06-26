#include <iostream>
#include "Libreria.hpp"

void main() {
	Clibreria nuevo;

//	nuevo.pedirdatos();
	nuevo.from_csv("Arrests5.csv", 1, ',');
	nuevo.tiposdevalor();
	nuevo.indexar();
};