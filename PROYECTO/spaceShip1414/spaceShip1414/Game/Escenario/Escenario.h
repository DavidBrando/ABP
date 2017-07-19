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
#include <list>
#include <vector>
#include <string>
#include "../graphicEngine\TGraphicEngine.h"
#include "../graphicEngine\entityTree\TTransform.h"
#include "../graphicEngine\entityTree\TCamara.h"
#include "../graphicEngine\entityTree\TNodo.h"
#include "../graphicEngine\entityTree\TMalla.h"
#include "../graphicEngine\entityTree\TLuz.h"

class Personaje;
class Juego;
class Puerta;
class Terminal;
class Objetos;
class Pared;
class Enemigo;
class Entity2D;
class Mundo;
class Waypoints;
class Camara;
class player;
class Luces;


class Escenario {


private:
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
		std::vector<Elemento> ObjetosEscena;
	}ElementoHijo;

	typedef struct
	{
		std::string nombre;
		TipoDatos position;
		TipoDatos rotation;
		TipoDatos escala;
		std::vector<ElementoHijo> ObjetosEscena;
	}ElementoPadre;

	std::vector<ElementoPadre> Padres;
	std::vector<ElementoHijo> Hijos;
	std::vector<Elemento> SubHijos;
	Mundo *mundo;
	std::vector<Enemigo*> enemigos;
	std::vector<Pared*> Listparedes;
	std::vector<Luces*> ListLuces;
	std::vector<Puerta*> puertas;
	std::vector<Camara*> listaDeCamaras;
	std::vector<Objetos*> objConsumables;
	std::vector<Waypoints*> waypoints;
	Luces *luzActual;
	int tam;
	Entity2D *entity;
	// Juego *jue;
	//Personaje *pers;
	TGraphicEngine * engine;
	Camara *c;
	player *jugador;

	

public:

	Escenario(TGraphicEngine * motorApp, Mundo* /*, b2World *world,  Juego* game*/);
	Escenario(const Escenario& orig);
	~Escenario();
	Camara* buscarCamara(int ID);
	void setPadres(std::string nombre, double t[], double r[], double s[], std::vector<Escenario::ElementoHijo> objetos);
	void setHijos(std::string nombre, double t[], double r[], double s[], std::vector<Escenario::Elemento> objetos);
	void setSubHijos(std::string nombre, double t[], double r[], double s[]);
	void muestraEstructura();
	void dibujarEscenario();
	void fabricaDeEnemigos();
	void destroyWaypoints();
	std::vector<Escenario::ElementoHijo> getHijos();
	std::vector<Escenario::Elemento> getSubHijos();
	void removeListHijos();
	void removeListSubHijos();
	void actualizarListaEnemigos(float dt);

	std::vector<Pared*> getParedes();
	int getTam();
	void cambiaEstado(std::string mensaje);
	void actualizarEstadoPersonaje();
	void actualizarEstadoPuerta();
	Camara * getCamara();
	void actualizarCamaras();
	void actualizarObjetosConsumables();
	void inicializarWaypoints();
	void eleminarEnemigos();
	void cambioDeLuces(int ID);
	player* getPersonaje();
	void destroyPared();
};

#endif /* ESCENARIO_H */

