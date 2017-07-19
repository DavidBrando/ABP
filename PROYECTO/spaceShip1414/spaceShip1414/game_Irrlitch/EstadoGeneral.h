#pragma once
/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   EstadoGeneral.h
* Author: Hector
*
* Created on 31 de diciembre de 2016, 12:04
*/

#ifndef ESTADOGENERAL_H
#define ESTADOGENERAL_H

#include <string>
#include <irrlicht.h>

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class EstadoGeneral : public IEventReceiver {
protected:
	std::string nombre;
	bool activo;
	bool primero;
	bool control;
public:
	EstadoGeneral(void);
	EstadoGeneral(std::string nuevoNombre);
	virtual ~EstadoGeneral();

	std::string getNombre(void);
	bool EstaActivo(void);
	void setActivo(bool);
	virtual void Inicializar(void);
	virtual void LimpiarEstado(void);
	virtual void Dentro(void) = 0;
	virtual void Fuera(void) = 0;
	virtual bool OnEvent(const SEvent &event) = 0;
	virtual void render(IrrlichtDevice*) = 0;
	virtual void StarUP(IrrlichtDevice*) = 0;


};

#endif /* ESTADOGENERAL_H */

