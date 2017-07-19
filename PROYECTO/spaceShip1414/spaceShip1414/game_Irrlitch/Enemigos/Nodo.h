#pragma once

#include <string>
#include <irrlicht.h>

using namespace irr;
using namespace core;

class Nodo
{
public:
	Nodo(std::string name, vector3df position, int place);
	~Nodo();
	bool operator==(const Nodo& n) const;
	bool operator!=(const Nodo& n) const;
	std::string getNombre();
	vector3df getPosicion();
	int getLugarDelNodo();


private: 

		std::string nombre;
		vector3df pos;
		int lugar;

};

