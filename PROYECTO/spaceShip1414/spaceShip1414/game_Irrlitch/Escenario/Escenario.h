#pragma once
/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   Escenario.h
* Author: Hector
*
* Created on 17 de noviembre de 2016, 20:08
*/



#ifndef ESCENARIO_H
#define ESCENARIO_H

#include <iostream>
#include <irrlicht.h>
#include <Box2D\Box2D.h>
#include <list>
#include <vector>
#include <string>


class Personaje;
class Juego;
class Puerta;
class Terminal;
class Objetos;
class Pared;
class Enemigo;
class Entity2D;
class Waypoints;

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


class Escenario {


private:
	ISceneManager* SM;
	IVideoDriver* VD;
	//vector con cada elemento que se cree (puertas, objetos, paredes, etc...)
	typedef struct
	{
		double x, y, z;
	} TipoDatos;

	typedef struct
	{
		std::string nombre;
		TipoDatos position;
		TipoDatos rotation;
		TipoDatos escala;
	} Elemento;


	typedef struct
	{
		std::string nombre;
		TipoDatos position;
		TipoDatos rotation;
		TipoDatos escala;
		std::list<Elemento> ObjetosEscena;
	}ElementoHijo;

	typedef struct
	{
		std::string nombre;
		TipoDatos position;
		TipoDatos rotation;
		TipoDatos escala;
		std::list<ElementoHijo> ObjetosEscena;
	}ElementoPadre;

	std::list<ElementoPadre> Padres;
	std::list<ElementoHijo> Hijos;
	std::list<Elemento> SubHijos;
	b2World *mundo;
	std::list<Enemigo*> enemigos;
	std::list<Pared*> paredes;
	std::list<Puerta*> puertas;
	std::list<Objetos*> objConsumables;
	std::vector<Waypoints*> waypoints;
	int tam;
	Entity2D *entity;
	 Juego *jue;
	Personaje *pers;

public:
	Escenario(ISceneManager* smgr, IVideoDriver* driver, b2World *world,  Juego* game);
	Escenario(const Escenario& orig);
	virtual ~Escenario();

	void setPadres(std::string nombre, double t[], double r[], double s[], std::list<Escenario::ElementoHijo> objetos);
	void setHijos(std::string nombre, double t[], double r[], double s[], std::list<Escenario::Elemento> objetos);
	void setSubHijos(std::string nombre, double t[], double r[], double s[]);
	void muestraEstructura();
	void dibujarEscenario();
	void fabricaDeEnemigos();
	void destroyWaypoints();
	std::list<Escenario::ElementoHijo> getHijos();
	std::list<Escenario::Elemento> getSubHijos();
	void removeListHijos();
	void removeListSubHijos();
	void actualizarListaEnemigos(f32 dt);

	std::list<Pared*> getParedes();
	int getTam();
	void cambiaEstado(std::string mensaje);
	void actualizarEstadoPersonaje();
	void actualizarEstadoPuerta();
	void actualizarObjetosConsumables();
	void inicializarWaypoints();
	void eleminarEnemigos();
	Personaje* getPersonaje();
	void destroyPared();
};

#endif /* ESCENARIO_H */

