#pragma once
#ifndef _HEADER_HPP_
#define _HEADER_HPP_
#include <stdio.h>
#include <vector>
#include <string>
#include <sstream> 
#include <fstream>
#include "arbol_AVL.hpp"
class libreria
{
private:
	std::vector<std::vector<std::string*>> tupla;
	std::vector<int> tiposdevalores;
	AVLTree <std::vector<std::vector<std::string*>>*> ordenado;
public:
	libreria();
	~libreria();
	void from_csv(std::string,int,char);
	void pedirdatos();
	void tiposdevalor();
	void to_csv(std::string);

};

libreria::libreria()
{
}

libreria::~libreria()
{
}

void libreria::from_csv(std::string nombreArchivo,int header,char separador) {
	std::string temp;
	std::string registro;
	std::ifstream archivo(nombreArchivo);

	while (std::getline(archivo, registro)) {
		std::stringstream ss(registro);
		std::vector <std::string*> row;
		while (std::getline(ss,temp,separador))
		{
			row.push_back(&temp);
		}
	tupla.push_back(row);
	ordenado.Add(&tupla);
	}
}
void libreria::pedirdatos() {
	std::string archivo;
	std::string extensionotro;
	int opcion=3;
	int cabecera;
	char separadorotro;

	std::cout << "\nintroduzca nombre de archivo (sin extension): ";
	std::getline(std::cin, archivo);
	
	while (opcion >= 3 ||opcion < 0) {
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
		archivo = archivo +'.'+ extensionotro;
	}

	std::cout << "\ncuantas filas son de cabecera: ";
	std::cin >> cabecera;

	switch (opcion)
	{
	case 0:
		from_csv(archivo+".csv",cabecera,',');
		break;
	case 1:
		from_csv(archivo+".tsv", cabecera, '\t');
		break;
	case 2:
		from_csv(archivo, cabecera, separadorotro);
		break;
	default:
		break;
	}
}
void libreria::tiposdevalor() {
	int valor=3;
	for (int i = 0; i < tupla[0].size(); i++)
	{
		while (valor >= 3 || valor < 0) {
		std::cout << "\n[0]entero [1]flotante [2]cadena de texto\nintroduzca el tipo de variable de la columna n " << i + 1 << " :";
			std::cin >> valor;
			if (valor >= 3 ||valor < 0)
				std::cout << "\nERROR, introduzca uno de los valores señalados";
		}
		tiposdevalores.push_back(valor);
	}
}


void to_csv(std::string nombreArchivo) {
}

#endif // !_HEADER_HPP_
