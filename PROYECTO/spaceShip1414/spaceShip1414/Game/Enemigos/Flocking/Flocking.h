#pragma once

#include <Box2D\Box2D.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>

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
	glm::vec3 cohesion(Entity2D *entity); //1º
	glm::vec3 alineacion(Entity2D *entity); //3º
	glm::vec3 separacion(Entity2D *entity); //2º
	void colisionAvoidance(Entity2D * e);
	bool getLider();
	void setLider(bool x);
	void addEntity(Entity2D *e);
	void removeEntity(Entity2D *e);
	glm::vec3 media(glm::vec3 v, int cont);
	float distanciaAlCuadrado(glm::vec3 u, glm::vec3 v);

	void cambiarEstadoSequito(Entity2D * e, int estado);

};

