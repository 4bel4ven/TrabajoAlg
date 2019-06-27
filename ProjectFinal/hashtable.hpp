#pragma once
#ifndef _HASHTABLE_HPP_
#define _HASHTABLE_HPP_

#include <vector>
#include <iostream>
#include <list>
#include <string>
#include <fstream>


class hashtable {
private:
	std::vector <std::list<std::string>*> hash;
	std::vector<int> posi;
public:
	void iniciaHash() {
		for (int c = 0; c < 10; ++c)
			hash.push_back(new std::list<std::string>);
	}
	int obtenerHash(std::string v) {
		int sum = 0, t;
		for (auto c : v) {
			t = (int)c;
			sum += t;
		}
		return sum % 10;
	}
	void insercion(std::string value,int pos) {

		int key = obtenerHash(value);
		hash.at(key)->push_back(value);
	}



	bool existe(std::string v) {
		int t = obtenerHash(v);
		bool band = false;
		for (std::list<std::string>::iterator i = hash[t]->begin(); i != hash[t]->end() && band == false; ++i) {
			if (*i == v)band = true;
		}
		return band;
	}

	void erase() {
		hash.clear();
	}
};

#endif // !_HASHTABLE_HPP_