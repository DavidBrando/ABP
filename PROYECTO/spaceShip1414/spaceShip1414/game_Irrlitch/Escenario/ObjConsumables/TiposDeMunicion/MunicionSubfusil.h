#pragma once

#include "../Municion.h"

class MunicionSubfusil : public Municion
{
public:
	MunicionSubfusil(const vector3df & posicion, const vector3df & rotacion, const vector3df & escala, const int & identificacion, IMeshSceneNode * nodo, const int &tipoM, const int &balasDeLaCaja);
	~MunicionSubfusil();
	int getMunicion();
	void setFisica(b2World *world);

private:

	int municion;

};

