

#include "Botiquines.h"
#include "../../Fisicas/Entity2D.h"


Botiquines::Botiquines(const vector3df & posicion, const vector3df & rotacion, const vector3df & escala, const int & identificacion, IMeshSceneNode * nodo) :
	Objetos(posicion, rotacion, escala, identificacion, nodo)
{
	vida = 50.0f;
}

Botiquines::~Botiquines()
{
}

float Botiquines::getVida()
{
	return vida;
}

void Botiquines::setFisica(b2World * world)
{
	entity = new Entity2D(world, pos, rot, scale, this, ID);

}
