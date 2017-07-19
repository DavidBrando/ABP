#pragma once


#include "Objetos.h"



class Municion : public Objetos
{
public:
	Municion(const vector3df & posicion, const vector3df & rotacion, const vector3df & escala, const int & identificacion, IMeshSceneNode *nodo, const int &tipoM);
	~Municion();
	int getTipoMunicion();
	virtual void setFisica(b2World *world);

protected:

	int tipoMunicion;

};

