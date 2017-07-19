#include "Terminal.h"
#include "../Fisicas/Entity2D.h"
#include "Escenario.h"
#include "../Fisicas/Mundo.h"

Terminal::Terminal(glm::vec3 posicion, glm::vec3 rotacion, glm::vec3 escala, Mundo * world,  Escenario* esce)
{
	pos = posicion;
	rot = rotacion;
	escal = escala;

	activado = false;
	entity = new Entity2D(world->getWorldBox2D(), posicion, rotacion, escala, this, 5);
	escena = esce;
}

Terminal::~Terminal()
{
}

glm::vec3 Terminal::getPosicion()
{
	return pos;
}

glm::vec3 Terminal::getRotacion()
{
	return rot;
}

glm::vec3 Terminal::getEscala()
{
	return escal;
}

bool Terminal::getEstado()
{
	return activado;
}

void Terminal::cambiarEstado(bool x)
{
	activado = x;
}

void Terminal::cambiarColor()
{
	//if(activado == true) {
	//	node->getMaterial(0).EmissiveColor.set(20, 20, 255, 80);
	//	escena->cambiaEstado("menu");
	//}

	//else{
	//	node->getMaterial(0).EmissiveColor.set(20, 255, 0, 80);
	//}
}


