#include "MaquinaEstadosJuego.h"
#include "estadosJuego.h"
#include <iostream>

MaquinaEstadosJuego::MaquinaEstadosJuego()
{
}

MaquinaEstadosJuego::~MaquinaEstadosJuego()
{
	listaEstados.clear();
	std::cout << "MaquinaEstadosJuego Destroyed" << std::endl;
}

void MaquinaEstadosJuego::addEstado(estadosJuego * nombreEstados, bool activo)
{
	listaEstados.push_back(nombreEstados);

	if (activo)
	{
		nombreEstados->setEstadoActivo(true);
		nombreEstados->inicializarEstado();
		estadoActivo = nombreEstados;
	}
}

void MaquinaEstadosJuego::cambiaEstado(const std::string nombre)
{
	if (!listaEstados.empty())
	{
		reniciar = getEstadoActivo()->limpiarEstado();
		getEstadoActivo()->setEstadoActivo(false);
		for (std::size_t i = 0; i < listaEstados.size(); i++)
		{
			if (nombre == listaEstados[i]->getEstado())
			{
				listaEstados[i]->setEstadoActivo(true);
				listaEstados[i]->inicializarEstado();
				activarEstado(listaEstados[i]);
			}
		}
	}
}

estadosJuego * MaquinaEstadosJuego::getEstadoActivo()
{
	return estadoActivo;
}

estadosJuego * MaquinaEstadosJuego::getEstado(const std::string nombre)
{
	if (!listaEstados.empty())
	{
		for (std::size_t i = 0; i < listaEstados.size(); i++)
		{
			if (listaEstados[i]->getEstado() == nombre)
			{
				return listaEstados[i];
			}
		}
	}
	return nullptr;
}

void MaquinaEstadosJuego::borrarEstado(const std::string nombre)
{
	if (!listaEstados.empty())
	{
		for (std::vector<estadosJuego*>::iterator it = listaEstados.begin(); it != listaEstados.end(); ++it)
		{
			if ((*it)->getEstado() == nombre) { listaEstados.erase(it); break; }
		}
	}
}

bool MaquinaEstadosJuego::reniciarEstado()
{
	return reniciar;
}

void MaquinaEstadosJuego::activarEstado(estadosJuego * estado)
{
	estadoActivo = estado;
}