

#include "MunicionPistola.h"
#include "../Fisicas/Entity2D.h"
#include "../Fisicas/Mundo.h"
#include "../graphicEngine/TGraphicEngine.h"


MunicionPistola::MunicionPistola(const glm::vec3 & posicion, const glm::vec3 & rotacion, const glm::vec3 & escala, const int & identificacion, const int &tipoM, const int &balasDeLaCaja, TGraphicEngine *motor):
	Municion(posicion, rotacion, escala, identificacion, tipoM, motor)
{
	municion = balasDeLaCaja;
	nodo = motor->addMalla("resourse/models/Objetos/municion.obj");

	motor->escalar(nodo, esca.x, esca.y, esca.z);
	motor->trasladar(nodo, pos.x, pos.y, pos.z);
	motor->rotarYPR(nodo, rot.y, rot.x, rot.z);

}


MunicionPistola::~MunicionPistola()
{
}

int MunicionPistola::getMunicion()
{
	return municion;
}

void MunicionPistola::setFisica(Mundo * world)
{
	entity = new Entity2D(world->getWorldBox2D(), pos, esca, this, ID);
}
