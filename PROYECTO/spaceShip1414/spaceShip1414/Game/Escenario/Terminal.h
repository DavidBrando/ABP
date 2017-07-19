#pragma once

#include <glm\vec3.hpp>

class Mundo;
class Entity2D;
class Escenario;


class Terminal
{
public:
	Terminal(glm::vec3 posicion, glm::vec3 rotacion, glm::vec3 escala, Mundo *world, Escenario* esce);
	~Terminal();
	glm::vec3 getPosicion();
	glm::vec3 getRotacion();
	glm::vec3 getEscala();
	bool getEstado();

	void cambiarEstado(bool x);
	void cambiarColor();


private:

	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 escal;
	Entity2D *entity;

	Escenario* escena;
	bool activado;

};

