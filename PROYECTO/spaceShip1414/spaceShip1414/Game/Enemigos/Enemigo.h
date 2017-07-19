#pragma once
/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   Enemigo.h
* Author: Iván
*
* Created on 29 de noviembre de 2016, 17:52
*/


#include <iostream>

#include <Box2D\Box2D.h>
#include <list>
#include <vector>
#include <glm\glm.hpp>

#ifndef ENEMIGO_H
#define ENEMIGO_H

class Nodo;
class AStar;
class Waypoints;
class Entity2D;
class Bala;
class LogicaDifusa;
class Flocking;
class TTransform;
class TGraphicEngine;
class TNodo;
class Mundo;

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 180 / 3.14f 

#define CRIA 10
#define BERSERKER 11
#define SOLDADO 12
#define JEFE 13

#define BUSCARPUNTO 0
#define PATRULLAR 1
#define ALERTA 2
#define ATACAR 3
#define ROTACION 4
#define DESCANSAR 5
#define ESCAPAR 6
#define CUERPOACUERPO 7
#define FLOCKING 8

#define MULTIVEL 50
#define PROPCURVA 35
//el enemigo deberia tener un estado que sea
//siguiendo al lider o algo para aplicar el flocking
// a menos velocidad mas propcurva y a mas vel, menos propcurva


#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif



typedef struct
{
	glm::vec3 linear;
	float angular;
} Steering;

typedef struct
{
	glm::vec3 posicion;
	float orientacion;
	glm::vec3 velocidad;
	float rotacion;

	void update(Steering st, float dt)
	{
		posicion += velocidad*dt;
		orientacion += rotacion*dt;
		//posicion.y = -5.0;
		st.linear.y = 0;
		velocidad += st.linear*dt;
		rotacion += st.angular*dt;
		//std::cout << "CACA: " << velocidad.length() << std::endl;
		if (glm::length(velocidad) > 5.0f)
		{
			velocidad = glm::normalize(velocidad);
			velocidad *= MULTIVEL;
		}

		//std::cout <<"copon: "<< posicion.X << " " << posicion.Z << std::endl;


	}

} Kinematic;

class Enemigo {

public:
	//Enemigo(ISceneManager* smgr, IVideoDriver* driver, b2World *world, glm::vec3 posicion, Waypoints* puntos);
	Enemigo(TGraphicEngine*, Mundo*, glm::vec3 posicion, Waypoints *puntos);
	// Enemigo(const Enemigo& orig);
	virtual ~Enemigo();

	virtual void Update(float dt);
	void Mover();
	void setVelocidad();
	virtual void Patrullar();
	virtual void Atacar(float dt);
	virtual void BuscarWaypoint();
	virtual void CQC() = 0;
	void setPos(glm::vec3 pos);
	bool estaVivo();
	glm::vec3 getPos();
	glm::vec3 getRot();
	glm::vec3 getScale();
	glm::vec3 getVectorVel();
	float getVel();
	virtual void quitarVida(float damage) = 0;
	virtual void recuperarResistencia() = 0;

	float getVida();
	Entity2D*  getEntity();
	float getDamageChoque();
	void setEstado(int num);
	int getEstado();

	void setDisparo(bool x);
	void aumentarTiempoDisparo(float t);
	void resetTiempoDisparo();
	void setTime(float t);
	float getTiempoDisparo();
	bool getDisparado();
	void disparar(float dt);
	void actualizarLista();
	void setPosJugador(float x, float y);
	Nodo* getNodoInicio();
	Nodo* getNodoFin();
	void setPesoMaximoLogicaDifusa(float x);
	void iniLogicaDifusa();

	Kinematic seek(const glm::vec3 target);

	Kinematic arrive(const glm::vec3 target);

	void align(const glm::vec3 target);

	void collisionAvoidance(glm::vec3 vecU);

	void obstacleAvoidance();


	bool getVista();
	void setVista(bool x);
	bool getEsquivarPared();
	void setEsquivarPared(bool x);
	bool getVision();
	void setVision(bool x);
	bool getLider();

	void setGrupoFlocking(Entity2D * e);

	void deleteEntity(Entity2D * e);


	//metodos del motor

	float getYaw();
	float getPitch();
	void rotation(TGraphicEngine *, float, float, float, float);
	void rotationYPR(TGraphicEngine *, float, float, float);
	void scale(TGraphicEngine *, float, float, float);
	void translation(TGraphicEngine *, float, float, float);
	void setYaw(float);
	void setPitch(float);
	TNodo * getNodo();



protected:
	


	float vel;
	glm::vec3 vecVel;
	glm::vec3 pos, rot, vectorUnitario;
	Entity2D *entity;
	int estadoActual;
	float vida;
	int raza;

	b2World* mundo;
	float blindaje;
	Waypoints *waypoints;
	LogicaDifusa *logica;
	Flocking *floc;

	AStar *path;
	Nodo *puntoIni, *puntoFin, *nodoAnterior;
	int dir, posNodo;
	float damageChoque;
	float moral;
	float resistencia;
	bool vista; //usado para esquivar enemigos
	bool esquivarPared;
	bool vision; //cambiarlo por un raycasting que te diga si choca contra algo o no
	//hay que crear booleanos para ver si tiene que esquivar un muro, enemigo o si puede verte
	Kinematic st;
	Steering sto;

	std::list<Bala*> listaBalas;
	std::vector<Nodo*> recorrido; //maximo 4 nodos
	bool disparado;
	float tiempoDisparo;
	glm::vec2 posJugador;
	float damageBala;
	float time;

	//variables motor
	TNodo *nodo;
	TGraphicEngine * engine;
	float yaw;
	float pitch;
};

#endif /* ENEMIGO_H */

