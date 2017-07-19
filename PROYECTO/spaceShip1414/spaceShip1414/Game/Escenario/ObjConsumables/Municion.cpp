

#include "Municion.h"
#include "../Fisicas/Entity2D.h"
#include "../Fisicas/Mundo.h"

Municion::Municion(const glm::vec3 & posicion, const glm::vec3 & rotacion, const glm::vec3 & escala, const int & identificacion, const int &tipoM, TGraphicEngine *motor) :
	Objetos(posicion, rotacion, escala, identificacion, motor)
{
	tipoMunicion = tipoM;
}

Municion::~Municion()
{
}

int Municion::getTipoMunicion()
{
	return tipoMunicion;
}

void Municion::setFisica(Mundo * world)
{
	

}
