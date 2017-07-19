#pragma once

#include <irrlicht.h>
#include <Box2D\Box2D.h>


using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Entity2D;
class Escenario;


class Terminal
{
public:
	Terminal(vector3df posicion, vector3df rotacion, vector3df escala, b2World *world, IMeshSceneNode* nodo, Escenario* esce);
	~Terminal();
	vector3df getPosicion();
	vector3df getRotacion();
	vector3df getEscala();
	bool getEstado();

	void cambiarEstado(bool x);
	void cambiarColor();


private:

	vector3df pos;
	vector3df rot;
	vector3df escal;
	Entity2D *entity;
	IMeshSceneNode* node;
	Escenario* escena;
	bool activado;

};

