#pragma once


#include "Objetos.h"


class Botiquines : public Objetos
{
public:
	Botiquines(const vector3df & posicion, const vector3df & rotacion, const vector3df & escala, const int & identificacion, IMeshSceneNode *nodo);
	~Botiquines();
	float getVida();
	void setFisica(b2World *world);

private:
	float vida;
};

