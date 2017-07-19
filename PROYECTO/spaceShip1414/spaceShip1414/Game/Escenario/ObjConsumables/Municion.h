#pragma once


#include "Objetos.h"



class Municion : public Objetos
{
public:
	Municion(const glm::vec3 & posicion, const glm::vec3 & rotacion, const glm::vec3 & escala, const int & identificacion, const int &tipoM, TGraphicEngine *motor);
	~Municion();
	int getTipoMunicion();
	virtual void setFisica(Mundo *world);

protected:

	int tipoMunicion;

};

