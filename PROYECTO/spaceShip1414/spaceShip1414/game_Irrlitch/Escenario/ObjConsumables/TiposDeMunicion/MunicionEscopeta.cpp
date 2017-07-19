
#include "MunicionEscopeta.h"
#include "../../../Fisicas/Entity2D.h"


MunicionEscopeta::MunicionEscopeta(const vector3df & posicion, const vector3df & rotacion, const vector3df & escala, const int & identificacion, IMeshSceneNode * nodo, const int &tipoM, const int &balasDeLaCaja)
	: Municion(posicion, rotacion, escala, identificacion, nodo, tipoM)
{
	municion = balasDeLaCaja;
}


MunicionEscopeta::~MunicionEscopeta()
{
}

int MunicionEscopeta::getMunicion()
{
	return municion;
}

void MunicionEscopeta::setFisica(b2World * world)
{
	entity = new Entity2D(world, pos, rot, scale, this, ID);

}
