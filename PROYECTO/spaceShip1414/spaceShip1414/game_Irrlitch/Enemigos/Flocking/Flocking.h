#pragma once

#include <Box2D\Box2D.h>
#include <iostream>
#include <vector>
#include <vector3d.h>


using namespace irr;
using namespace core;

class Entity2D;

class Flocking
{

private:

	bool lider;
	std::vector<Entity2D*> vecindario; //vector con las entities que hay en el flock
	float escala;
	float distanciaSeparacion;
	

public:
	Flocking(bool x);
	~Flocking();
	vector3df cohesion(Entity2D *entity); //1�
	vector3df alineacion(Entity2D *entity); //3�
	vector3df separacion(Entity2D *entity); //2�
	void colisionAvoidance(Entity2D * e);
	bool getLider();
	void setLider(bool x);
	void addEntity(Entity2D *e);
	void removeEntity(Entity2D *e);
	vector3df media(vector3df v, int cont);
	float distanciaAlCuadrado(vector3df u, vector3df v);

	void cambiarEstadoSequito(Entity2D * e, int estado);

};

