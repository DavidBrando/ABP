#include "Estados.h"



Estados::Estados()
{
	nombreEstado = "desconocido";
	pathAnimacion = "desconocido";
	estadoActivo = false;
	primerEstado = true;
}

Estados::Estados(std::string nuevoEstado)
{
	nombreEstado = nuevoEstado;
	pathAnimacion = "desconocido";
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

std::string Estados::getPathAnimacion()
{
	return pathAnimacion;
}

void Estados::asignarPath(std::string path)
{
	pathAnimacion = path;
}
