#pragma once
/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   Juego.h
* Author: Hector
*
* Created on 19 de diciembre de 2016, 22:22
*/

#ifndef JUEGO_H
#define JUEGO_H

#include "EstadoGeneral.h"
#include <string>
#include <Box2D\Box2D.h>
#include <irrlicht.h>
#include <IrrlichtDevice.h>
#include <iostream>
#include <list>
#include "CAppReceiver.h"


class ManejadorEstadoGeneral;
class Enemigo;
class Personaje;
class Escenario;
class Camara;
class readJson;
class MiContactListener;
class MyContactFilter;
class Menu;

class Juego : public EstadoGeneral {
public:
	CAppReceiver teclado;
	IVideoDriver* driver;
	ISceneManager* smgr;
	IGUIEnvironment* guienv;
	b2Vec2 gravity;
	b2World *world;
	MiContactListener* contactListenerInstance;
	MyContactFilter* filtroContact;
	u32 then;
	Personaje *pers;
	Escenario *esce;
	Enemigo *ene;
	readJson *json;
	Camara *cam;
	int lastFPS;
	Menu *menuPausa;
	int estado;

	void loopJuego();

	Juego();
	Juego(std::string name);
	virtual ~Juego();
	void Dentro(void);
	void Fuera(void);
	bool OnEvent(const SEvent &event);
	void render(IrrlichtDevice* iDevice);
	void StarUP(IrrlichtDevice* iDevice);
	void update(int state);
	void mover(f32 dt);
	void recargar();
	void pausa(IrrlichtDevice* iDevice);
	void cambioarma();
	void raton(f32 dt);
	void accionesDeTeclado();
	void cambioEstado(std::string est);
	void destroyNew();
	bool para;


};

#endif /* JUEGO_H */

