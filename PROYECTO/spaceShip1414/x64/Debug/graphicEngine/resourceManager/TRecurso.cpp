#include "TRecurso.h"

TRecurso::TRecurso()
{
}

TRecurso::TRecurso(std::string n)
{
	this->nombre = n;
}

TRecurso::~TRecurso()
{
}

std::string TRecurso::getNombre()
{
	return this->nombre;
}


void TRecurso::setNombre(std::string n)
{
	this->nombre = n; 
}
