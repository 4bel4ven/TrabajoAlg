#include <iostream>
#include "Libreria.hpp"
#include <cstdlib>

void main() {
	

	int opcion;
	Clibreria nuevo;
	do {
		system("CLS");
		std::cout << "\t\t\tBienvenido";
		std::cout << "\nOPCIONES:\n1:Importar un archivo\n2:Realizar un filtro\n3.Seleccionar una cantidad de columnas\n4.Mostrar\n0.salir.";
		do {
			std::cout << "\n\t\tIntroduzca un número: ";
			std::cin >> opcion;
		} while (opcion < 0 || opcion >4);
		if (opcion == 1) {
			system("CLS");
			nuevo.pedirdatos();
			nuevo.pedirtiposdevalor();
			nuevo.indexar();
			nuevo.imprimir();
			std::cin.ignore();
			std::cin.get();
		}
		else if (opcion == 2) {
			system("CLS");
			nuevo.pedirFiltrado();
			std::cin.ignore();
			std::cin.get();
		}
		else if (opcion == 3) {
			system("CLS");
			nuevo.iniciarSeleccion();
			std::cin.ignore();
			std::cin.get();
		}
		else if (opcion == 4) {
			system("CLS");
			nuevo.imprimir();
			std::cin.ignore();
			std::cin.get();
		};
	} while (opcion != 0);
	
	
}