/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   Escenario.cpp
* Author: Hector
*
* Created on 17 de noviembre de 2016, 20:08
*/

#include <stdlib.h>
#include <time.h>
#include "Escenario.h"
#include "Pared.h"
#include "Puerta.h"
#include "readJson.h"
#include "Terminal.h"
#include "../Juego.h"
#include "../Jugador/Personaje.h"
#include "../Enemigos/CriaAlien.h"
#include "../Enemigos/Waypoints.h"
#include "../Enemigos/AlienBerserker.h"
#include "../Enemigos/Enemigo.h"
#include "Pared.h"
#include "ObjConsumables\Objetos.h"
#include "ObjConsumables\Botiquines.h"
#include "ObjConsumables\Llave.h"
#include "ObjConsumables\TiposDeMunicion\MunicionEscopeta.h"
#include "ObjConsumables\TiposDeMunicion\MunicionPistola.h"
#include "ObjConsumables\TiposDeMunicion\MunicionSubfusil.h"
#include "../Fisicas/Entity2D.h"


Escenario::Escenario(ISceneManager* smgr, IVideoDriver* driver, b2World *world, Juego* game) {

	SM = smgr;
	VD = driver;
	mundo = world;
	srand(time(NULL));
	entity = new Entity2D(world);
	jue = game;
	pers = new Personaje(smgr, driver, world, game);
}

Escenario::Escenario(const Escenario& orig) {
}

Escenario::~Escenario() {
	delete(entity);
}

void Escenario::setPadres(std::string nombre, double t[], double r[], double s[], std::list<Escenario::ElementoHijo> objetos) {
	ElementoPadre p;
	p.nombre = nombre;
	p.position.x = t[0];
	p.position.y = t[1];
	p.position.z = t[2];
	p.rotation.x = r[0];
	p.rotation.y = r[1];
	p.rotation.z = r[2];
	p.escala.x = s[0];
	p.escala.y = s[1];
	p.escala.z = s[2];
	p.ObjetosEscena = objetos;
	Padres.push_back(p);

}

void Escenario::setHijos(std::string nombre, double t[], double r[], double s[], std::list<Escenario::Elemento> objetos) {
	ElementoHijo p;
	p.nombre = nombre;
	p.position.x = t[0];
	p.position.y = t[1];
	p.position.z = t[2];
	p.rotation.x = r[0];
	p.rotation.y = r[1];
	p.rotation.z = r[2];
	p.escala.x = s[0];
	p.escala.y = s[1];
	p.escala.z = s[2];
	p.ObjetosEscena = objetos;
	Hijos.push_back(p);
}

void Escenario::setSubHijos(std::string nombre, double t[], double r[], double s[]) {
	Elemento p;
	p.nombre = nombre;
	p.position.x = t[0];
	p.position.y = t[1];
	p.position.z = t[2];
	p.rotation.x = r[0];
	p.rotation.y = r[1];
	p.rotation.z = r[2];
	p.escala.x = s[0];
	p.escala.y = s[1];
	p.escala.z = s[2];

	SubHijos.push_back(p);
}

std::list<Escenario::ElementoHijo> Escenario::getHijos() {
	return Hijos;
}

std::list<Escenario::Elemento> Escenario::getSubHijos() {
	return SubHijos;
}

std::list<Pared*> Escenario::getParedes() {

	return paredes;
}

int Escenario::getTam() {
	return tam;
}

void Escenario::muestraEstructura() {
	cout << "/////////////////////////////////////////////////////" << endl;
	for (std::list<ElementoPadre>::iterator I = Padres.begin(); I != Padres.end(); I++) {
		std::cout << "Padre: " << (*I).nombre << std::endl;
		std::cout << "  Posicion: x=" << (*I).position.x << " y= " << (*I).position.y << " z= " << (*I).position.z << std::endl;
		std::cout << "  Rotacion: x=" << (*I).rotation.x << " y= " << (*I).rotation.y << " z= " << (*I).rotation.z << std::endl;
		std::cout << "  Escala: x=" << (*I).escala.x << " y= " << (*I).escala.y << " z= " << (*I).escala.z << std::endl;

		for (std::list<ElementoHijo>::iterator M = (*I).ObjetosEscena.begin(); M != (*I).ObjetosEscena.end(); M++) {
			cout << "..............................................." << endl;
			std::cout << "      Hijo: " << (*M).nombre << std::endl;
			std::cout << "          Posicion: x=" << (*M).position.x << " y= " << (*M).position.y << " z= " << (*M).position.z << std::endl;
			std::cout << "          Rotacion: x=" << (*M).rotation.x << " y= " << (*M).rotation.y << " z= " << (*M).rotation.z << std::endl;
			std::cout << "          Escala: x=" << (*M).escala.x << " y= " << (*M).escala.y << " z= " << (*M).escala.z << std::endl;
			for (std::list<Elemento>::iterator N = (*M).ObjetosEscena.begin(); N != (*M).ObjetosEscena.end(); N++) {
				cout << "*****************************************************" << endl;
				std::cout << "      SubHijo: " << (*N).nombre << std::endl;
				std::cout << "          Posicion: x=" << (*N).position.x << " y= " << (*N).position.y << " z= " << (*N).position.z << std::endl;
				std::cout << "          Rotacion: x=" << (*N).rotation.x << " y= " << (*N).rotation.y << " z= " << (*N).rotation.z << std::endl;
				std::cout << "          Escala: x=" << (*N).escala.x << " y= " << (*N).escala.y << " z= " << (*N).escala.z << std::endl;

				cout << "******************************************************" << endl;
			}
			cout << "..............................................." << endl;
		}

	}

	cout << "/////////////////////////////////////////////////////" << endl;
}

