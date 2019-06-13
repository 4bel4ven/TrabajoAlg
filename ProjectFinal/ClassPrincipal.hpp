#pragma once
#include <string>

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
	size_t seleccion() { int fila; return fila; };

};

#endif // !_LIBRERIASDF_HPP_
