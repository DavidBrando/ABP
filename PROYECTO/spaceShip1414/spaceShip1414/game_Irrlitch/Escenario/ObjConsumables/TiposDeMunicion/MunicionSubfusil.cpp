

#include "MunicionSubfusil.h"
#include "../../../Fisicas/Entity2D.h"



MunicionSubfusil::MunicionSubfusil(const vector3df & posicion, const vector3df & rotacion, const vector3df & escala, const int & identificacion, IMeshSceneNode * nodo, const int &tipoM, const int &balasDeLaCaja)
	: Municion(posicion, rotacion, escala, identificacion, nodo, tipoM)
{
	municion = balasDeLaCaja;
}


MunicionSubfusil::~MunicionSubfusil()
{
}

int MunicionSubfusil::getMunicion()
{
	return municion;
}

void MunicionSubfusil::setFisica(b2World * world)
{
	entity = new Entity2D(world, pos, rot, scale, this, ID);

}
