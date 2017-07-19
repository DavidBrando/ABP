#pragma once

#include "Objetos.h"

class Llave : public Objetos
{
public:
	Llave(const vector3df & posicion, const vector3df & rotacion, const vector3df & escala, const int & identificacion, IMeshSceneNode *nodo, std::string nombreHabitacion);
	~Llave();
	void setFisica(b2World *world);
	std::string getNombreHabitacion();

private:
	std::string nombre;
};

