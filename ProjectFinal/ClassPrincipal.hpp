#pragma once
#include <string>
#include "arbol_index.hpp"

#ifndef _LIBRERIASDF_HPP_
#define _LIBRERIASDF_HPP_
class libreriaDF {
private:
	size_t* arregloColumnas;
	size_t* cantidad;

public:
	
	libreriaDF() {};
	~libreriaDF() {};

	void from_csv(std::string nombreArchivo, char separacion, int header) {};
	void to_csv(std::string nombreArchivo, char separacion, int header) {};
	void indexing(int numeroColumna) {};
	size_t seleccion_busqueda(int numeroColumna) { int fila; return fila;};
	void campos_busqueda (){};
	size_t * NuevoDF_busquedas(){};
<<<<<<< HEAD

=======
	
>>>>>>> be0d7af831dd78d511f1b0c005e08b4d86fb472e


};

#endif // !_LIBRERIASDF_HPP_
