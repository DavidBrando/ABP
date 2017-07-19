#include "Llave.h"
#include "../Fisicas/Entity2D.h"
#include "../Fisicas/Mundo.h"
#include "../graphicEngine/TGraphicEngine.h"

Llave::Llave(const glm::vec3 & posicion, const glm::vec3 & rotacion, const glm::vec3 & escala, const int & identificacion, std::string nombreHabitacion, TGraphicEngine *motor) :
	Objetos(posicion, rotacion, escala, identificacion, motor)
{
	nombre = nombreHabitacion;
	nodo = motor->addMalla("resourse/models/Objetos/key-1.obj");

	motor->escalar(nodo, esca.x, esca.y, esca.z);
	motor->trasladar(nodo, pos.x, pos.y, pos.z);
	motor->rotarYPR(nodo, rot.y, rot.x, rot.z);

}


Llave::~Llave()
{
}

void Llave::setFisica(Mundo * world)
{
	entity = new Entity2D(world->getWorldBox2D(), pos, esca, this, ID);

}

std::string Llave::getNombreHabitacion()
{
	return nombre;
}
