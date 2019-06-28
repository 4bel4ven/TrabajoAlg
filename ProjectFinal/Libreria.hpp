
#ifndef _LIBRERIA_HPP_
#define _LIBRERIA_HPP_
#include <conio.h>
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
	void pedirtiposdevalor();
	void indexar();
	void iniciarSeleccion();
	std::vector<std::vector<std::string>> seleccion(std::vector<int> column);  ///pasar a private
	void printPos(std::vector<int*> posiciones);  ///pasar a private
	void imprimir();
	void pedirFiltrado();
	std::vector<int*> filtrado_mayorque(int column, std::string valor);
	std::vector<int*> filtrado_menorque(int column, std::string valor);
	std::vector<int*> filtrado_igualque(int column, std::string valor);

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
	std::cin >> archivo;
	//std::getline(std::cin, archivo);

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
		std::cin >> extensionotro;
		//std::getline(std::cin, extensionotro);
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

void Clibreria::pedirtiposdevalor()
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
				tempArbolInt.Add(intfromStr,new int(j));
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
				tempArbolFlot.Add(floatfromStr,&j);
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
	printTu(tuplaSeleccionada);
	std::cin.ignore();
	std::cin.get();
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

void Clibreria::printPos(std::vector<int*> posiciones) {
	std::string valor;
	for (int i = 0; i < posiciones.size(); i++) { 
		int pos = *posiciones.at(i);					//filas
		for (int j = 0; j < tupla.at(0).size(); j++) { //columnas
			valor = tupla[pos][j];
			if (j == 0) std::cout << "\n" << valor;
			else std::cout << "\t" << valor;
		};
	};
}

void Clibreria::imprimir() {
	printTu(tupla);
}

void Clibreria::pedirFiltrado() {
	int opcion,valor,columna,elemento;
	std::vector <int> columnas, elementos;
	std::vector <int*> columnasFiltro;
	do {
		std::cout << "\nMENU DE OPCIONES:\tOJO, 1-2-3 (para datos numéricos) y 4 (para datos de texto)\n1.Mayor\n2.Menor\n3.Igual a\n4.Inicia con\nSu respuesta";
		std::cin >> opcion;
		if (opcion > 4 || opcion < 1) std::cout << "ERROR, NUMERO NO VALIDO";
	} while (opcion > 4 || opcion < 1);

	if (opcion == 2) { //menor que
		do {
			std::cout << "\nEn cuántas columnas quieres buscar (1 o 2)";
			std::cin >> valor;
			if (valor > 2 || valor < 1) std::cout << "ERROR, NUMERO NO VALIDO";
		} while (valor > 2 || valor < 1);

		if (valor == 1) { //cuando es una columna
			std::cout << "\nQué columna es:";
			std::cin >> columna;
			std::cout << "\nQué valor es:";
			std::cin >> elemento;

			columnasFiltro = filtrado_menorque(columna, std::to_string(elemento));
			printPos(columnasFiltro);
		}
		else { //cuando sean dos columnas

		};

	}
	else if (opcion == 1) { //mayor que
		do {
			std::cout << "\nEn cuántas columnas quieres buscar (1 o 2)";
			std::cin >> valor;
			if (valor > 2 || valor < 1) std::cout << "ERROR, NUMERO NO VALIDO";
		} while (valor > 2 || valor < 1);
		if (valor == 1) { //cuando es una columna
			std::cout << "\nQué columna es:";
			std::cin >> columna;
			std::cout << "\nQué valor es:";
			std::cin >> elemento;

			columnasFiltro = filtrado_mayorque(columna, std::to_string(elemento));
			printPos(columnasFiltro);
		}
		else { //cuando sean dos columnas

		};
	}
	else if (opcion == 3) { //igual
		do {
			std::cout << "\nEn cuántas columnas quieres buscar (1 o 2)";
			std::cin >> valor;
			if (valor > 2 || valor < 1) std::cout << "ERROR, NUMERO NO VALIDO";
		} while (valor > 2 || valor < 1);
		if (valor == 1) { //cuando es una columna
			std::cout << "\nQué columna es:";
			std::cin >> columna;
			std::cout << "\nQué valor es:";
			std::cin >> elemento;

			columnasFiltro = filtrado_igualque(columna, std::to_string(elemento));
			printPos(columnasFiltro);
		}
		else { //cuando sean dos columnas

		};
	}
	else if (opcion == 4) { //empieza con
		
	};
}

std::vector<int*> Clibreria::filtrado_mayorque(int column, std::string valor) {
	std::vector<int*> tempLista;
	std::vector<float*> tempLista1;
	if (tiposdevalores.at(column) == 0) {
		AVLTree<int> temp;
		for (int i = 0; i < busquedaInt.size(); i++)
			if (busquedaInt.at(i).first == column) {
				temp = busquedaInt.at(i).second;
				goto step3;
			};
	step3:
		tempLista = temp.Greater_Than(std::stoi(valor));
		return tempLista;
	}
	else if (tiposdevalores.at(column) == 1) {
		AVLTree<float> temp;
		for (int i = 0; i < busquedaFloat.size(); i++)
			if (busquedaFloat.at(i).first == column) {
				temp = busquedaFloat.at(i).second;
				goto step4;
			};
	step4:
		tempLista = temp.Greater_Than(std::stof(valor));
		return tempLista;
	};
}

std::vector<int*> Clibreria::filtrado_menorque(int column, std::string valor) {
	std::vector<int*> tempLista;
	std::vector<float*> tempLista1;
	if (tiposdevalores.at(column) == 0) {
		AVLTree<int> temp;
		for (int i = 0; i < busquedaInt.size(); i++)
			if (busquedaInt.at(i).first == column) {
				temp = busquedaInt.at(i).second;
				goto step5;
			};
	step5:
		tempLista= temp.Smaller_Than( std::stoi(valor));
		return tempLista;
	}
	else if (tiposdevalores.at(column) == 1) {
		AVLTree<float> temp;
		for (int i = 0; i < busquedaFloat.size(); i++)
			if (busquedaFloat.at(i).first == column) {
				temp = busquedaFloat.at(i).second;
				goto step6;
			};
	step6:
		tempLista = temp.Smaller_Than(std::stof(valor));
		return tempLista;
	};
}
std::vector<int*> Clibreria::filtrado_igualque(int column, std::string valor) {
	std::vector<int*> tempLista;
	std::vector<float*> tempLista1;
	if (tiposdevalores.at(column) == 0) {
		AVLTree<int> temp;
		for (int i = 0; i < busquedaInt.size(); i++)
			if (busquedaInt.at(i).first == column) {
				temp = busquedaInt.at(i).second;
				goto step7;
			};
	step7:
		tempLista = temp.Find(std::stoi(valor));
		return tempLista;
	}
	else if (tiposdevalores.at(column) == 1) {
		AVLTree<float> temp;
		for (int i = 0; i < busquedaFloat.size(); i++)
			if (busquedaFloat.at(i).first == column) {
				temp = busquedaFloat.at(i).second;
				goto step8;
			};
	step8:
		tempLista = temp.Find(std::stof(valor));
		return tempLista;
	};
}


//void to_csv(std::string nombreArchivo) {
//}

#endif // !_LIBRERIA_HPP_