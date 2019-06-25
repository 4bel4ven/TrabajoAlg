#pragma once
#ifndef _VALOR_HPP_
#define _VALOR_HPP_
#include <list>
template<typename T>
class valor {
private:
	std::list<T> valoresColumna;
public:
	valor() {};
	void agregar(T e) { valoresColumna->push_back(e); }
}
#endif // !_VALOR_HPP_
