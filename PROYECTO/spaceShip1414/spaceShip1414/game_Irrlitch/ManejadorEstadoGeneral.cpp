/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   ManejadorEstadoGeneral.cpp
* Author: Hector
*
* Created on 10 de enero de 2017, 17:27
*/

#include "ManejadorEstadoGeneral.h"


ManejadorEstadoGeneral::ManejadorEstadoGeneral(void) {

}

ManejadorEstadoGeneral::ManejadorEstadoGeneral(const ManejadorEstadoGeneral&)
{
}

ManejadorEstadoGeneral::~ManejadorEstadoGeneral() {
}

bool ManejadorEstadoGeneral::Inicializar(int width, int heigth, bool fullscreen)
{
	irrlichtDevice = createDevice(EDT_OPENGL, dimension2d<u32>(width, heigth), 32, false, 0);

	if (irrlichtDevice)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ManejadorEstadoGeneral::Finalizar()
{
	irrlichtDevice->closeDevice();
	irrlichtDevice->drop();

	return true;
}

IrrlichtDevice* ManejadorEstadoGeneral::getDevice()
{
	return irrlichtDevice;
}

bool ManejadorEstadoGeneral::EstaEjecutando(void)
{
	return irrlichtDevice->run();
}

void ManejadorEstadoGeneral::AddEstado(EstadoGeneral* NuevoEstado, bool activo)
{
	EstadosJuego.push_back(NuevoEstado);

	if (activo)
	{
		NuevoEstado->setActivo(true);
		device->setEventReceiver(NuevoEstado);//illoooo
		NuevoEstado->Inicializar();
	}
}

void ManejadorEstadoGeneral::CambiaEstado(const std::string nombre)
{
	for (int i = 0; i<EstadosJuego.size(); i++)
	{
		if (nombre == EstadosJuego[i]->getNombre())
		{
			if (this->getEstadoActivo() != NULL)
			{
				this->getEstadoActivo()->LimpiarEstado();
			}

			device->setEventReceiver(EstadosJuego[i]);
			EstadosJuego[i]->Inicializar();

		}
	}
}

EstadoGeneral* ManejadorEstadoGeneral::getEstadoActivo()
{
	for (int i = 0; i<EstadosJuego.size(); i++)
	{
		if (EstadosJuego[i]->EstaActivo())
		{
			return EstadosJuego[i];
		}
	}

	return NULL;
}

EstadoGeneral* ManejadorEstadoGeneral::getEstadoGeneral(const std::string nombre)
{
	for (int i = 0; i<EstadosJuego.size(); i++)
	{
		if (nombre == EstadosJuego[i]->getNombre())
		{
			return EstadosJuego[i];
		}
	}

	return NULL;
}

void ManejadorEstadoGeneral::EmpezarRender()
{
	irrlichtDevice->getVideoDriver()->beginScene(true, true, SColor(255, 255, 255, 255));
}

void ManejadorEstadoGeneral::AcabarRender()
{
	irrlichtDevice->getVideoDriver()->endScene();
}

void ManejadorEstadoGeneral::Render()
{
	if (this->getEstadoActivo() != NULL)
	{
		this->getEstadoActivo()->render(device);
	}

}

