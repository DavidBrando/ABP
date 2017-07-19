

#include "Nodo.h"



Nodo::Nodo(std::string name, glm::vec3 position, int place)
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

glm::vec3 Nodo::getPosicion()
{
	return pos;
}

int Nodo::getLugarDelNodo()
{
	return lugar;
}


