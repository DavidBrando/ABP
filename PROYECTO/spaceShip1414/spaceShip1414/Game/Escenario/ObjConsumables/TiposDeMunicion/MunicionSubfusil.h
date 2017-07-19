#pragma once

#include "../Municion.h"

class MunicionSubfusil : public Municion
{
public:
	MunicionSubfusil(const glm::vec3 & posicion, const glm::vec3 & rotacion, const glm::vec3 & escala, const int & identificacion, const int &tipoM, const int &balasDeLaCaja, TGraphicEngine *motor);
	~MunicionSubfusil();
	int getMunicion();
	void setFisica(Mundo *world);

private:

	int municion;

};

