

#include "Nodo.h"



Nodo::Nodo(std::string name, vector3df position, int place)
{
	nombre = name;
	pos = position;
	lugar = place;

}


Nodo::~Nodo()
{
}

bool Nodo::operator==(const Nodo & n) const
{
	return (this->nombre.compare(n.nombre) == 0);
}

bool Nodo::operator!=(const Nodo & n) const
{
	return (this->nombre.compare(n.nombre) != 0);
}

std::string Nodo::getNombre()
{
	return nombre;
}

vector3df Nodo::getPosicion()
{
	return pos;
}

int Nodo::getLugarDelNodo()
{
	return lugar;
}


