#pragma once

#include "../Municion.h"

class MunicionEscopeta : public Municion
{
public:
	MunicionEscopeta(const vector3df & posicion, const vector3df & rotacion, const vector3df & escala, const int & identificacion, IMeshSceneNode * nodo, const int &tipoM, const int &balasDeLaCaja);
	~MunicionEscopeta();
	int getMunicion();
	void setFisica(b2World *world);

private:

	int municion;

};

