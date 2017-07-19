#pragma once
/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   ManejadorEstadoGeneral.h
* Author: Hector
*
* Created on 10 de enero de 2017, 17:26
*/

#ifndef MANEJADORESTADOGENERAL_H
#define MANEJADORESTADOGENERAL_H

#define manager	ManejadorEstadoGeneral::getInstancia()
#define device	ManejadorEstadoGeneral::getInstancia().getDevice()

#include <string>
#include <irrlicht.h>
#include <vector>
#include "EstadoGeneral.h"


using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class ManejadorEstadoGeneral {
private:
	IrrlichtDevice* irrlichtDevice;
	vector<EstadoGeneral*> EstadosJuego;

private:
	ManejadorEstadoGeneral(void);
	ManejadorEstadoGeneral(const ManejadorEstadoGeneral&);
	virtual ~ManejadorEstadoGeneral(void);
	ManejadorEstadoGeneral operator =(const ManejadorEstadoGeneral&);

public:
	static ManejadorEstadoGeneral& getInstancia(void)
	{
		static ManejadorEstadoGeneral instancia;
		return(instancia);
	}
public:

	bool Inicializar(int width, int heigth, bool fullscreen);
	bool Finalizar(void);

	IrrlichtDevice* getDevice(void);

	bool EstaEjecutando(void);
	void AddEstado(EstadoGeneral* NuevoEstado, bool activo = false);
	void CambiaEstado(const std::string nombre);
	EstadoGeneral* getEstadoActivo(void);
	EstadoGeneral* getEstadoGeneral(const std::string nombre);
	void EmpezarRender(void);
	void AcabarRender(void);
	void Render(void);



};

#endif /* MANEJADORESTADOGENERAL_H */

