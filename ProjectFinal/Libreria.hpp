
#ifndef _LIBRERIA_HPP_
#define _LIBRERIA_HPP_

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream> 
#include <fstream>
#include <stdio.h>
#include "arbol_AVL.hpp"
#include "hashtable.hpp"

class Clibreria {

private:
	//tupla inicial
	std::vector<std::vector<std::string>> tupla;
	//tupla con seleccion del usuario
	std::vector<std::vector<std::string>> tuplaSeleccionada;
	//alberga los tipos de valores de cada columna
	std::vector<int> tiposdevalores;
	//son pares (int guarda la columna y el otro la indexación de dicha columna)
	std::vector< std::pair<int,hashtable>> busquedaString; 
	//son pares (int guarda la columna y el otro la indexación de dicha columna)
	std::vector<std::pair<int,AVLTree<int>>> busquedaInt; //son pares 
	//son pares (int guarda la columna y el otro la indexación de dicha columna)
	std::vector<std::pair<int,AVLTree<float>>> busquedaFloat;//son pares 

	///-------------funciones privadas------------------///
	void printTu(std::vector<std::vector<std::string>> tuplaPRINT); ///pasar a private
public:

	Clibreria() {
	}
	~Clibreria() {}

	void from_csv(std::string nombreArchivo, int header, char separador);  ///pasar a private
	void pedirdatos();
	void tiposdevalor();
	void indexar();
	void iniciarSeleccion();
	std::vector<std::vector<std::string>> seleccion(std::vector<int> column);  ///pasar a private
	void printPos(std::vector<int> posiciones);  ///pasar a private
	void imprimir();
	std::vector<int> filtrado_mayorque(int column, std::string valor, std::vector<std::vector<std::string>>tuplaF);
	void filtrado_menorque(int column, std::string valor, std::vector<std::vector<std::string>>tuplaF);
	void filtrado_igualque(int column, std::string valor, std::vector<std::vector<std::string>>tuplaF);
	void filtrado();
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
	for (int i = 0; i < tiposdevalores.size(); i++) { //columnas

		int opcion = tiposdevalores.at(i);
		std::string tempStr; ///convertí a string normal


		if (opcion == 0) {
			int intfromStr;
			AVLTree<int> tempArbolInt;
			std::pair<int, AVLTree<int>> Pos_tempArbolInt;
			
			for (int j = 0; j < tupla.size(); j++) { //filas
				tempStr = tupla[j][i];
				intfromStr = std::stoi(tempStr); ///quité *
				tempArbolInt.Add(intfromStr,j);
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
				tempArbolFlot.Add(floatfromStr,j);
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
				tempArbolString.insercion(tempStr,j);
			};
			Pos_tempArbolString.first = i;
			Pos_tempArbolString.second = tempArbolString;

			busquedaString.push_back(Pos_tempArbolString);

		};
	}
}

void Clibreria::iniciarSeleccion() {
	int cantidad,valor;
	std::vector<int> valores;
	std::cout << "Cuantas columnas quiere seleccíonar: ";
	std::cin >> cantidad;
	std::cout << "\n---OJO: aparecerán las columnas en el orden que las escribas---";
	for (int i = 0; i < cantidad; i++) {
		if (i == 0) {
			std::cout << "\nescribe la " << i + 1 << "° columna: ";
			std::cin >> valor;
			valores.push_back(valor);
		}
		else {
			step2:
			std::cout << "\nescribe la " << i + 1 << "° columna: ";
			std::cin >> valor;
			for (int j = 0; j < i; j++) {
				if (valor == valores.at(j)) {
					std::cout << "---ya has escrito esta columna---";
					goto step2;
				};
			};
			valores.push_back(valor);
		};
	}
	tuplaSeleccionada = seleccion(valores);
}

std::vector<std::vector<std::string>> Clibreria::seleccion(std::vector<int> column) {
	
	std::vector<std::vector<std::string>> tuplaTemp;

	for (int i = 0; i < column.size(); i++) {
		int numeroCol = column.at(i);
		tuplaTemp.push_back(tupla.at(numeroCol));
	};
	return tuplaTemp;
		/*
		int j = 0;
		int tipovalor = tiposdevalores.at(i);
		if (tipovalor == 0) {
			while (numeroCol != busquedaInt.at(j).first) {
				++j;
			}


		}
		else if (tipovalor == 1) {
			while (numeroCol != busquedaFloat.at(j).first) {
				++j;
			}
		}
		else {
			while (numeroCol != busquedaString.at(j).first) {
				++j;
			}
		};
		for (int j = 0; j < tiposdevalores.size(); j++) {
		};*/
}

void Clibreria::printTu(std::vector<std::vector<std::string>> tuplaPRINT) {
	std::string valor;
	int valor1 = tuplaPRINT.at(0).size(); //col
	int valor2 = tuplaPRINT.size(); //fila
	for (int i = 0; i < tuplaPRINT.size(); i++) { //filas
		for (int j = 0; j < tuplaPRINT.at(0).size(); j++) { //columnas
			valor = tuplaPRINT[i][j];
			if (j==0 ) std::cout << "\n" << valor;
			else std::cout << "\t" << valor;
		};
	};
}
void Clibreria::printPos(std::vector<int> posiciones) {

}

void Clibreria::imprimir() {
	printTu(tupla);
}

std::vector<int> Clibreria::filtrado_mayorque(int column, std::string valor, std::vector<std::vector<std::string>>tuplaF) {
	std::vector<int> tempLista;
	if (tiposdevalores.at(column) == 0) {
	
	}
	else if (tiposdevalores.at(column) == 1) {
	};
}
void Clibreria::filtrado_menorque(int column, std::string valor,std::vector<std::vector<std::string>>tuplaF) {

}
void Clibreria::filtrado_igualque(int column, std::string valor,std::vector<std::vector<std::string>>tuplaF) {

}


//void to_csv(std::string nombreArchivo) {
//}

#endif // !_LIBRERIA_HPP_