#include "Estados.h"



Estados::Estados()
{
	nombreEstado = "desconocido";
	estadoActivo = false;
	primerEstado = true;
}

Estados::Estados(std::string nuevoEstado)
{
	nombreEstado = nuevoEstado;
	estadoActivo = false;
	primerEstado = true;
}

Estados::~Estados()
{
}

std::string Estados::getEstado()
{
	return nombreEstado;
}

bool Estados::getEstadoActivo()
{
	return estadoActivo;
}

void Estados::setEstadoActivo(bool activo)
{
	estadoActivo = activo;
}

void Estados::inicializarEstado()
{
	estadoActivo = true;

}

void Estados::limpiarEstado()
{
	estadoActivo = false;
}
