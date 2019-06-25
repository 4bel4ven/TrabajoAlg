#pragma once

#ifndef _LIBRERIADF_HPP_
#define _LIBRERIADF_HPP_

#include <fstream>
#include <string>
#include <vector>
#include <list>
#include "hashtable.hpp"
#include "arbol_valor.hpp"

class libreriaDF 
{
private:
	std::vector<std::vector<std::string*>> tupla;

	std::vector<std::list<std::string>*> dataframe;

	std::vector<std::list<int>*> indexacionesColumnas; //aquí estará indexada cada columna	

	size_t* cantidadRegistros;

public:
	libreriaDF() {
		cantidadRegistros = new size_t(0);
	};
	
	~libreriaDF() {};
	
	void from_csv(std::string nombreArchivo, char separacion, int header, unsigned int cantidadColumnas, int valores[]) 
	{//el nombre de archivo va con extension

		std::string temp;

		std::ifstream archivo(nombreArchivo);
		
		while (std::getline(archivo,temp)){ //mientras haya columnas
			std::stringstream ss(archivo);

				std::getline(archivo, temp, separacion);
				dataframe[columna]->push_back(temp3);

				switch (valores[columna]) 
				{
				case 0: //int
					//std::getline(archivo, temp1, separacion);
					
					break;
				case 1: //float
					//std::getline(archivo, temp2, separacion);
					//conjColumnas[i]->push_back(temp2);
					break;
				case 2: //string
					//std::getline(archivo, temp3, separacion);
					//conjColumnas[i]->push_back(temp3);
					break;
				}
		}


	};

	void to_csv(std::string nombreArchivo, char separacion, int header) {};
	
	void indexacolumna_numero(int numeroColumna) {//indexación mediante árbol
		std::list<int> *columna = nullptr;
		
		AVLTree<int>* conjunto=new AVLTree<int>();

		for (std::list<std::string>::iterator it = dataframe[numeroColumna]->begin(); it != dataframe[numeroColumna]->end(); ++it) {
			float val = std::stof(*it);
			conjunto->Add(val);
			columna->push_back(val);
		}
	}

	};
	
	void indexacolumna_float(int numeroColumna){ //indexación mediante árbol
		std::list<float> *columna = nullptr;
		AVLTree<float>* conjunto = new AVLTree<float>();
		
		for(std::list<std::string>::iterator it = dataframe[numeroColumna]->begin(); it != dataframe[numeroColumna]->end(); ++it){
			float val = std::stof(*it);
			conjunto->Add(val);
			columna->push_back(val);

		}
	}

	void indexacolumna_caracter( int numeroColumna){ //indexación mediante hash
		std::list<std::string>* columna = nullptr;

		for (std::list<std::string>::iterator it = dataframe[numeroColumna]->begin(); it != dataframe[numeroColumna]->end(); ++it) {
			
			
		}
	}

	size_t seleccion_busqueda_numero(int numeroColumna, size_t valor) { 
		int fila; 
		return fila;

	}
	size_t seleccion_busqueda_string(int numeroColumna, std::string caracter){



	}

	void campos_busqueda (){}
	size_t * NuevoDF_busquedas(){}
	


};

#endif // !_LIBRERIASDF_HPP_
