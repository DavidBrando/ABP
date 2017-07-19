#pragma once


#include "Objetos.h"


class Botiquines : public Objetos
{
public:
	Botiquines(const glm::vec3 & posicion, const glm::vec3 & rotacion, const glm::vec3 & escala, const int & identificacion, TGraphicEngine *motor);
	~Botiquines();
	float getVida();
	void setFisica(Mundo *world);

private:
	float vida;
};

