/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   EstadoGeneral.cpp
* Author: Hector
*
* Created on 31 de diciembre de 2016, 12:04
*/

#include "EstadoGeneral.h"

EstadoGeneral::EstadoGeneral(void) {
	nombre = "desconocido";
	activo = false;
	primero = true;
}

EstadoGeneral::EstadoGeneral(std::string nuevoNombre)
{
	nombre = nuevoNombre;
	activo = false;
	primero = true;
}

EstadoGeneral::~EstadoGeneral() {
}

std::string EstadoGeneral::getNombre(void)
{
	return nombre;
}

bool EstadoGeneral::EstaActivo(void)
{
	return activo;
}

void EstadoGeneral::setActivo(bool activar)
{
	activo = activar;
}

void EstadoGeneral::Inicializar(void)
{
	activo = true;
	this->Dentro();
}

void EstadoGeneral::LimpiarEstado()
{
	activo = false;
	this->Fuera();
}

