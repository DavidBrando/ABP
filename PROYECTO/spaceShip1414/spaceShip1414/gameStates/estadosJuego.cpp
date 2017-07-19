#include "estadosJuego.h"

estadosJuego::estadosJuego()
{
	nombreEstado = "desconocido";
	estadoActivo = false;
}

estadosJuego::estadosJuego(std::string nuevoEstado)
{
	nombreEstado = nuevoEstado;
	estadoActivo = false;
}

estadosJuego::~estadosJuego()
{
}

std::string estadosJuego::getEstado()
{
	return nombreEstado;
}

bool estadosJuego::getEstadoActivo()
{
	return estadoActivo;
}

void estadosJuego::setEstadoActivo(bool activo)
{
	estadoActivo = activo;
}

void estadosJuego::inicializarEstado()
{
}

bool estadosJuego::limpiarEstado()
{
	estadoActivo = false;
	return 0;
}

void estadosJuego::render(void * window)
{
}

void estadosJuego::resize(float width, float height)
{
}

void estadosJuego::handler(void * event, void * window, void * manager)
{
}

void estadosJuego::update(double deltatime, void * window, void * manager)
{
}