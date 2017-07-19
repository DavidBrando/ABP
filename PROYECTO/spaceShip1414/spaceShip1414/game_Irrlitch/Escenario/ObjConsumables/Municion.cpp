

#include "Municion.h"
#include "../../Fisicas/Entity2D.h"


Municion::Municion(const vector3df & posicion, const vector3df & rotacion, const vector3df & escala, const int & identificacion, IMeshSceneNode * nodo, const int &tipoM) :
	Objetos(posicion, rotacion, escala, identificacion, nodo)
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

void Municion::setFisica(b2World * world)
{
	

}