void Escenario::removeListHijos() {
	Hijos.clear();
}

void Escenario::removeListSubHijos() {
	SubHijos.clear();
}

void Escenario::dibujarEscenario() {
	int num = 0;
	tam = 0;

	//Waypoints *puntos = new Waypoints();

	Waypoints *zona1 = new Waypoints();
	Waypoints *zona2 = new Waypoints();
	Waypoints *zona3 = new Waypoints();
	Waypoints *zona4 = new Waypoints();


	for (std::list<ElementoPadre>::iterator I = Padres.begin(); I != Padres.end(); I++) {

		if ((*I).nombre == "HANGAR") {

			for (std::list<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {
				if ((*T).nombre == "Puerta") {

					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {
						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 20 + num * 5, 5 * num + 60, 50 - num);

						if((*N).nombre == "Puerta-CERRADA") {

							objeto->getMaterial(0).EmissiveColor.set(0, 255, 0, 0);

							Puerta *door = new Puerta(num, vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
								vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
								vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z),
								objeto, (*I).nombre);

							door->setFisica(mundo, SM, num);
							puertas.push_back(door);
							num++;

						}

						else {

							Puerta *door = new Puerta(num, vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
								vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
								vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z),
								objeto, "ABIERTA");

							door->setFisica(mundo, SM, num);
							puertas.push_back(door);
							num++;
						}

					}

				}


				if ((*T).nombre == "Ventanas") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(20, 103, 103, 103);
						Pared *wall = new Pared(vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));

						wall->setFisica(mundo);
						paredes.push_back(wall);
					}
				}



				if ((*T).nombre == "Paredes") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(20, 0, 0, 0);
						Pared *wall = new Pared(vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));

						wall->setFisica(mundo);
						paredes.push_back(wall);
					}
				}

				if ((*T).nombre == "Suelo") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 255, 255, 255);

					}
				}
			}
		}

		if ((*I).nombre == "SALA_ESPERA") {

			for (std::list<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {
				if ((*T).nombre == "Puerta") {

					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {
						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 20 + num * 5, 5 * num + 60, 50 - num);

						Puerta *door = new Puerta(num, vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z),
							objeto, "ABIERTA");

						door->setFisica(mundo, SM, num);
						puertas.push_back(door);
						num++;
					}

				}


				if ((*T).nombre == "Paredes") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(20, 123, 124, 50);
						Pared *wall = new Pared(vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));

						wall->setFisica(mundo);
						paredes.push_back(wall);
					}
				}

				if ((*T).nombre == "Suelo") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 23, 79, 74);

					}
				}
			}
		}

		if ((*I).nombre == "SALA_GENERADOR") {

			for (std::list<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {
				if ((*T).nombre == "Puerta") {

					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {
						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 20 + num * 5, 5 * num + 60, 50 - num);


						if ((*N).nombre == "Puerta-CERRADA") {
							objeto->getMaterial(0).EmissiveColor.set(0, 255, 0, 0);

							Puerta *door = new Puerta(num, vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
								vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
								vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z),
								objeto, (*I).nombre);

							door->setFisica(mundo, SM, num);
							puertas.push_back(door);
							num++;

						}

						else {

							Puerta *door = new Puerta(num, vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
								vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
								vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z),
								objeto, "ABIERTA");

							door->setFisica(mundo, SM, num);
							puertas.push_back(door);
							num++;
						}

					}

				}


				if ((*T).nombre == "Paredes") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(20, 176, 120, 0);
						Pared *wall = new Pared(vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));

						wall->setFisica(mundo);
						paredes.push_back(wall);
					}
				}

				if ((*T).nombre == "Suelo") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 4, 17, 38);

					}
				}
			}
		}

		if ((*I).nombre == "HALL") {

			for (std::list<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {
				if ((*T).nombre == "Puerta") {

					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {
						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 20 + num * 5, 5 * num + 60, 50 - num);

						if ((*N).nombre == "Puerta-CERRADA") {
							objeto->getMaterial(0).EmissiveColor.set(0, 255, 0, 0);

							Puerta *door = new Puerta(num, vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
								vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
								vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z),
								objeto, (*I).nombre);

							door->setFisica(mundo, SM, num);
							puertas.push_back(door);
							num++;

						}

						else {

							Puerta *door = new Puerta(num, vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
								vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
								vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z),
								objeto, "ABIERTA");

							door->setFisica(mundo, SM, num);
							puertas.push_back(door);
							num++;
						}

					}

				}


				if ((*T).nombre == "Paredes") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(20, 38, 18, 0);
						Pared *wall = new Pared(vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));

						wall->setFisica(mundo);
						paredes.push_back(wall);
					}
				}

				if ((*T).nombre == "Suelo") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 98, 46, 113);

					}
				}
			}
		}

		if ((*I).nombre == "SALA_MANTENIMIENTO") {

			for (std::list<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {
				if ((*T).nombre == "Puerta") {

					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {
						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 20 + num * 5, 5 * num + 60, 50 - num);


						Puerta *door = new Puerta(num, vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z),
							objeto, "ABIERTA");

						door->setFisica(mundo, SM, num);
						puertas.push_back(door);
						num++;
					}

				}


				if ((*T).nombre == "Paredes") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(20, 58, 64, 23);
						Pared *wall = new Pared(vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));

						wall->setFisica(mundo);
						paredes.push_back(wall);
					}
				}

				if ((*T).nombre == "Suelo") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 77, 35, 35);

					}
				}
			}
		}

		if ((*I).nombre == "CANTINA") {

			for (std::list<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {
				if ((*T).nombre == "Puerta") {

					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {
						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 20 + num * 5, 5 * num + 60, 50 - num);


						Puerta *door = new Puerta(num, vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z),
							objeto, "ABIERTA");

						door->setFisica(mundo, SM, num);
						puertas.push_back(door);
						num++;
					}

				}


				if ((*T).nombre == "Paredes") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(20, 3, 32, 13);
						Pared *wall = new Pared(vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));

						wall->setFisica(mundo);
						paredes.push_back(wall);
					}
				}

				if ((*T).nombre == "Suelo") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 255, 164, 0);

					}
				}
			}
		}

		if ((*I).nombre == "COMISARIA") {

			for (std::list<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {
				if ((*T).nombre == "Puerta") {

					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {
						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 20 + num * 5, 5 * num + 60, 50 - num);

						Puerta *door = new Puerta(num, vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z),
							objeto, "ABIERTA");

						door->setFisica(mundo, SM, num);
						puertas.push_back(door);
						num++;
					}

				}


				if ((*T).nombre == "Paredes") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(20, 117, 50, 234);
						Pared *wall = new Pared(vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));

						wall->setFisica(mundo);
						paredes.push_back(wall);
					}
				}

				if ((*T).nombre == "Suelo") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 0, 0, 0);

					}
				}
			}
		}

		if ((*I).nombre == "VESTUARIO") {

			for (std::list<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {
				if ((*T).nombre == "Puerta") {

					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {
						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 20 + num * 5, 5 * num + 60, 50 - num);

						if ((*N).nombre == "Puerta-CERRADA") {
							objeto->getMaterial(0).EmissiveColor.set(0, 255, 0, 0);

							Puerta *door = new Puerta(num, vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
								vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
								vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z),
								objeto, "Comisaria");

							door->setFisica(mundo, SM, num);
							puertas.push_back(door);
							num++;

						}

						else {

							Puerta *door = new Puerta(num, vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
								vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
								vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z),
								objeto, "ABIERTA");

							door->setFisica(mundo, SM, num);
							puertas.push_back(door);
							num++;
						}

					}

				}


				if ((*T).nombre == "Paredes") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(20, 20, 72, 109);
						Pared *wall = new Pared(vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));

						wall->setFisica(mundo);
						paredes.push_back(wall);
					}
				}

				if ((*T).nombre == "Suelo") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 77, 118, 31);

					}
				}
			}
		}

		if ((*I).nombre == "CELDA") {

			for (std::list<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {
				if ((*T).nombre == "Puerta") {

					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {
						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 20 + num * 5, 5 * num + 60, 50 - num);

						Puerta *door = new Puerta(num, vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z),
							objeto, "ABIERTA");

						door->setFisica(mundo, SM, num);
						puertas.push_back(door);
						num++;
					}

				}


				if ((*T).nombre == "Paredes") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(20, 0, 0, 0);
						Pared *wall = new Pared(vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));

						wall->setFisica(mundo);
						paredes.push_back(wall);
					}
				}

				if ((*T).nombre == "Suelo") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 49, 0, 0);

					}
				}
			}
		}

		if ((*I).nombre == "ARSENAL") {

			for (std::list<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {
				if ((*T).nombre == "Puerta") {

					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {
						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 20 + num * 5, 5 * num + 60, 50 - num);

						Puerta *door = new Puerta(num, vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z),
							objeto, "ABIERTA");

						door->setFisica(mundo, SM, num);
						puertas.push_back(door);
						num++;
					}

				}


				if ((*T).nombre == "Paredes") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(20, 255, 0, 0);
						Pared *wall = new Pared(vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));

						wall->setFisica(mundo);
						paredes.push_back(wall);
					}
				}

				if ((*T).nombre == "Suelo") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 10, 4, 84);

					}
				}
			}
		}

		if ((*I).nombre == "PASILLO_1") {

			for (std::list<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {
				if ((*T).nombre == "Puerta") {

					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {
						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 20 + num * 5, 5 * num + 60, 50 - num);

						Puerta *door = new Puerta(num, vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z),
							objeto, "ABIERTA");

						door->setFisica(mundo, SM, num);
						puertas.push_back(door);
						num++;
					}

				}


				if ((*T).nombre == "Paredes") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(20, 19, 19, 19);
						Pared *wall = new Pared(vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));

						wall->setFisica(mundo);
						paredes.push_back(wall);
					}
				}

				if ((*T).nombre == "Suelo") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 96, 110, 174);

					}
				}
			}
		}

		if ((*I).nombre == "PASILLO_2") {

			for (std::list<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {
				if ((*T).nombre == "Puerta") {

					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {
						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 20 + num * 5, 5 * num + 60, 50 - num);

						Puerta *door = new Puerta(num, vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z),
							objeto, "ABIERTA");

						door->setFisica(mundo, SM, num);
						puertas.push_back(door);
						num++;
					}

				}


				if ((*T).nombre == "Paredes") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(20, 19, 19, 19);
						Pared *wall = new Pared(vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));

						wall->setFisica(mundo);
						paredes.push_back(wall);
					}
				}

				if ((*T).nombre == "Suelo") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 96, 110, 174);

					}
				}
			}
		}

		if ((*I).nombre == "PASILLO_3") {

			for (std::list<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {
				if ((*T).nombre == "Puerta") {

					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {
						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 20 + num * 5, 5 * num + 60, 50 - num);

						if ((*N).nombre == "Puerta-CERRADA") {
							objeto->getMaterial(0).EmissiveColor.set(0, 255, 0, 0);

							Puerta *door = new Puerta(num, vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
								vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
								vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z),
								objeto, "Almacen_3");

							door->setFisica(mundo, SM, num);
							puertas.push_back(door);
							num++;

						}

						else {

							Puerta *door = new Puerta(num, vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
								vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
								vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z),
								objeto, "ABIERTA");

							door->setFisica(mundo, SM, num);
							puertas.push_back(door);
							num++;
						}

					}

				}


				if ((*T).nombre == "Paredes") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(20, 19, 19, 19);
						Pared *wall = new Pared(vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));

						wall->setFisica(mundo);
						paredes.push_back(wall);
					}
				}

				if ((*T).nombre == "Suelo") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 96, 110, 174);

					}
				}
			}
		}

		if ((*I).nombre == "PASILLO_4") {

			for (std::list<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {
				if ((*T).nombre == "Puerta") {

					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {
						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 20 + num * 5, 5 * num + 60, 50 - num);


						Puerta *door = new Puerta(num, vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z),
							objeto, "ABIERTA");

						door->setFisica(mundo, SM, num);
						puertas.push_back(door);
						num++;
					}

				}


				if ((*T).nombre == "Paredes") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(20, 19, 19, 19);
						Pared *wall = new Pared(vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));

						wall->setFisica(mundo);
						paredes.push_back(wall);
					}
				}

				if ((*T).nombre == "Suelo") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 96, 110, 174);

					}
				}
			}
		}

		if ((*I).nombre == "PASILLO_5") {

			for (std::list<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {
				if ((*T).nombre == "Puerta") {

					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {
						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 20 + num * 5, 5 * num + 60, 50 - num);


						if ((*N).nombre == "Puerta-CERRADA") {
							objeto->getMaterial(0).EmissiveColor.set(0, 255, 0, 0);

							Puerta *door = new Puerta(num, vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
								vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
								vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z),
								objeto, "Comisaria");

							door->setFisica(mundo, SM, num);
							puertas.push_back(door);
							num++;

						}

						else {

							Puerta *door = new Puerta(num, vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
								vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
								vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z),
								objeto, "ABIERTA");

							door->setFisica(mundo, SM, num);
							puertas.push_back(door);
							num++;
						}

					}

				}


				if ((*T).nombre == "Paredes") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(20, 19, 19, 19);
						Pared *wall = new Pared(vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));

						wall->setFisica(mundo);
						paredes.push_back(wall);
					}
				}

				if ((*T).nombre == "Suelo") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 96, 110, 174);

					}
				}

				if ((*T).nombre == "Terminal") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 96, 110, 174);

						Terminal *ter = new Terminal(vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z),
							mundo, objeto, this);

					}
				}

			}
		}

		if ((*I).nombre == "PASILLO_6") {

			for (std::list<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {
				if ((*T).nombre == "Puerta") {

					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {
						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 20 + num * 5, 5 * num + 60, 50 - num);


						Puerta *door = new Puerta(num, vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z),
							objeto, "ABIERTA");

						door->setFisica(mundo, SM, num);
						puertas.push_back(door);
						num++;
					}

				}


				if ((*T).nombre == "Paredes") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(20, 19, 19, 19);
						Pared *wall = new Pared(vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));

						wall->setFisica(mundo);
						paredes.push_back(wall);
					}
				}

				if ((*T).nombre == "Suelo") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 96, 110, 174);

					}
				}
			}
		}

		if ((*I).nombre == "ALMACEN_1") {

			for (std::list<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {
				if ((*T).nombre == "Puerta") {

					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {
						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 20 + num * 5, 5 * num + 60, 50 - num);

						Puerta *door = new Puerta(num, vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z),
							objeto, "ABIERTA");

						door->setFisica(mundo, SM, num);
						puertas.push_back(door);
						num++;
					}

				}


				if ((*T).nombre == "Paredes") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(20, 73, 73, 73);
						Pared *wall = new Pared(vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));

						wall->setFisica(mundo);
						paredes.push_back(wall);
					}
				}

				if ((*T).nombre == "Suelo") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 10, 37, 56);

					}
				}
			}
		}

		if ((*I).nombre == "ALMACEN_2") {

			for (std::list<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {
				if ((*T).nombre == "Puerta") {

					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {
						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 20 + num * 5, 5 * num + 60, 50 - num);


						Puerta *door = new Puerta(num, vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z),
							objeto, "ABIERTA");

						door->setFisica(mundo, SM, num);
						puertas.push_back(door);
						num++;
					}

				}


				if ((*T).nombre == "Paredes") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(20, 73, 73, 73);
						Pared *wall = new Pared(vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));

						wall->setFisica(mundo);
						paredes.push_back(wall);
					}
				}

				if ((*T).nombre == "Suelo") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 10, 37, 56);
					}
				}
			}
		}

		if ((*I).nombre == "ALMACEN_3") {

			for (std::list<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {
				if ((*T).nombre == "Puerta") {

					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {
						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 20 + num * 5, 5 * num + 60, 50 - num);

						Puerta *door = new Puerta(num, vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z),
							objeto, "ABIERTA");

						door->setFisica(mundo, SM, num);
						puertas.push_back(door);
						num++;
					}

				}


				if ((*T).nombre == "Paredes") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(20, 73, 73, 73);
						Pared *wall = new Pared(vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));

						wall->setFisica(mundo);
						paredes.push_back(wall);
					}
				}

				if ((*T).nombre == "Suelo") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 10, 37, 56);

					}
				}
			}
		}

		if ((*I).nombre == "ALMACEN_4") {

			for (std::list<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {
				if ((*T).nombre == "Puerta") {

					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {
						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 20 + num * 5, 5 * num + 60, 50 - num);

						Puerta *door = new Puerta(num, vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z),
							objeto,"ABIERTA");

						door->setFisica(mundo, SM, num);
						puertas.push_back(door);
						num++;
					}

				}


				if ((*T).nombre == "Paredes") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(20, 73, 73, 73);
						Pared *wall = new Pared(vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));

						wall->setFisica(mundo);
						paredes.push_back(wall);
					}
				}

				if ((*T).nombre == "Suelo") {
					for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
							vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
							vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
							vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
						objeto->getMaterial(0).EmissiveColor.set(0, 10, 37, 56);

					}
				}
			}
		}


		if ((*I).nombre == "WAYPOINTS_ZONA1") {



			for (std::list<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {

				IMeshSceneNode *objeto = SM->addSphereSceneNode(2.0f, 16, 0, -1,
					vector3df(10 * ((*T).position.x + ((*I).position.x)), 10 * ((*T).position.y + ((*I).position.y)), 10 * ((*T).position.z + (*I).position.z)),
					vector3df((*T).rotation.x + (*I).rotation.x, (*T).rotation.y + (*I).rotation.y, (*T).rotation.z + (*I).rotation.z),
					vector3df((*T).escala.x * (*I).escala.x, (*T).escala.y * (*I).escala.y, (*T).escala.z * (*I).escala.z));
				objeto->getMaterial(0).EmissiveColor.set(20, 200, 80, 80);

				zona1->creaPuntos((*T).nombre, vector3df(10 * ((*T).position.x + ((*I).position.x)), 10 * ((*T).position.y + ((*I).position.y)), 10 * ((*T).position.z + (*I).position.z)));
				//puntos->MuestraPuntos();
				//puntos->creaPesos();
				//puntos->mostrarPesos();
			}
		}

		if ((*I).nombre == "WAYPOINTS_ZONA2") {

	


			for (std::list<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {

				IMeshSceneNode *objeto = SM->addSphereSceneNode(2.0f, 16, 0, -1,
					vector3df(10 * ((*T).position.x + ((*I).position.x)), 10 * ((*T).position.y + ((*I).position.y)), 10 * ((*T).position.z + (*I).position.z)),
					vector3df((*T).rotation.x + (*I).rotation.x, (*T).rotation.y + (*I).rotation.y, (*T).rotation.z + (*I).rotation.z),
					vector3df((*T).escala.x * (*I).escala.x, (*T).escala.y * (*I).escala.y, (*T).escala.z * (*I).escala.z));
				objeto->getMaterial(0).EmissiveColor.set(20, 200, 80, 80);

				zona2->creaPuntos((*T).nombre, vector3df(10 * ((*T).position.x + ((*I).position.x)), 10 * ((*T).position.y + ((*I).position.y)), 10 * ((*T).position.z + (*I).position.z)));
				//puntos->MuestraPuntos();
				//puntos->creaPesos();
				//puntos->mostrarPesos();
			}
		}

		if ((*I).nombre == "WAYPOINTS_ZONA3") {

			


			for (std::list<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {

				IMeshSceneNode *objeto = SM->addSphereSceneNode(2.0f, 16, 0, -1,
					vector3df(10 * ((*T).position.x + ((*I).position.x)), 10 * ((*T).position.y + ((*I).position.y)), 10 * ((*T).position.z + (*I).position.z)),
					vector3df((*T).rotation.x + (*I).rotation.x, (*T).rotation.y + (*I).rotation.y, (*T).rotation.z + (*I).rotation.z),
					vector3df((*T).escala.x * (*I).escala.x, (*T).escala.y * (*I).escala.y, (*T).escala.z * (*I).escala.z));
				objeto->getMaterial(0).EmissiveColor.set(20, 200, 80, 80);

				zona3->creaPuntos((*T).nombre, vector3df(10 * ((*T).position.x + ((*I).position.x)), 10 * ((*T).position.y + ((*I).position.y)), 10 * ((*T).position.z + (*I).position.z)));
				//puntos->MuestraPuntos();
				//puntos->creaPesos();
				//puntos->mostrarPesos();
			}
		}

	

		if ((*I).nombre == "WAYPOINTS_ZONA4") {



			for (std::list<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {

				IMeshSceneNode *objeto = SM->addSphereSceneNode(2.0f, 16, 0, -1,
					vector3df(10 * ((*T).position.x + ((*I).position.x)), 10 * ((*T).position.y + ((*I).position.y)), 10 * ((*T).position.z + (*I).position.z)),
					vector3df((*T).rotation.x + (*I).rotation.x, (*T).rotation.y + (*I).rotation.y, (*T).rotation.z + (*I).rotation.z),
					vector3df((*T).escala.x * (*I).escala.x, (*T).escala.y * (*I).escala.y, (*T).escala.z * (*I).escala.z));
				objeto->getMaterial(0).EmissiveColor.set(20, 200, 80, 80);

				zona4->creaPuntos((*T).nombre, vector3df(10 * ((*T).position.x + ((*I).position.x)), 10 * ((*T).position.y + ((*I).position.y)), 10 * ((*T).position.z + (*I).position.z)));
				//puntos->MuestraPuntos();
				//puntos->creaPesos();
				//puntos->mostrarPesos();
			}
		}

		if ((*I).nombre == "TAM") {


			tam = (*I).escala.x* (*I).escala.z * 100;

		}

		/*
		0: botiquin
		1: llave
		2: municion de pistola
		3:   " " de subfusil
		4:   " " de escopeta
		*/

		if((*I).nombre == "BOTIQUINES") {

			for (std::list<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {

				IMeshSceneNode *objeto = SM->addCubeSceneNode(2.0f, 0, -1,
					vector3df(10 * ((*T).position.x + ((*I).position.x)), 10 * ((*T).position.y + ((*I).position.y)), 10 * ((*T).position.z + (*I).position.z)),
					vector3df((*T).rotation.x + (*I).rotation.x, (*T).rotation.y + (*I).rotation.y, (*T).rotation.z + (*I).rotation.z),
					vector3df((*T).escala.x * (*I).escala.x, (*T).escala.y * (*I).escala.y, (*T).escala.z * (*I).escala.z));
				objeto->getMaterial(0).EmissiveColor.set(20, 255, 0, 0);

				Botiquines *bot = new Botiquines(objeto->getPosition(), objeto->getRotation(), objeto->getScale(), 0, objeto);

				bot->setFisica(mundo);
				objConsumables.push_back(bot);

			}
		}

		if ((*I).nombre == "MUNICION_PISTOLA") {

			for (std::list<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {

				IMeshSceneNode *municion = SM->addCubeSceneNode(1.5f, 0, -1,
					vector3df(10 * ((*T).position.x + ((*I).position.x)), 10 * ((*T).position.y + ((*I).position.y)), 10 * ((*T).position.z + (*I).position.z)),
					vector3df((*T).rotation.x + (*I).rotation.x, (*T).rotation.y + (*I).rotation.y, (*T).rotation.z + (*I).rotation.z),
					vector3df((*T).escala.x * (*I).escala.x, (*T).escala.y * (*I).escala.y, (*T).escala.z * (*I).escala.z));
				municion->getMaterial(0).EmissiveColor.set(0, 128, 0, 128);

				MunicionPistola *pistola = new MunicionPistola(municion->getPosition(), municion->getRotation(),
					municion->getScale(), 2, municion, 2, 7);
				pistola->setFisica(mundo);

				objConsumables.push_back(pistola);

			}
		}


		
		if ((*I).nombre == "MUNICION_ESCOPETA") {

			for (std::list<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {

				IMeshSceneNode *municion = SM->addCubeSceneNode(1.5f, 0, -1,
					vector3df(10 * ((*T).position.x + ((*I).position.x)), 10 * ((*T).position.y + ((*I).position.y)), 10 * ((*T).position.z + (*I).position.z)),
					vector3df((*T).rotation.x + (*I).rotation.x, (*T).rotation.y + (*I).rotation.y, (*T).rotation.z + (*I).rotation.z),
					vector3df((*T).escala.x * (*I).escala.x, (*T).escala.y * (*I).escala.y, (*T).escala.z * (*I).escala.z));
				municion->getMaterial(0).EmissiveColor.set(0, 0, 0, 128);

				MunicionEscopeta *escopeta = new MunicionEscopeta(municion->getPosition(), municion->getRotation(),
					municion->getScale(), 4, municion, 4, 2);
				escopeta->setFisica(mundo);

				objConsumables.push_back(escopeta);

			}
		}

		if ((*I).nombre == "LLAVES") {

			for (std::list<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {

				IMeshSceneNode *objeto = SM->addCubeSceneNode(1.5f, 0, -1,
					vector3df(10 * ((*T).position.x + ((*I).position.x)), 10 * ((*T).position.y + ((*I).position.y)), 10 * ((*T).position.z + (*I).position.z)),
					vector3df((*T).rotation.x + (*I).rotation.x, (*T).rotation.y + (*I).rotation.y, (*T).rotation.z + (*I).rotation.z),
					vector3df((*T).escala.x * (*I).escala.x, (*T).escala.y * (*I).escala.y, (*T).escala.z * (*I).escala.z));
				objeto->getMaterial(0).EmissiveColor.set(0, 128, 128, 128);

				Llave *llave = new Llave(objeto->getPosition(), objeto->getRotation(),
					objeto->getScale(), 1, objeto, (*T).nombre);
				llave->setFisica(mundo);

				objConsumables.push_back(llave);

			}
		}



	}
	/*vector3df(100, 5, 0);
	vector3df(100, 5, 20);
	vector3df(100, 5, 40);*/

	//creacion de la municion de prueba que habra que transladar

	//IMeshSceneNode *municion = SM->addCubeSceneNode(1.5f);
	//municion->setPosition(vector3df(100, 5, 0));
	//municion->getMaterial(0).EmissiveColor.set(0, 128, 0, 0);
	//MunicionPistola *pistola = new MunicionPistola(municion->getPosition(), municion->getRotation(),
	//	municion->getScale(), 2, municion, 2, 7);
	//pistola->setFisica(mundo);

	//IMeshSceneNode *municion1 = SM->addCubeSceneNode(1.5f);
	//municion1->setPosition(vector3df(100, 5, 20));
	//municion1->getMaterial(0).EmissiveColor.set(0, 0, 128, 0);
	//MunicionSubfusil *subfusil = new MunicionSubfusil(municion1->getPosition(), municion1->getRotation(),
	//	municion1->getScale(), 3, municion1, 3, 15);
	//subfusil->setFisica(mundo);


	//IMeshSceneNode *municion2 = SM->addCubeSceneNode(1.5f);
	//municion2->setPosition(vector3df(100, 5, 40));
	//municion2->getMaterial(0).EmissiveColor.set(0, 0, 0, 128);
	//MunicionEscopeta *escopeta = new MunicionEscopeta(municion2->getPosition(), municion2->getRotation(),
	//	municion2->getScale(), 4, municion2, 4, 2);
	//escopeta->setFisica(mundo);

	//objConsumables.push_back(pistola);
	//objConsumables.push_back(subfusil);
	//objConsumables.push_back(escopeta);
	std::cout << "-------------------------------------->" << tam << std::endl;

	waypoints.push_back(zona1); waypoints.push_back(zona2); waypoints.push_back(zona3); waypoints.push_back(zona4);

	inicializarWaypoints();
	fabricaDeEnemigos();

	//destroyWaypoints();



}

void Escenario::fabricaDeEnemigos() {

	for (std::list<ElementoPadre>::iterator I = Padres.begin(); I != Padres.end(); I++) {

		if ((*I).nombre == "CRIAS_ALIENS") {

			for (std::list<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {

				if ((*T).nombre == "zona1") {

					CriaAlien *ene = new CriaAlien(SM, VD, mundo,
						vector3df(10 * ((*T).position.x + ((*I).position.x)), 10 * ((*T).position.y + ((*I).position.y)), 10 * ((*T).position.z + (*I).position.z))
						, this, waypoints.at(0));

					enemigos.push_back(ene);
				}

				else if ((*T).nombre == "zona2") {

					CriaAlien *ene = new CriaAlien(SM, VD, mundo,
						vector3df(10 * ((*T).position.x + ((*I).position.x)), 10 * ((*T).position.y + ((*I).position.y)), 10 * ((*T).position.z + (*I).position.z))
						, this, waypoints.at(1));

					enemigos.push_back(ene);
				}

				else if ((*T).nombre == "zona3") {

					CriaAlien *ene = new CriaAlien(SM, VD, mundo,
						vector3df(10 * ((*T).position.x + ((*I).position.x)), 10 * ((*T).position.y + ((*I).position.y)), 10 * ((*T).position.z + (*I).position.z))
						, this, waypoints.at(2));

					enemigos.push_back(ene);
				}

				else if ((*T).nombre == "zona4") {

					CriaAlien *ene = new CriaAlien(SM, VD, mundo,
						vector3df(10 * ((*T).position.x + ((*I).position.x)), 10 * ((*T).position.y + ((*I).position.y)), 10 * ((*T).position.z + (*I).position.z))
						, this, waypoints.at(3));

					enemigos.push_back(ene);
				}
			}

		}

		else if ((*I).nombre == "ALIEN_BERSERKER") {

			for (std::list<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {

				if ((*T).nombre == "zona1") {

					AlienBerserker *ene = new AlienBerserker(SM, VD, mundo,
						vector3df(10 * ((*T).position.x + ((*I).position.x)), 10 * ((*T).position.y + ((*I).position.y)), 10 * ((*T).position.z + (*I).position.z))
						, waypoints.at(0));

					enemigos.push_back(ene);
				}

				else if ((*T).nombre == "zona2") {

					AlienBerserker *ene = new AlienBerserker(SM, VD, mundo,
						vector3df(10 * ((*T).position.x + ((*I).position.x)), 10 * ((*T).position.y + ((*I).position.y)), 10 * ((*T).position.z + (*I).position.z))
						, waypoints.at(1));

					enemigos.push_back(ene);
				}

				else if ((*T).nombre == "zona3") {

					AlienBerserker *ene = new AlienBerserker(SM, VD, mundo,
						vector3df(10 * ((*T).position.x + ((*I).position.x)), 10 * ((*T).position.y + ((*I).position.y)), 10 * ((*T).position.z + (*I).position.z))
						, waypoints.at(2));

					enemigos.push_back(ene);
				}

				else if ((*T).nombre == "zona4") {

					AlienBerserker *ene = new AlienBerserker(SM, VD, mundo,
						vector3df(10 * ((*T).position.x + ((*I).position.x)), 10 * ((*T).position.y + ((*I).position.y)), 10 * ((*T).position.z + (*I).position.z))
						, waypoints.at(3));
				
					enemigos.push_back(ene);
				}
			}

		}

	}


	CriaAlien *e = new CriaAlien(SM, VD, mundo,
		vector3df(50, 10, -5)
		, this, waypoints.at(0));
	e->setLider(true);
	enemigos.push_back(e);
}

void Escenario::destroyWaypoints() {

	if (!waypoints.empty()) {
		for (std::vector<Waypoints*>::iterator it = waypoints.begin(); it != waypoints.end();) {
			if ((*it) != NULL) {

				delete(*it);
				it = waypoints.erase(it);

			}
			else
				it++;
		}

	}
}


void Escenario::actualizarEstadoPersonaje()
{
	//cambiar el NULL por nullptr
	if (pers!=nullptr)
	{
		if (pers->getVivo() == false)
		{		
			delete(pers);
			pers = nullptr;
		}
	}
	
}


void Escenario::destroyPared() {

	if (!paredes.empty()) {
		for (std::list<Pared*>::iterator it = paredes.begin(); it != paredes.end();) {
			if ((*it) != NULL) {
				
					delete(*it);
					it = paredes.erase(it);
				
			}
			else
				it++;
		}

	}
}

void Escenario::actualizarEstadoPuerta()
{
	if (!puertas.empty())
	{
		for (std::list<Puerta*>::iterator it = puertas.begin(); it != puertas.end(); it++) {
			if ((*it) != NULL ) {
			
					(*it)->Update();
				
			}
		
		}

	}
}

void Escenario::actualizarObjetosConsumables()
{

	if (!objConsumables.empty()) {
		for (std::list<Objetos*>::iterator it = objConsumables.begin(); it != objConsumables.end();) {
			if ((*it) != NULL) {
				if (!(*it)->getVivo() ) {

					(*it)->destroyEntidades();
					it = objConsumables.erase(it);
				}
				else
					it++;
			}
			else
				it++;
		}

	}
}

void Escenario::inicializarWaypoints()
{
	for (std::size_t i = 0; i < waypoints.size(); i++) {
		waypoints.at(i)->setTamDelMapa(tam);
		waypoints.at(i)->crearMatriz();
		waypoints.at(i)->creaPesos(entity);

	}

}

void Escenario::actualizarListaEnemigos(f32 dt) {

	if (!enemigos.empty()) {
		for (std::list<Enemigo*>::iterator it = enemigos.begin(); it != enemigos.end();) {
			if ((*it) != NULL) {
				if (!(*it)->estaVivo()) {
					//std::cout << "HOLAAAAAA :D" << std::endl;
					delete(*it);
					it = enemigos.erase(it);
				}
				else
					it++;
			}
			else
				it++;
		}

		for (std::list<Enemigo*>::iterator it = enemigos.begin(); it != enemigos.end(); it++) {
			if ((*it) != NULL && (*it)->estaVivo() == true) {

				//estados que usan / necesitan de la logica difusa
				if((*it)->getEstado() == 3 || (*it)->getEstado() == 6 || (*it)->getEstado() == 7) {
					(*it)->setPosJugador(pers->getPos().X, pers->getPos().Z);
				}
				(*it)->Update(dt);

			}
		}
	}
}

void Escenario::cambiaEstado(std::string mensaje)
{
	 jue->cambioEstado(mensaje);
}

Personaje* Escenario::getPersonaje()
{
	return pers;
}

void Escenario::eleminarEnemigos()
{
	
	if (!enemigos.empty()) {
		for (std::list<Enemigo*>::iterator it = enemigos.begin(); it != enemigos.end();) {
			if ((*it) != NULL) {

				if ((*it)->estaVivo()) {
					(*it)->getEntity()->setLive(false);
				}
				else
					it++;
			}
			else
				it++;
		}
		
	}

	
}