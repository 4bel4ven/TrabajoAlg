#pragma once

#ifndef _LIBRERIASDF_HPP_
#define _LIBRERIASDF_HPP_

#include <fstream>
#include <string>
#include <vector>
#include "arbol_index.hpp"

template<typename T>
class libreriaDF {
private:
	std::vector<Std::vector<T>>* arregloColumnas;
	std::vector<Std::vector<T>>* arregloIndexaciones; //aquí estará indexada cada columna
	size_t* cantidad;
	int* column_int;
	int* column_float;
	int* column_string;
public:
	
	libreriaDF() 
	{
		cantidad = new size_t(0);
		arregloColumnas = nullptr;
		arregloIndexaciones = nullptr;
		column_float=nullptr;
		column_int=nullptr;
		column_string=nullptr;
	};
	
	~libreriaDF() {};

	
	
	//void set_column_int(int cant, int valores[cant]){column_int=valores;}
	//
	//void set_column_float(int cantidad, int valores[cantidad]){column_float=valores;}
	//
	//void set_column_string(int cantidad, int valores[cantidad]){column_string=valores;}

	void from_csv(std::string nombreArchivo, char separacion, int header, int cantidadColumnas, int valores[cantidadColumnas]) 
	{//el nombre de archivo va con extension

		int valor=0;
		int temp1;
		float temp2;
		std::string temp3;
		std::ifstream archivo(nombreArchivo);
		
		while (std::getline(archivo,temp)){ //mientras haya columnas
			for (int i=0;i<cantidadColumnas;i++) //leer todas las columnas
			{switch valores[i]:
			case 0: //int
				std::getline(archivo, temp1, separacion);
				arregloColumnas[i].pushback(temp1);
				break;
			case 1: //float
				std::getline(archivo, temp2, separacion);
				arregloColumnas[i].pushback(temp2);
				break;
			case 2: //string
				std::getline(archivo, temp3, separacion);
				arregloColumnas[i].pushback(temp3);
				break;
			}
		}
		std::vector<int> columna+valor;
		std::vector<std::string> columna+valor;
		std::vector<float> columna+valor;

		 };
	void to_csv(std::string nombreArchivo, char separacion, int header) {};
	
	void indexacolumna_numero(unsigned int numeroColumna) { //usar arbol
		std::vector<int> *columna = nullptr;
		columna = arregloColumnas[numeroColumna];


	};
	void indexacolumna_float(unsigned int numeroColumna){
		std::vector<int> *columna = nullptr;
		columna = arregloColumnas[numeroColumna];
	}

	void indexacolumna_caracter(unsigned int numeroColumna){ //usar hash

	}

	size_t seleccion_busqueda_numero(int numeroColumna, size_t valor) { int fila; return fila;};
	size_t seleccion_busqueda_string(int numeroColumna, std::string caracter){};

	void campos_busqueda (){};
	size_t * NuevoDF_busquedas(){};
	


};

#endif // !_LIBRERIASDF_HPP_
