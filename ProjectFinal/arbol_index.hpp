#pragma once
#ifndef _ARBOL_INDEX_HPP_
#define _ARBOL_INDEX_HPP_
template <class T>
class CNodo
{
private:
	T elemento;
	CNodo<T>* hijoDer;
	CNodo<T>* hijoIzq;
public:
	CNodo() {}
	~CNodo() {}
	
    CNodo(T e) {
		elemento = e;
		hijoDer = nullptr;
		hijoIzq = nullptr;
	}
	T getElemento() { return elemento; }
	CNodo<T>*& getHD() { return hijoDer; }
	CNodo<T>*& getHI() { return hijoIzq; }
	void seTElemento(T e) {
		elemento = e;
	}
	void setHD(CNodo<T>* d) { hijoDer = d; }
	void setHI(CNodo<T>* i) { hijoIzq = i; }


};

template <class T>
class arbol_index{
private:
	void _enOrden(CNodo<T>*& nodo) {
		if (nodo == nullptr) return;
		else {
			_enOrden(nodo->getHI());
			cout<<nodo->getElemento()<< " ";
			_enOrden(nodo->getHD());
		}
	}
	void _preOrden(CNodo<T>*& nodo) {
		if (nodo == nullptr) return;
		else {
			cout << nodo->getElemento() << " ";
			_preOrden(nodo->getHI());
			_preOrden(nodo->getHD());
		}
	}
	void _postOrden(CNodo<T>*& nodo) {
		if (nodo == nullptr) return;
		else {
			_postOrden(nodo->getHI());
			_postOrden(nodo->getHD());
			cout << nodo->getElemento() << " ";
		}
	}

	void _insertar(CNodo<T>*& nodo, X e) {
		if (nodo == nullptr)
					nodo = new CNodo<X>(e);		
		else if (e <= nodo->getElemento()) 
			_insertar(nodo->getHI(), e);
		else
			_insertar(nodo->getHD(), e);
	}
	CNodo<T>* raiz;
public:
	CArbol() {
		raiz = nullptr;
	}
	~CArbol() {}
	void insertar(T e) {
		_insertar(raiz, e);
	}
	void enOrden() {
		_enOrden(raiz);
	}
	void preOrden() {
		_preOrden(raiz);
	}
	void postOrden() {
		_postOrden(raiz);
	}

};
#endif