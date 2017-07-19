#pragma once
/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   Personaje.h
* Author: User
*
* Created on 16 de noviembre de 2016, 15:41
*/


#include <irrlicht.h>
#include <iostream>
#include <Box2D\Box2D.h>
#include <list>


#ifndef PERSONAJE_H
#define PERSONAJE_H

class Bala;
class Pistola;
class Fusil;
class Escopeta;
class Entity2D;
class Juego;
class Inventario;

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

class Personaje {
private:

	IMeshSceneNode *maya;
	IMeshSceneNode *shadow;
	float vel;
	vector3df pos;
	Entity2D *entity;
	vector3df angulo;
	int cargador; //cargador actual del arma en uso
	int municionTotal; //balas totales que tiene el jugador del arma actual
	f32 tiempoDisparo;
	bool disparo;
	bool teclaE;
	bool teclaQ;
	bool impulso = false;
	std::list<Bala*> listaBalas;
	int direccion;
	int armaActual;
	Pistola *pistola;
	Fusil *fusil;
	Escopeta *escopeta;
	float temporizador;
	float vida;
	float vidaMax;
	Juego *game;
	Inventario *inv;


	ITextSceneNode *GVida;
	ITextSceneNode *RVida;


public:
	Personaje(ISceneManager* smgr, IVideoDriver* driver, b2World *world, Juego *j);
	Personaje(const Personaje& orig);
	virtual ~Personaje();

	vector3df getPos();
	vector3df getRot();
	vector3df getAngulo();
	int getCargador();
	int getMunicionActual();
	float getVel();
	f32 getTiempoDisparo();
	bool getDisparo();
	int getDireccion();
	float getDamage();
	float getTiempoArma();
	int getArmaActual();
	bool getTeclaE();
	bool getTeclaQ();
	bool getImpulso();
	void setImpulso(bool x);
	void quitarVida(float damage);
	void curar(float recup);
	void usarBotiquin();
	float getVida();

	void pasarMensaje();

	void iniciarTiempoImpulso();

	void disminuirTem();

	float getTemporizador();
	Inventario* getInventario();
	

	void moverPersonaje(int modo, f32 dt);
	void setVelocidad();
	void rotar(vector3df raton);
	void setPos(vector3df pos);
	void recargar();
	void cogerMunicion(int municionCogida, int arma); 
	
	void setDisparo(bool x);
	void setTiempoDisparo(f32 t);
	void actualizarLista(f32 dt);
	void disparar(ISceneManager* smgr, IVideoDriver* driver, b2World *world, f32 dt, vector2df posRaton);
	void actualizarPosicion();
	void setArmaActual(int newArma);

	/*void subirNivelDamage();
	void subirCargador();
	void subirCapacidadDeMun();*/

	void setTeclaE(bool x);
	void setTeclaQ(bool x);
	bool getVivo();
	Entity2D* getEntity();
	void destroyBalas();
};


#endif /* PERSONAJE_H */
