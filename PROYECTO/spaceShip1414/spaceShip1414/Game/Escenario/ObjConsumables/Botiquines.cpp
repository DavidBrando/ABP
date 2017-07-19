

#include "Botiquines.h"
#include "../Fisicas/Entity2D.h"
#include "../Fisicas/Mundo.h"
#include "../graphicEngine/TGraphicEngine.h"

Botiquines::Botiquines(const glm::vec3 & posicion, const glm::vec3 & rotacion, const glm::vec3 & escala, const int & identificacion, TGraphicEngine *motor) :
	Objetos(posicion, rotacion, escala, identificacion, motor)
{
	vida = 50.0f;

	nodo = motor->addMalla("resourse/models/Objetos/botiquin.obj");

	motor->escalar(nodo, esca.x, esca.y, esca.z);
	motor->trasladar(nodo, pos.x, pos.y, pos.z);
	motor->rotarYPR(nodo, rot.y, rot.x, rot.z);


}

Botiquines::~Botiquines()
{
}

float Botiquines::getVida()
{
	return vida;
}

void Botiquines::setFisica(Mundo * world)
{

	entity = new Entity2D(world->getWorldBox2D(), pos, esca, this, ID);

}
