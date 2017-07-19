#pragma once

#include "Objetos.h"

class Llave : public Objetos
{
public:
	Llave(const glm::vec3 & posicion, const glm::vec3 & rotacion, const glm::vec3 & escala, const int & identificacion, std::string nombreHabitacion, TGraphicEngine *motor);
	~Llave();
	void setFisica(Mundo *world);
	std::string getNombreHabitacion();

private:
	std::string nombre;
};

