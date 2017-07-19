#pragma once

//#include <btBulletDynamicsCommon.h>
//#include <btBulletCollisionCommon.h>
#include <glm\vec3.hpp>

class Mundo3D;


class Entity3D
{
public:

	/*	Entity2D(b2World *world);// mundo para hacer raycasting
	Entity2D(b2World *world, glm::vec3  pos, glm::vec3 rot, void* dirPers); //personaje
	Entity2D(b2World* world, glm::vec3  pos, glm::vec3  rot, glm::vec3  escala, void* dirPared); //pared
	Entity2D(b2World* world, glm::vec3  pos, glm::vec3  rot, glm::vec3  escala, bool sensor, void* dirPuerta, int ident);// puerta
	Entity2D(b2World* world, glm::vec3  pos, glm::vec3  rot, bool vivo, void* dirBala, int tipo); //bala de jugador y enemigo; tipo == 0 player, tipo == 1 enemigo
	Entity2D(b2World *world, glm::vec3  pos, bool vivo, void* dirEnemigo, unsigned int raza); //enemigo con el int de distintas razas
	Entity2D(b2World* world, glm::vec3  pos, glm::vec3  rot, glm::vec3  escala, void* dirObjeto, int tipo); //objetos consumables con el int del tipo
	*/ 

	/*Entity3D(Mundo3D *mundo, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, void* dirPers);
	Entity3D(Mundo3D *mundo, void* dirPared, glm::vec3  pos, glm::vec3 rot, glm::vec3 escala);
	~Entity3D();


	void* getObjeto3D();
	btRigidBody* getCuerpo3D();
	int getIDEN();
	bool getLive();
	void setLive(bool x);*/

private:

	//Mundo3D *m;
	//void* dirObjeto3D;
	////btCollisionShape* body;
	//btRigidBody *rigidBody;
	//int iden;
	//bool live;
};

