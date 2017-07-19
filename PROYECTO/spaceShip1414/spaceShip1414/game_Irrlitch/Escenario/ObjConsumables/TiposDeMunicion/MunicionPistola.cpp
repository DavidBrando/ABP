

#include "MunicionPistola.h"
#include "../../../Fisicas/Entity2D.h"


MunicionPistola::MunicionPistola(const vector3df & posicion, const vector3df & rotacion, const vector3df & escala, const int & identificacion, IMeshSceneNode * nodo, const int &tipoM, const int &balasDeLaCaja):
	Municion(posicion, rotacion, escala, identificacion, nodo, tipoM)
{
	municion = balasDeLaCaja;
}


MunicionPistola::~MunicionPistola()
{
}

int MunicionPistola::getMunicion()
{
	return municion;
}

void MunicionPistola::setFisica(b2World * world)
{
	entity = new Entity2D(world, pos, rot, scale, this, ID);
}
