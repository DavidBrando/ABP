#include "Terminal.h"
#include "../Fisicas/Entity2D.h"
#include "Escenario.h"

Terminal::Terminal(vector3df posicion, vector3df rotacion, vector3df escala, b2World * world, IMeshSceneNode* nodo, Escenario* esce)
{
	pos = posicion;
	rot = rotacion;
	escal = escala;
	node = nodo;
	activado = false;
	entity = new Entity2D(world, posicion, rotacion, escala, this, 5);
	escena = esce;
}

Terminal::~Terminal()
{
}

vector3df Terminal::getPosicion()
{
	return pos;
}

vector3df Terminal::getRotacion()
{
	return rot;
}

vector3df Terminal::getEscala()
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
	if(activado == true) {
		node->getMaterial(0).EmissiveColor.set(20, 20, 255, 80);
		escena->cambiaEstado("menu");
	}

	else{
		node->getMaterial(0).EmissiveColor.set(20, 255, 0, 80);
	}
}


