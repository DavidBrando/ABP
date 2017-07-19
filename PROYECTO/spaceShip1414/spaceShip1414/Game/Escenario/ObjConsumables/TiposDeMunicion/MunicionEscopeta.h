#pragma once

#include "../Municion.h"

class MunicionEscopeta : public Municion
{
public:
	MunicionEscopeta(const glm::vec3 & posicion, const glm::vec3 & rotacion, const glm::vec3 & escala, const int & identificacion, const int &tipoM, const int &balasDeLaCaja, TGraphicEngine *motor);
	~MunicionEscopeta();
	int getMunicion();
	void setFisica(Mundo *world);

private:

	int municion;

};

