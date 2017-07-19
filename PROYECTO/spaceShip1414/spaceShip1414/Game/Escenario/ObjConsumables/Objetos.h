#pragma once

#include <iostream>
#include <Box2D\Box2D.h>
#include <glm\vec3.hpp>

class Entity2D;
class Mundo;
class TTransform;
class TGraphicEngine;
class TNodo;
class Mundo;

class Objetos
{
public:
	Objetos(const glm::vec3 &posicion, const glm::vec3 &rotacion, const glm::vec3 &escala, const int &identificacion, TGraphicEngine *motor);
	~Objetos();
	void destroyEntidades();
	glm::vec3 getPos();
	glm::vec3 getRot();
	glm::vec3 getEscala();
	int getID();
	virtual void setFisica(Mundo *world);

	bool getVivo();

	void rotation(TGraphicEngine *, float, float, float, float);
	void rotationYPR(TGraphicEngine *, float, float, float);
	void scale(TGraphicEngine *, float, float, float);
	void translation(TGraphicEngine *, float, float, float);
	TNodo * getNodo();

protected:

	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 esca;
	Entity2D *entity;
	int ID;
	TNodo *nodo;
	TGraphicEngine * engine;
	float yaw;
	float pitch;
	//IMeshSceneNode *maya;
};

