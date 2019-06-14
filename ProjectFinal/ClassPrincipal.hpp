#pragma once

#ifndef _LIBRERIASDF_HPP_
#define _LIBRERIASDF_HPP_

#include <string>
#include <vector>
#include "arbol_index.hpp"

template<typename T>
class libreriaDF {
private:
	std::vector<Std::vector<T>>* arregloColumnas;
	std::vector<Std::vector<T>>* arregloIndexaciones; //aquí estará indexada cada columna
	size_t* cantidad;
public:
	
	libreriaDF() {
		cantidad = new size_t(0);
		arregloColumnas = nullptr;
		arregloIndexaciones = nullptr;
		};
	~libreriaDF() {};

	void from_csv(std::string nombreArchivo, char separacion, int header) {};
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
