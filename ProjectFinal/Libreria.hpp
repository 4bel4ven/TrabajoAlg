
#ifndef _LIBRERIA_HPP_
#define _LIBRERIA_HPP_

#include <stdio.h>
#include <vector>
#include <string>
#include <sstream> 
#include <fstream>
#include <stdio.h>
#include "arbol_AVL.hpp"
#include "hashtable.hpp"

class Clibreria {

private:
	std::vector<std::vector<std::string>> tupla;/// quité *

	std::vector<int> tiposdevalores;

	std::vector< hashtable> busquedaString;

	std::vector<AVLTree<int*>> busquedaInt;

	std::vector<AVLTree<float*>> busquedaFloat;

public:

	Clibreria() {
	}
	~Clibreria() {}

	void from_csv(std::string nombreArchivo, int header, char separador);
	void pedirdatos();
	void tiposdevalor();
	void indexar();
	//void to_csv(std::string nombreArchivo);

};

void Clibreria::from_csv(std::string nombreArchivo, int header, char separador)
{
	std::string temp;
	std::string registro;
	std::ifstream archivo(nombreArchivo);

	while (std::getline(archivo, registro)) {
		std::stringstream ss(registro);
		std::vector <std::string> row;  ///aqui quité *
		while (std::getline(ss, temp, separador))
		{
			row.push_back(temp); ///quité &
		}
		tupla.push_back(row);
	}
}

void Clibreria::pedirdatos()
{
	std::string archivo;
	std::string extensionotro;
	int opcion = 3;
	int cabecera;
	char separadorotro;

	std::cout << "\nintroduzca nombre de archivo (sin extension): ";
	std::getline(std::cin, archivo);

	while (opcion >= 3 || opcion < 0) {
		std::cout << "\nque tipo de archivo es\n[0].csv [1].tsv [2]otro : ";
		std::cin >> opcion;
		if (opcion >= 3 || opcion < 0)
			std::cout << "\nERROR, introduzca uno de los valores señalados";
	}

	if (opcion == 2) {
		std::cout << "\n\tDetalles adicionales necesarios\n\t\tque tipo de separador usa: ";
		std::cin >> separadorotro;
		std::cout << "\n\t\tcual es su extension (sin punto): ";
		std::getline(std::cin, extensionotro);
		archivo = archivo + '.' + extensionotro;
	}

	std::cout << "\ncuantas filas son de cabecera: ";
	std::cin >> cabecera;

	switch (opcion)
	{
	case 0:
		from_csv(archivo + ".csv", cabecera, ',');
		break;
	case 1:
		from_csv(archivo + ".tsv", cabecera, '\t');
		break;
	case 2:
		from_csv(archivo, cabecera, separadorotro);
		break;
	default:
		break;
	}
}

void Clibreria::tiposdevalor()
{
	for (int i = 0; i < tupla[0].size(); i++)
	{
	int valor = 3;
		while (valor >= 3 || valor < 0) {
			std::cout << "\n[0]entero [1]flotante [2]cadena de texto\nintroduzca el tipo de variable de la columna n " << i + 1 << " :";
			std::cin >> valor;
			if (valor >= 3 || valor < 0)
				std::cout << "\nERROR, introduzca uno de los valores señalados";
		}
		tiposdevalores.push_back(valor);
	}
}

void Clibreria::indexar()
{
	for (int i = 0; i < tiposdevalores.size(); i++) {

		int opcion = tiposdevalores.at(i);

		int intfromStr;
		float floatfromStr;

		AVLTree<int> tempArbolInt;
		AVLTree<float> tempArbolFlot;

		std::string tempStr ; ///convertí a string normal

		

		switch (opcion) {
		case 0: //enteros
			for (int j = 0; j < tupla.at(0).size(); j++) {
				tempStr = tupla[j][i];
				intfromStr = std::stoi(tempStr); ///quité *
				tempArbolInt.Add(intfromStr);
			}
			delete (&tempArbolInt);
			break;
		case 1: //flotantes
			for (int j = 0; j < tupla.at(0).size(); j++) {
				tempStr = tupla[j][i];
				floatfromStr = std::stof(tempStr); ///quité *
				tempArbolFlot.Add(floatfromStr);
			}
			delete (&tempArbolFlot);
			break;
		case 2: //string

			break;

		}
	}
}

//void to_csv(std::string nombreArchivo) {
//}

#endif // !_LIBRERIA_HPP_