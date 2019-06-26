
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

	std::vector< std::pair<int,hashtable>> busquedaString;  //son pares para saber qué columna son

	std::vector<std::pair<int,AVLTree<int>>> busquedaInt;

	std::vector<std::pair<int,AVLTree<float>>> busquedaFloat;

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
		do {
			std::cout << "\n[0]entero [1]flotante [2]cadena de texto\nintroduzca el tipo de variable de la columna n " << i + 1 << " :";
			std::cin >> valor;
			if (valor >= 3 || valor < 0)
				std::cout << "\nERROR, introduzca uno de los valores señalados";
		} while (valor >= 3 || valor < 0);
		tiposdevalores.push_back(valor);
	}
}

void Clibreria::indexar()
{
	for (int i = 0; i < tiposdevalores.size(); i++) {

		int opcion = tiposdevalores.at(i);
		std::string tempStr; ///convertí a string normal


		if (opcion == 0) {
			int intfromStr;
			AVLTree<int> tempArbolInt;
			std::pair<int, AVLTree<int>> Pos_tempArbolInt;
			
			for (int j = 0; j < tupla.size(); j++) {
				tempStr = tupla[j][i];
				intfromStr = std::stoi(tempStr); ///quité *
				tempArbolInt.Add(intfromStr);
			};
			Pos_tempArbolInt.first=i;
			Pos_tempArbolInt.second = tempArbolInt;

			busquedaInt.push_back(Pos_tempArbolInt);
		}
		else if(opcion == 1) {

			float floatfromStr;
			AVLTree<float> tempArbolFlot;
			std::pair<int, AVLTree<float>> Pos_tempArbolFlot;

			for (int j = 0; j < tupla.size(); j++) {
				tempStr = tupla[j][i];
				floatfromStr = std::stof(tempStr); ///quité *
				tempArbolFlot.Add(floatfromStr);
			};
			Pos_tempArbolFlot.first =i;
			Pos_tempArbolFlot.second = tempArbolFlot;

			busquedaFloat.push_back(Pos_tempArbolFlot);
		}
		else {

		hashtable tempArbolString;
		tempArbolString.iniciaHash();
		std::pair<int, hashtable> Pos_tempArbolString;

			for (int j = 0; j < tupla.size(); j++) {
				tempStr = tupla[j][i];
				tempArbolString.insercion(tempStr);
			};
			Pos_tempArbolString.first = i;
			Pos_tempArbolString.second = tempArbolString;

			busquedaString.push_back(Pos_tempArbolString);

		};
		switch (opcion) {
		
		case 0: //enteros
			
			
			

			break;
		case 1: //flotantes
		
			break;
		case 2: //string
			break;

		}
	}
}

//void to_csv(std::string nombreArchivo) {
//}

#endif // !_LIBRERIA_HPP_