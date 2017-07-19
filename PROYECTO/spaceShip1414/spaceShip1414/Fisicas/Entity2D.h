#pragma once
/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   Entity2D.h
* Author: User
*
* Created on 9 de diciembre de 2016, 15:52
*/

#ifndef ENTITY2D_H
#define ENTITY2D_H
#include <Box2D\Box2D.h>
#include <glm\vec3.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\string_cast.hpp>
#include <glm\gtx\euler_angles.hpp>


class RayCastCallback;

class Entity2D {
public:
	glm::vec4 multiplicarVector(const glm::mat4 & m, float x, float y, float z);
	Entity2D(b2World *world);
	Entity2D(b2World *world, glm::vec3  pos, glm::vec3 rot, void* dirPers);
	Entity2D(b2World* world, glm::vec3  pos, glm::vec3  rot, glm::vec3  escala, void* dirPared);
	Entity2D(b2World* world, glm::vec3  pos, glm::vec3  rot, glm::vec3  escala, bool sensor, void* dirPuerta, int ident);
	Entity2D(b2World* world, glm::vec3  pos, glm::vec3  rot, bool vivo, void* dirBala, int tipo);
	Entity2D(b2World *world, glm::vec3  pos, bool vivo, void* dirEnemigo, unsigned int raza);
	Entity2D(b2World* world, glm::vec3  pos, glm::vec3  escala, void* dirObjeto, int tipo);
	Entity2D(b2World *world, glm::vec3 pos, glm::vec3 rot, glm::vec3 escala, void* dirCamara, bool sensor);

	Entity2D(const Entity2D& orig);
	virtual ~Entity2D();
	float rayCast(b2Vec2 inicio, b2Vec2 fin);
	b2Body* getCuerpo2D();
	void getRotarDireccion();
	float rayCasting(b2Vec2 inicio, b2Vec2 fin);
	void llamarCallBack(RayCastCallback* callback, b2Vec2 inicio, b2Vec2 fin);
	int getIDEN();
	int getIDENSH();
	bool getLive();
	void setLive(bool x);

	void* getObjeto3D();
	void mostrarPos2D();
	void destruirFixture();
	void crearFixture();
	b2Body* getSombraP2D();
	b2Body* getSombraE2D();
	b2Body* getPuertaBody();
	int getId();

	glm::vec3  getNormal();
	glm::vec3  getPuntoDeChoque();
	glm::vec3 getEscalaFixture();

private:


	b2Body *body;
	b2BodyDef bodyDef;
	b2PolygonShape bodyShape;
	b2CircleShape bodyCircle;
	b2MassData md;
	b2Filter filtro;
	b2Body *sombraP;
	b2Body *sombraE;
	b2Body *puertaBody;
	b2BodyDef sombraDef;
	b2PolygonShape sombraShape;

	/*IMeshSceneNode* fisica;
	IMeshSceneNode* fisica2;
	IMeshSceneNode* direccion;*/

	int iden;
	int idenSh = -1;
	int id;
	bool live;
	void* objeto3D;
	b2Vec2 normal;
	b2Vec2 puntoDeChoque;
	glm::vec3 escalaFixture;

};

#endif /* ENTITY2D_H */

