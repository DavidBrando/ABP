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

#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <glm\glm.hpp>
#include "Escenario.h"
#include "Pared.h"
#include "../Fisicas/Mundo.h"
#include "../Camara.h"
#include "Puerta.h"
#include "readJson.h"
#include "Luces.h"
//#include "Terminal.h"
//#include "../Juego.h"
//#include "../Jugador/Personaje.h"
#include "../Enemigos/CriaAlien.h"
#include "../Enemigos/Waypoints.h"
#include "../Enemigos/AlienBerserker.h"
#include "../Enemigos/Enemigo.h"
//#include "Pared.h"
#include "ObjConsumables\Objetos.h"
#include "ObjConsumables\Botiquines.h"
#include "ObjConsumables\Llave.h"
#include "ObjConsumables\TiposDeMunicion\MunicionEscopeta.h"
#include "ObjConsumables\TiposDeMunicion\MunicionPistola.h"
#include "ObjConsumables\TiposDeMunicion\MunicionSubfusil.h"
#include "../Fisicas/Entity2D.h"
#include "../player.h"
#include "../ActivadorCamara.h"


Camara * Escenario::buscarCamara(int ID)
{

	for (std::size_t i = 0; i < listaDeCamaras.size(); i++) {
		if (listaDeCamaras[i]->getId() == ID) {
			return listaDeCamaras[i];
		}
	}



}

Escenario::Escenario(TGraphicEngine * motorApp, Mundo *m) {

	engine = motorApp;
	mundo = m;
	jugador = new player(motorApp, m);

	//cam->getTCamara()->desactivar();
	srand(time(NULL));
	entity = new Entity2D(m->getWorldBox2D());

}
Escenario::Escenario(const Escenario& orig) {
}

Escenario::~Escenario() {
	for (std::vector<Enemigo*>::iterator it = enemigos.begin(); it != enemigos.end(); ++it)
	{
		if ((*it) != nullptr) { delete (*it); }
	}
	enemigos.clear();
	/*for (std::vector<Pared*>::iterator it = Listparedes.begin(); it != Listparedes.end(); ++it)
	{
		if ((*it) != nullptr) { delete (*it); }
	}*/
	Listparedes.clear();
	for (std::vector<Luces*>::iterator it = ListLuces.begin(); it != ListLuces.end(); ++it)
	{
		if ((*it) != nullptr) { delete (*it); }
	}
	ListLuces.clear();
	/*for (std::vector<Puerta*>::iterator it = puertas.begin(); it != puertas.end(); ++it)
	{
		if ((*it) != nullptr) { delete (*it); }
	}*/
	puertas.clear();
	for (std::vector<Camara*>::iterator it = listaDeCamaras.begin(); it != listaDeCamaras.end(); ++it)
	{
		if ((*it) != nullptr) { delete (*it); }
	}
	listaDeCamaras.clear();
	for (std::vector<Waypoints*>::iterator it = waypoints.begin(); it != waypoints.end(); ++it)
	{
		if ((*it) != nullptr) { delete (*it); }
	}
	waypoints.clear();
	delete jugador;
	delete entity;
	std::cout << "Escenario Destroyed" << std::endl;

}

void Escenario::setPadres(std::string nombre, double t[], double r[], double s[], std::vector<Escenario::ElementoHijo> objetos) {
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

void Escenario::setHijos(std::string nombre, double t[], double r[], double s[], std::vector<Escenario::Elemento> objetos) {
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

std::vector<Escenario::ElementoHijo> Escenario::getHijos() {
	return Hijos;
}

std::vector<Escenario::Elemento> Escenario::getSubHijos() {
	return SubHijos;
}

std::vector<Pared*> Escenario::getParedes() {

	return Listparedes;
}

int Escenario::getTam() {
	return tam;
}

void Escenario::muestraEstructura() {
	cout << "/////////////////////////////////////////////////////" << endl;
	for (std::vector<ElementoPadre>::iterator I = Padres.begin(); I != Padres.end(); I++) {
		std::cout << "Padre: " << (*I).nombre << std::endl;
		std::cout << "  Posicion: x=" << (*I).position.x << " y= " << (*I).position.y << " z= " << (*I).position.z << std::endl;
		std::cout << "  Rotacion: x=" << (*I).rotation.x << " y= " << (*I).rotation.y << " z= " << (*I).rotation.z << std::endl;
		std::cout << "  Escala: x=" << (*I).escala.x << " y= " << (*I).escala.y << " z= " << (*I).escala.z << std::endl;

		for (std::vector<ElementoHijo>::iterator M = (*I).ObjetosEscena.begin(); M != (*I).ObjetosEscena.end(); M++) {
			cout << "..............................................." << endl;
			std::cout << "      Hijo: " << (*M).nombre << std::endl;
			std::cout << "          Posicion: x=" << (*M).position.x << " y= " << (*M).position.y << " z= " << (*M).position.z << std::endl;
			std::cout << "          Rotacion: x=" << (*M).rotation.x << " y= " << (*M).rotation.y << " z= " << (*M).rotation.z << std::endl;
			std::cout << "          Escala: x=" << (*M).escala.x << " y= " << (*M).escala.y << " z= " << (*M).escala.z << std::endl;
			for (std::vector<Elemento>::iterator N = (*M).ObjetosEscena.begin(); N != (*M).ObjetosEscena.end(); N++) {
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
	int camaras = -1;
	//Waypoints *puntos = new Waypoints();
	
	Waypoints *zona1 = new Waypoints();
	Waypoints *zona2 = new Waypoints();
	Waypoints *zona3 = new Waypoints();
	Waypoints *zona4 = new Waypoints();
	float tx, ty, tz, rx, ry, rz, ex, ey, ez;
	float txA, tyA, tzA, rxA, ryA, rzA, exA, eyA, ezA;
	std::string aux;
	//Camara *cam = new Camara(engine, true,
	//	glm::vec3(0, 0, 0),
	//	glm::vec3(0, 0, 0),
	//	glm::vec3(1, 1, 1));
	ActivadorCamara * Active;

	for (std::vector<ElementoPadre>::iterator I = Padres.begin(); I != Padres.end(); I++) {

		std::cout << "salida: " << (*I).nombre << std::endl;

		if ((*I).nombre == "Paredes") {
			for (std::vector<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {
							tx = ((*T).position.x + (*I).position.x);
							ty = ((*T).position.y + (*I).position.y);
							tz = ((*T).position.z + (*I).position.z);

							rx = ((*T).rotation.x + (*I).rotation.x);
							ry = ((*T).rotation.y + (*I).rotation.y);
							rz = ((*T).rotation.z + (*I).rotation.z);

							ex = ((*T).escala.x * (*I).escala.x);
							ey = ((*T).escala.y * (*I).escala.y);
							ez = ((*T).escala.z * (*I).escala.z);

							Pared * wall = new Pared(engine, glm::vec3(tx, 0, -tz), glm::vec3(rx, ry, rz), glm::vec3(ex, ey, ez), "");
							wall->setFisicas(mundo);
							Listparedes.push_back(wall);

							}
						}

		if ((*I).nombre == "Luces") {

			for (std::vector<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {
				tx = ((*T).position.x + (*I).position.x);
				ty = ((*T).position.y + (*I).position.y);
				tz = ((*T).position.z + (*I).position.z);

				rx = ((*T).rotation.x + (*I).rotation.x);
				ry = ((*T).rotation.y + (*I).rotation.y);
				rz = ((*T).rotation.z + (*I).rotation.z);

				ex = ((*T).escala.x * (*I).escala.x);
				ey = ((*T).escala.y * (*I).escala.y);
				ez = ((*T).escala.z * (*I).escala.z);

				int ID;
				std::stringstream((*T).nombre) >> ID;

				std::cout << "Lus ID: " << ID << " " << tx << " " << ty <<" "<< -tz << std::endl;

				Luces * luz = new Luces(engine, glm::vec3(tx, ty, -tz),
					glm::vec3(rx, ry, -rz),
					glm::vec3(ex, ey, ez), ID);
				if (ListLuces.empty())
				{	luz->activar();
					luz->setLocal(true);
					luz->setFoco(false);
					float v[3] = { 0.25f, 0.25f, 0.25f };
					luz->setAmbient(v);
					v[0] = 20.0f;
					v[1] = 20.0f;
					v[2] = 20.0f;
					luz->setColor(v);
					luz->setAtenuacionConstante(1.0f);
					luz->setAtenuacionLiniar(0.09f);
					luz->setAtenuacionCuadratica(0.032f);
					v[0] = (float)(tx);
					v[1] = (float)ty;
					v[2] = (float)(-tz);
					luz->setDireccionLuz(v);
					luz->setExponentFoco(glm::cos(glm::radians(15.0f)));
					luz->setCosCutOffFoco(glm::cos(glm::radians(12.5f)));
					luzActual = luz;
				}
				ListLuces.push_back(luz);
			}
		}
		if ((*I).nombre == "CamarasSeguimiento") {
		

			for (std::vector<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {
			

					if ((*T).nombre == "PosCam") {

						tx = ((*T).position.x + (*I).position.x);
						ty = ((*T).position.y + (*I).position.y);
						tz = ((*T).position.z + (*I).position.z);

						rx = ((*T).rotation.x + (*I).rotation.x);
						ry = ((*T).rotation.y + (*I).rotation.y);
						rz = ((*T).rotation.z + (*I).rotation.z);

						ex = ((*T).escala.x * (*I).escala.x);
						ey = ((*T).escala.y * (*I).escala.y);
						ez = ((*T).escala.z * (*I).escala.z);

						for (std::vector<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {
							
							int ID;
							std::stringstream((*N).nombre) >> ID;
							std::cout << "CAMARASEGUIMIENTO ID: " << ID << std::endl;
								Camara *cam = new Camara(engine, ID, true, true,
									glm::vec3(tx, ty, -tz),
									glm::vec3(rx, ry, rz),
									glm::vec3(1, 1, 1));

								listaDeCamaras.push_back(cam);
								camaras++;


						

						}

					}
				
			}
		}

		if ((*I).nombre == "CamarasFijas") {


			for (std::vector<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {

				if ((*T).nombre == "PosCam") {

						tx = ((*T).position.x + (*I).position.x);
						ty = ((*T).position.y + (*I).position.y);
						tz = ((*T).position.z + (*I).position.z);

						rx = ((*T).rotation.x + (*I).rotation.x);
						ry = ((*T).rotation.y + (*I).rotation.y);
						rz = ( (*T).rotation.z + (*I).rotation.z);

						ex = ((*T).escala.x * (*I).escala.x);
						ey = ((*T).escala.y * (*I).escala.y);
						ez = ((*T).escala.z * (*I).escala.z);

					for (std::vector<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						int ID;
						std::stringstream((*N).nombre) >> ID;
						std::cout << "CAMARAFIJA ID: " << ID << std::endl;

							Camara *cam = new Camara(engine, ID, true, false,
								glm::vec3(tx, ty, -tz),
								glm::vec3(rx, ry, rz),
								glm::vec3(1, 1, 1));

							listaDeCamaras.push_back(cam);
							camaras++;


						
					}

				}

			}
		}

		if ((*I).nombre == "CamarasDePasillos") {

			for (std::vector<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {


				if ((*T).nombre == "PosCam") {

					tx = ((*T).position.x + (*I).position.x);
					ty = ((*T).position.y + (*I).position.y);
					tz = ((*T).position.z + (*I).position.z);

					rx = ((*T).rotation.x + (*I).rotation.x);
					ry = ((*T).rotation.y + (*I).rotation.y);
					rz = ((*T).rotation.z + (*I).rotation.z);

					ex = ((*T).escala.x * (*I).escala.x);
					ey = ((*T).escala.y * (*I).escala.y);
					ez = ((*T).escala.z * (*I).escala.z);

					for (std::vector<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						int ID;
						std::stringstream((*N).nombre) >> ID;
						std::cout << "CAMARASPASILLOS ID: " << ID << std::endl;


						Camara *cam = new Camara(engine, ID, true, false,
							glm::vec3(tx, ty, -tz),
							glm::vec3(rx, ry, rz),
							glm::vec3(1, 1, 1));

						listaDeCamaras.push_back(cam);
						camaras++;




					}

				}

			}

		}


		if ((*I).nombre == "PlanosDeCambio") {


			for (std::vector<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {

				if ((*T).nombre == "Activador") {

				

					for (std::vector<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {
						int res;

						tx = ((*N).position.x + (*T).position.x + (*I).position.x);
						ty = ((*N).position.y + (*T).position.y + (*I).position.y);
						tz = ((*N).position.z + (*T).position.z + (*I).position.z);

						rx = ((*N).rotation.x + (*T).rotation.x + (*I).rotation.x);
						ry = ((*N).rotation.y + (*T).rotation.y + (*I).rotation.y);
						rz = ((*N).rotation.z + (*T).rotation.z + (*I).rotation.z);

						ex = ((*N).escala.x * (*T).escala.x * (*I).escala.x);
						ey = ((*N).escala.y * (*T).escala.y * (*I).escala.y);
						ez = ((*N).escala.z * (*T).escala.z * (*I).escala.z);

						std::stringstream((*N).nombre) >> res;
						std::cout << "ACTIVADOR ID: " << res << std::endl;

						Camara *cam = buscarCamara(res);

						Active = new ActivadorCamara(engine, mundo, res, glm::vec3(tx, ty, -tz),
							glm::vec3(rx, ry, -rz),
							glm::vec3(ex, ey, ez),
							cam);
					}
				}
			}

		}



		if ((*I).nombre == "HANGAR") {
			for (std::vector<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {

				

				if ((*T).nombre == "Modelo") {
						//	std::cout << "entra" << std::endl;

						tx = ((*T).position.x + (*I).position.x);
						ty = ((*T).position.y + (*I).position.y);
						tz = ((*T).position.z + (*I).position.z);

						rx = ((*T).rotation.x + (*I).rotation.x);
						ry = ((*T).rotation.y + (*I).rotation.y);
						rz = ((*T).rotation.z + (*I).rotation.z);

						ex = ((*T).escala.x * (*I).escala.x);
						ey = ((*T).escala.y * (*I).escala.y);
						ez = ((*T).escala.z * (*I).escala.z);

						std::cout << "ROTACIONES 1" << std::endl;
						std::cout << "X: " << rx << std::endl;
						std::cout << "Y: " << ry << std::endl;
						std::cout << "Z: " << rz << std::endl;
						std::cout << "///////////" << std::endl;
						std::cout << "trans 1" << std::endl;
						std::cout << "X: " << tx << std::endl;
						std::cout << "Y: " << ty << std::endl;
						std::cout << "Z: " << tz << std::endl;

						Pared * wall = new Pared(engine, glm::vec3(tx, ty, -tz ),
							glm::vec3(rx, ry, rz),
							glm::vec3(ex, ey, ez),"hangar");

				}

				if ((*T).nombre == "Modelo-Puerta-ABIERTA-ARRIBA-H") {
					//	std::cout << "entra" << std::endl;
					for (std::vector<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {
						
						

						tx = ((*N).position.x + (*T).position.x + (*I).position.x);
						ty = ((*N).position.y + (*T).position.y + (*I).position.y);
						tz = ((*N).position.z + (*T).position.z + (*I).position.z);

						rx = ((*N).rotation.x + (*T).rotation.x + (*I).rotation.x);
						ry = ((*N).rotation.y + (*T).rotation.y + (*I).rotation.y);
						rz = ((*N).rotation.z + (*T).rotation.z + (*I).rotation.z);

						ex = ((*N).escala.x * (*T).escala.x * (*I).escala.x);
						ey = ((*N).escala.y * (*T).escala.y * (*I).escala.y);
						ez = ((*N).escala.z * (*T).escala.z * (*I).escala.z);


						Puerta * door = new Puerta(engine,num, glm::vec3(tx+1, ty, -tz),
							glm::vec3(rx, ry, -rz),
							glm::vec3(ex, ey, ez), "ABIERTA","ARRIBA",(*N).nombre);
						door->setFisica(mundo, num);
						puertas.push_back(door);
						num++;
					
					}

				}

				if ((*T).nombre == "Modelo-Puerta-ABIERTA-LATERAL-H") {
					//	std::cout << "entra" << std::endl;
					for (std::vector<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						if (N == (*T).ObjetosEscena.begin()) {

							txA = ((*N).position.x + (*T).position.x + (*I).position.x);
							tyA = ((*N).position.y + (*T).position.y + (*I).position.y);
							tzA = ((*N).position.z + (*T).position.z + (*I).position.z);

							rxA = ((*N).rotation.x + (*T).rotation.x + (*I).rotation.x);
							ryA = ((*N).rotation.y + (*T).rotation.y + (*I).rotation.y);
							rzA = ((*N).rotation.z + (*T).rotation.z + (*I).rotation.z);

							exA = ((*N).escala.x * (*T).escala.x * (*I).escala.x);
							eyA = ((*N).escala.y * (*T).escala.y * (*I).escala.y);
							ezA = ((*N).escala.z * (*T).escala.z * (*I).escala.z);

							aux = (*N).nombre;

						}

						else {

							tx = ((*N).position.x + (*T).position.x + (*I).position.x);
							ty = ((*N).position.y + (*T).position.y + (*I).position.y);
							tz = ((*N).position.z + (*T).position.z + (*I).position.z);

							rx = ((*N).rotation.x + (*T).rotation.x + (*I).rotation.x);
							ry = ((*N).rotation.y + (*T).rotation.y + (*I).rotation.y);
							rz = ((*N).rotation.z + (*T).rotation.z + (*I).rotation.z);

							ex = ((*N).escala.x * (*T).escala.x * (*I).escala.x);
							ey = ((*N).escala.y * (*T).escala.y * (*I).escala.y);
							ez = ((*N).escala.z * (*T).escala.z * (*I).escala.z);

							//Puerta(TGraphicEngine * motorApp, int ident, glm::vec3 posicion, glm::vec3 rotacion, glm::vec3 escala, std::string llave, std::string tipo,
							//std::string model, glm::vec3 posicion2, glm::vec3 rotacion2, glm::vec3 escala2, std::string modelB);

							Puerta * door = new Puerta(engine, num, glm::vec3(txA, tyA, -tzA),
								glm::vec3(rxA, ryA - 180, -rzA),
								glm::vec3(exA, eyA, ezA), "ABIERTA", "LATERAL", aux,
								glm::vec3(tx, ty, -tz),
								glm::vec3(rx, ry - 180, -rz),
								glm::vec3(ex, ey, ez),
								(*N).nombre);

							door->setFisica(mundo, num);
							door->setFisicas(mundo, num, glm::vec3(tx, ty, -tz),
								glm::vec3(rx, ry - 180, -rz),
								glm::vec3(ex, ey, ez));
							puertas.push_back(door);
							num++;
						}

					}

				}
				

				
			}
		}

	//	//hay que poner un if de puerta doble
		if ((*I).nombre == "SALA_ESPERA") {

		

			for (std::vector<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {


				if ((*T).nombre == "Modelo") {

					tx = ((*T).position.x + (*I).position.x);
					ty = ((*T).position.y + (*I).position.y);
					tz = ((*T).position.z + (*I).position.z);

					rx = ((*T).rotation.x + (*I).rotation.x);
					ry = ((*T).rotation.y + (*I).rotation.y);
					rz = ((*T).rotation.z + (*I).rotation.z);

					ex = ((*T).escala.x * (*I).escala.x);
					ey = ((*T).escala.y * (*I).escala.y);
					ez = ((*T).escala.z * (*I).escala.z);

					std::cout << "ROTACIONES 1" << std::endl;
					std::cout << "X: " << rx << std::endl;
					std::cout << "Y: " << ry << std::endl;
					std::cout << "Z: " << rz << std::endl;

					std::cout << "///////////" << std::endl;
					std::cout << "trans 1" << std::endl;
					std::cout << "X: " << tx << std::endl;
					std::cout << "Y: " << ty << std::endl;
					std::cout << "Z: " << tz << std::endl;

					Pared * wall = new Pared(engine, glm::vec3(tx, ty, -tz),
						glm::vec3(rx, ry, rz),
						glm::vec3(ex, ey, ez), "sala_espera");

				}

				if ((*T).nombre == "Modelo-Puerta-ABIERTA-LATERAL-V") {
					//	std::cout << "entra" << std::endl;
					for (std::vector<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						if (N == (*T).ObjetosEscena.begin()) {

							txA = ((*N).position.x + (*T).position.x + (*I).position.x);
							tyA = ((*N).position.y + (*T).position.y + (*I).position.y);
							tzA = ((*N).position.z + (*T).position.z + (*I).position.z);

							rxA = ((*N).rotation.x + (*T).rotation.x + (*I).rotation.x);
							ryA = ((*N).rotation.y + (*T).rotation.y + (*I).rotation.y);
							rzA = ((*N).rotation.z + (*T).rotation.z + (*I).rotation.z);

							exA = ((*N).escala.x * (*T).escala.x * (*I).escala.x);
							eyA = ((*N).escala.y * (*T).escala.y * (*I).escala.y);
							ezA = ((*N).escala.z * (*T).escala.z * (*I).escala.z);

							aux = (*N).nombre;

						}

						else {

							tx = ((*N).position.x + (*T).position.x + (*I).position.x);
							ty = ((*N).position.y + (*T).position.y + (*I).position.y);
							tz = ((*N).position.z + (*T).position.z + (*I).position.z);

							rx = ((*N).rotation.x + (*T).rotation.x + (*I).rotation.x);
							ry = ((*N).rotation.y + (*T).rotation.y + (*I).rotation.y);
							rz = ((*N).rotation.z + (*T).rotation.z + (*I).rotation.z);

							ex = ((*N).escala.x * (*T).escala.x * (*I).escala.x);
							ey = ((*N).escala.y * (*T).escala.y * (*I).escala.y);
							ez = ((*N).escala.z * (*T).escala.z * (*I).escala.z);

							//Puerta(TGraphicEngine * motorApp, int ident, glm::vec3 posicion, glm::vec3 rotacion, glm::vec3 escala, std::string llave, std::string tipo,
							//std::string model, glm::vec3 posicion2, glm::vec3 rotacion2, glm::vec3 escala2, std::string modelB);

							Puerta * door = new Puerta(engine, num, glm::vec3(txA, tyA, -tzA),
								glm::vec3(rxA, ryA, -rzA),
								glm::vec3(exA, eyA, ezA), "ABIERTA", "LATERAL", aux,
								glm::vec3(tx, ty, -tz),
								glm::vec3(rx, ry, -rz),
								glm::vec3(ex, ey, ez),
								(*N).nombre);

							door->setFisica(mundo, num);
							door->setFisicas(mundo, num, glm::vec3(tx, ty, -tz),
								glm::vec3(rx, ry, -rz),
								glm::vec3(ex, ey, ez));
							puertas.push_back(door);
							num++;
						}

					}

				}
			}
		}

		if ((*I).nombre == "HALL") {
			

			for (std::vector<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {
			
				std::cout << "salida: " << (*T).nombre << std::endl;

				if ((*T).nombre == "Modelo") {

					tx = ((*T).position.x + (*I).position.x);
					ty = ((*T).position.y + (*I).position.y);
					tz = ((*T).position.z + (*I).position.z);

					rx = ((*T).rotation.x + (*I).rotation.x);
					ry = ((*T).rotation.y + (*I).rotation.y);
					rz = ((*T).rotation.z + (*I).rotation.z);

					ex = ((*T).escala.x * (*I).escala.x);
					ey = ((*T).escala.y * (*I).escala.y);
					ez = ((*T).escala.z * (*I).escala.z);

					std::cout << "ROTACIONES 1" << std::endl;
					std::cout << "X: " << rx << std::endl;
					std::cout << "Y: " << ry << std::endl;
					std::cout << "Z: " << rz << std::endl;

					std::cout << "///////////" << std::endl;
					std::cout << "trans 1" << std::endl;
					std::cout << "X: " << tx << std::endl;
					std::cout << "Y: " << ty << std::endl;
					std::cout << "Z: " << tz << std::endl;

					Pared * wall = new Pared(engine, glm::vec3(tx, ty, -tz),
						glm::vec3(rx, ry, rz),
						glm::vec3(ex, ey, ez), "hall");

				}
					if ((*T).nombre == "Modelo-Puerta-ABIERTA-LATERAL-H") {
					//	std::cout << "entra" << std::endl;
					for (std::vector<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						if (N == (*T).ObjetosEscena.begin()) {

							txA = ((*N).position.x + (*T).position.x + (*I).position.x);
							tyA = ((*N).position.y + (*T).position.y + (*I).position.y);
							tzA = ((*N).position.z + (*T).position.z + (*I).position.z);

							rxA = ((*N).rotation.x + (*T).rotation.x + (*I).rotation.x);
							ryA = ((*N).rotation.y + (*T).rotation.y + (*I).rotation.y);
							rzA = ((*N).rotation.z + (*T).rotation.z + (*I).rotation.z);

							exA = ((*N).escala.x * (*T).escala.x * (*I).escala.x);
							eyA = ((*N).escala.y * (*T).escala.y * (*I).escala.y);
							ezA = ((*N).escala.z * (*T).escala.z * (*I).escala.z);

							aux = (*N).nombre;

						}

						else {

							tx = ((*N).position.x + (*T).position.x + (*I).position.x);
							ty = ((*N).position.y + (*T).position.y + (*I).position.y);
							tz = ((*N).position.z + (*T).position.z + (*I).position.z);

							rx = ((*N).rotation.x + (*T).rotation.x + (*I).rotation.x);
							ry = ((*N).rotation.y + (*T).rotation.y + (*I).rotation.y);
							rz = ((*N).rotation.z + (*T).rotation.z + (*I).rotation.z);

							ex = ((*N).escala.x * (*T).escala.x * (*I).escala.x);
							ey = ((*N).escala.y * (*T).escala.y * (*I).escala.y);
							ez = ((*N).escala.z * (*T).escala.z * (*I).escala.z);

							//Puerta(TGraphicEngine * motorApp, int ident, glm::vec3 posicion, glm::vec3 rotacion, glm::vec3 escala, std::string llave, std::string tipo,
							//std::string model, glm::vec3 posicion2, glm::vec3 rotacion2, glm::vec3 escala2, std::string modelB);

							Puerta * door = new Puerta(engine, num, glm::vec3(txA, tyA, -tzA),
								glm::vec3(rxA, ryA - 180, -rzA),
								glm::vec3(exA, eyA, ezA), "ABIERTA", "LATERAL", aux,
								glm::vec3(tx, ty, -tz),
								glm::vec3(rx, ry - 180, -rz),
								glm::vec3(ex, ey, ez),
								(*N).nombre);

							door->setFisica(mundo, num);
							door->setFisicas(mundo, num, glm::vec3(tx, ty, -tz),
								glm::vec3(rx, ry - 180, -rz),
								glm::vec3(ex, ey, ez));
							puertas.push_back(door);
							num++;
						}

					}

				}

					if ((*T).nombre == "Modelo-Puerta-ABIERTA-LATERAL-V") {
						//	std::cout << "entra" << std::endl;
						for (std::vector<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

							if (N == (*T).ObjetosEscena.begin()) {

								txA = ((*N).position.x + (*T).position.x + (*I).position.x);
								tyA = ((*N).position.y + (*T).position.y + (*I).position.y);
								tzA = ((*N).position.z + (*T).position.z + (*I).position.z);

								rxA = ((*N).rotation.x + (*T).rotation.x + (*I).rotation.x);
								ryA = ((*N).rotation.y + (*T).rotation.y + (*I).rotation.y);
								rzA = ((*N).rotation.z + (*T).rotation.z + (*I).rotation.z);

								exA = ((*N).escala.x * (*T).escala.x * (*I).escala.x);
								eyA = ((*N).escala.y * (*T).escala.y * (*I).escala.y);
								ezA = ((*N).escala.z * (*T).escala.z * (*I).escala.z);

								aux = (*N).nombre;

							}

							else {

								tx = ((*N).position.x + (*T).position.x + (*I).position.x);
								ty = ((*N).position.y + (*T).position.y + (*I).position.y);
								tz = ((*N).position.z + (*T).position.z + (*I).position.z);

								rx = ((*N).rotation.x + (*T).rotation.x + (*I).rotation.x);
								ry = ((*N).rotation.y + (*T).rotation.y + (*I).rotation.y);
								rz = ((*N).rotation.z + (*T).rotation.z + (*I).rotation.z);

								ex = ((*N).escala.x * (*T).escala.x * (*I).escala.x);
								ey = ((*N).escala.y * (*T).escala.y * (*I).escala.y);
								ez = ((*N).escala.z * (*T).escala.z * (*I).escala.z);

								//Puerta(TGraphicEngine * motorApp, int ident, glm::vec3 posicion, glm::vec3 rotacion, glm::vec3 escala, std::string llave, std::string tipo,
								//std::string model, glm::vec3 posicion2, glm::vec3 rotacion2, glm::vec3 escala2, std::string modelB);

								Puerta * door = new Puerta(engine, num, glm::vec3(txA, tyA, -tzA),
									glm::vec3(rxA, ryA, -rzA),
									glm::vec3(exA, eyA, ezA), "ABIERTA", "LATERAL", aux,
									glm::vec3(tx, ty, -tz),
									glm::vec3(rx, ry, -rz),
									glm::vec3(ex, ey, ez),
									(*N).nombre);

								door->setFisica(mundo, num);
								door->setFisicas(mundo, num, glm::vec3(tx, ty, -tz),
									glm::vec3(rx, ry, -rz),
									glm::vec3(ex, ey, ez));
								puertas.push_back(door);
								num++;
							}

						}

					}


			}
		}



		if ((*I).nombre == "GENERADOR") {
		
			for (std::vector<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {

				if ((*T).nombre == "Modelo") {

					tx = ((*T).position.x + (*I).position.x);
					ty = ((*T).position.y + (*I).position.y);
					tz = ((*T).position.z + (*I).position.z);

					rx = ((*T).rotation.x + (*I).rotation.x);
					ry = ((*T).rotation.y + (*I).rotation.y);
					rz = ((*T).rotation.z + (*I).rotation.z);

					ex = ((*T).escala.x * (*I).escala.x);
					ey = ((*T).escala.y * (*I).escala.y);
					ez = ((*T).escala.z * (*I).escala.z);

					std::cout << "ROTACIONES 1" << std::endl;
					std::cout << "X: " << rx << std::endl;
					std::cout << "Y: " << ry << std::endl;
					std::cout << "Z: " << rz << std::endl;

					std::cout << "///////////" << std::endl;
					std::cout << "trans 1" << std::endl;
					std::cout << "X: " << tx << std::endl;
					std::cout << "Y: " << ty << std::endl;
					std::cout << "Z: " << tz << std::endl;

					Pared * wall = new Pared(engine, glm::vec3(tx, ty, -tz),
						glm::vec3(rx, ry, rz),
						glm::vec3(ex, ey, ez), "generador");

				}

				if ((*T).nombre == "Modelo-Puerta-ABIERTA-LATERAL-H") {
					//	std::cout << "entra" << std::endl;
					for (std::vector<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						if (N == (*T).ObjetosEscena.begin()) {

							txA = ((*N).position.x + (*T).position.x + (*I).position.x);
							tyA = ((*N).position.y + (*T).position.y + (*I).position.y);
							tzA = ((*N).position.z + (*T).position.z + (*I).position.z);

							rxA = ((*N).rotation.x + (*T).rotation.x + (*I).rotation.x);
							ryA = ((*N).rotation.y + (*T).rotation.y + (*I).rotation.y);
							rzA = ((*N).rotation.z + (*T).rotation.z + (*I).rotation.z);

							exA = ((*N).escala.x * (*T).escala.x * (*I).escala.x);
							eyA = ((*N).escala.y * (*T).escala.y * (*I).escala.y);
							ezA = ((*N).escala.z * (*T).escala.z * (*I).escala.z);

							aux = (*N).nombre;

						}

						else {

							tx = ((*N).position.x + (*T).position.x + (*I).position.x);
							ty = ((*N).position.y + (*T).position.y + (*I).position.y);
							tz = ((*N).position.z + (*T).position.z + (*I).position.z);

							rx = ((*N).rotation.x + (*T).rotation.x + (*I).rotation.x);
							ry = ((*N).rotation.y + (*T).rotation.y + (*I).rotation.y);
							rz = ((*N).rotation.z + (*T).rotation.z + (*I).rotation.z);

							ex = ((*N).escala.x * (*T).escala.x * (*I).escala.x);
							ey = ((*N).escala.y * (*T).escala.y * (*I).escala.y);
							ez = ((*N).escala.z * (*T).escala.z * (*I).escala.z);

							//Puerta(TGraphicEngine * motorApp, int ident, glm::vec3 posicion, glm::vec3 rotacion, glm::vec3 escala, std::string llave, std::string tipo,
							//std::string model, glm::vec3 posicion2, glm::vec3 rotacion2, glm::vec3 escala2, std::string modelB);

							Puerta * door = new Puerta(engine, num, glm::vec3(txA, tyA, -tzA),
								glm::vec3(rxA, ryA - 180, -rzA),
								glm::vec3(exA, eyA, ezA), "ABIERTA", "LATERAL", aux,
								glm::vec3(tx, ty, -tz),
								glm::vec3(rx, ry - 180, -rz),
								glm::vec3(ex, ey, ez),
								(*N).nombre);

							door->setFisica(mundo, num);
							door->setFisicas(mundo, num, glm::vec3(tx, ty, -tz),
								glm::vec3(rx, ry - 180, -rz),
								glm::vec3(ex, ey, ez));
							puertas.push_back(door);
							num++;
						}

					}

				}
			}

		}

		if ((*I).nombre == "MANTENIMIENTO") {
			for (std::vector<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {



				if ((*T).nombre == "Modelo") {

					tx = ((*T).position.x + (*I).position.x);
					ty = ((*T).position.y + (*I).position.y);
					tz = ((*T).position.z + (*I).position.z);

					rx = ((*T).rotation.x + (*I).rotation.x);
					ry = ((*T).rotation.y + (*I).rotation.y);
					rz = ((*T).rotation.z + (*I).rotation.z);

					ex = ((*T).escala.x * (*I).escala.x);
					ey = ((*T).escala.y * (*I).escala.y);
					ez = ((*T).escala.z * (*I).escala.z);

					std::cout << "ROTACIONES 1" << std::endl;
					std::cout << "X: " << rx << std::endl;
					std::cout << "Y: " << ry << std::endl;
					std::cout << "Z: " << rz << std::endl;
					std::cout << "///////////" << std::endl;
					std::cout << "trans 1" << std::endl;
					std::cout << "X: " << tx << std::endl;
					std::cout << "Y: " << ty << std::endl;
					std::cout << "Z: " << tz << std::endl;
					Pared * wall = new Pared(engine, glm::vec3(tx, ty, -tz),
						glm::vec3(rx, ry, rz),
						glm::vec3(ex, ey, ez), "mantenimiento");

				}


				if ((*T).nombre == "Modelo-Puerta-ABIERTA-LATERAL-V") {
					//	std::cout << "entra" << std::endl;
					for (std::vector<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						if (N == (*T).ObjetosEscena.begin()) {

							txA = ((*N).position.x + (*T).position.x + (*I).position.x);
							tyA = ((*N).position.y + (*T).position.y + (*I).position.y);
							tzA = ((*N).position.z + (*T).position.z + (*I).position.z);

							rxA = ((*N).rotation.x + (*T).rotation.x + (*I).rotation.x);
							ryA = ((*N).rotation.y + (*T).rotation.y + (*I).rotation.y);
							rzA = ((*N).rotation.z + (*T).rotation.z + (*I).rotation.z);

							exA = ((*N).escala.x * (*T).escala.x * (*I).escala.x);
							eyA = ((*N).escala.y * (*T).escala.y * (*I).escala.y);
							ezA = ((*N).escala.z * (*T).escala.z * (*I).escala.z);

							aux = (*N).nombre;

						}

						else {

							tx = ((*N).position.x + (*T).position.x + (*I).position.x);
							ty = ((*N).position.y + (*T).position.y + (*I).position.y);
							tz = ((*N).position.z + (*T).position.z + (*I).position.z);

							rx = ((*N).rotation.x + (*T).rotation.x + (*I).rotation.x);
							ry = ((*N).rotation.y + (*T).rotation.y + (*I).rotation.y);
							rz = ((*N).rotation.z + (*T).rotation.z + (*I).rotation.z);

							ex = ((*N).escala.x * (*T).escala.x * (*I).escala.x);
							ey = ((*N).escala.y * (*T).escala.y * (*I).escala.y);
							ez = ((*N).escala.z * (*T).escala.z * (*I).escala.z);

							//Puerta(TGraphicEngine * motorApp, int ident, glm::vec3 posicion, glm::vec3 rotacion, glm::vec3 escala, std::string llave, std::string tipo,
							//std::string model, glm::vec3 posicion2, glm::vec3 rotacion2, glm::vec3 escala2, std::string modelB);

							Puerta * door = new Puerta(engine, num, glm::vec3(txA, tyA, -tzA),
								glm::vec3(rxA, ryA, -rzA),
								glm::vec3(exA, eyA, ezA), "ABIERTA", "LATERAL", aux,
								glm::vec3(tx, ty, -tz),
								glm::vec3(rx, ry, -rz),
								glm::vec3(ex, ey, ez),
								(*N).nombre);

							door->setFisica(mundo, num);
							door->setFisicas(mundo, num, glm::vec3(tx, ty, -tz),
								glm::vec3(rx, ry, -rz),
								glm::vec3(ex, ey, ez));
							puertas.push_back(door);
							num++;
						}

					}

				}
			}
		}

		if ((*I).nombre == "CANTINA") {
			for (std::vector<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {


				if ((*T).nombre == "Modelo") {

					tx = ((*T).position.x + (*I).position.x);
					ty = ((*T).position.y + (*I).position.y);
					tz = ((*T).position.z + (*I).position.z);

					rx = ((*T).rotation.x + (*I).rotation.x);
					ry = ((*T).rotation.y + (*I).rotation.y);
					rz = ((*T).rotation.z + (*I).rotation.z);

					ex = ((*T).escala.x * (*I).escala.x);
					ey = ((*T).escala.y * (*I).escala.y);
					ez = ((*T).escala.z * (*I).escala.z);

					std::cout << "ROTACIONES 1" << std::endl;
					std::cout << "X: " << rx << std::endl;
					std::cout << "Y: " << ry << std::endl;
					std::cout << "Z: " << rz << std::endl;
					std::cout << "///////////" << std::endl;
					std::cout << "trans 1" << std::endl;
					std::cout << "X: " << tx << std::endl;
					std::cout << "Y: " << ty << std::endl;
					std::cout << "Z: " << tz << std::endl;
					Pared * wall = new Pared(engine, glm::vec3(tx, ty, -tz),
						glm::vec3(rx, ry, rz),
						glm::vec3(ex, ey, ez), "cantina");

				}


				if ((*T).nombre == "Modelo-Puerta-ABIERTA-LATERAL-H") {
					//	std::cout << "entra" << std::endl;
					for (std::vector<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						if (N == (*T).ObjetosEscena.begin()) {

							txA = ((*N).position.x + (*T).position.x + (*I).position.x);
							tyA = ((*N).position.y + (*T).position.y + (*I).position.y);
							tzA = ((*N).position.z + (*T).position.z + (*I).position.z);

							rxA = ((*N).rotation.x + (*T).rotation.x + (*I).rotation.x);
							ryA = ((*N).rotation.y + (*T).rotation.y + (*I).rotation.y);
							rzA = ((*N).rotation.z + (*T).rotation.z + (*I).rotation.z);

							exA = ((*N).escala.x * (*T).escala.x * (*I).escala.x);
							eyA = ((*N).escala.y * (*T).escala.y * (*I).escala.y);
							ezA = ((*N).escala.z * (*T).escala.z * (*I).escala.z);

							aux = (*N).nombre;

						}

						else {

							tx = ((*N).position.x + (*T).position.x + (*I).position.x);
							ty = ((*N).position.y + (*T).position.y + (*I).position.y);
							tz = ((*N).position.z + (*T).position.z + (*I).position.z);

							rx = ((*N).rotation.x + (*T).rotation.x + (*I).rotation.x);
							ry = ((*N).rotation.y + (*T).rotation.y + (*I).rotation.y);
							rz = ((*N).rotation.z + (*T).rotation.z + (*I).rotation.z);

							ex = ((*N).escala.x * (*T).escala.x * (*I).escala.x);
							ey = ((*N).escala.y * (*T).escala.y * (*I).escala.y);
							ez = ((*N).escala.z * (*T).escala.z * (*I).escala.z);

							//Puerta(TGraphicEngine * motorApp, int ident, glm::vec3 posicion, glm::vec3 rotacion, glm::vec3 escala, std::string llave, std::string tipo,
							//std::string model, glm::vec3 posicion2, glm::vec3 rotacion2, glm::vec3 escala2, std::string modelB);

							Puerta * door = new Puerta(engine, num, glm::vec3(txA, tyA, -tzA),
								glm::vec3(rxA, ryA - 180, -rzA),
								glm::vec3(exA, eyA, ezA), "ABIERTA", "LATERAL", aux,
								glm::vec3(tx, ty, -tz),
								glm::vec3(rx, ry - 180, -rz),
								glm::vec3(ex, ey, ez),
								(*N).nombre);

							door->setFisica(mundo, num);
							door->setFisicas(mundo, num, glm::vec3(tx, ty, -tz),
								glm::vec3(rx, ry - 180, -rz),
								glm::vec3(ex, ey, ez));
							puertas.push_back(door);
							num++;
						}

					}

				}
			}
		}

		if ((*I).nombre == "COMISARIA") {

			for (std::vector<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {


				if ((*T).nombre == "Modelo") {

					tx = ((*T).position.x + (*I).position.x);
					ty = ((*T).position.y + (*I).position.y);
					tz = ((*T).position.z + (*I).position.z);

					rx = ((*T).rotation.x + (*I).rotation.x);
					ry = ((*T).rotation.y + (*I).rotation.y);
					rz = ((*T).rotation.z + (*I).rotation.z);

					ex = ((*T).escala.x * (*I).escala.x);
					ey = ((*T).escala.y * (*I).escala.y);
					ez = ((*T).escala.z * (*I).escala.z);

					std::cout << "ROTACIONES 1" << std::endl;
					std::cout << "X: " << rx << std::endl;
					std::cout << "Y: " << ry << std::endl;
					std::cout << "Z: " << rz << std::endl;
					std::cout << "///////////" << std::endl;
					std::cout << "trans 1" << std::endl;
					std::cout << "X: " << tx << std::endl;
					std::cout << "Y: " << ty << std::endl;
					std::cout << "Z: " << tz << std::endl;
					Pared * wall = new Pared(engine, glm::vec3(tx, ty, -tz),
						glm::vec3(rx, ry, -rz),
						glm::vec3(ex, ey, ez), "comisaria");

				}

				if ((*T).nombre == "Modelo-Puerta-ABIERTA-LATERAL-V") {
					//	std::cout << "entra" << std::endl;
					for (std::vector<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						if (N == (*T).ObjetosEscena.begin()) {

							txA = ((*N).position.x + (*T).position.x + (*I).position.x);
							tyA = ((*N).position.y + (*T).position.y + (*I).position.y);
							tzA = ((*N).position.z + (*T).position.z + (*I).position.z);

							rxA = ((*N).rotation.x + (*T).rotation.x + (*I).rotation.x);
							ryA = ((*N).rotation.y + (*T).rotation.y + (*I).rotation.y);
							rzA = ((*N).rotation.z + (*T).rotation.z + (*I).rotation.z);

							exA = ((*N).escala.x * (*T).escala.x * (*I).escala.x);
							eyA = ((*N).escala.y * (*T).escala.y * (*I).escala.y);
							ezA = ((*N).escala.z * (*T).escala.z * (*I).escala.z);

							aux = (*N).nombre;

						}

						else {

							tx = ((*N).position.x + (*T).position.x + (*I).position.x);
							ty = ((*N).position.y + (*T).position.y + (*I).position.y);
							tz = ((*N).position.z + (*T).position.z + (*I).position.z);

							rx = ((*N).rotation.x + (*T).rotation.x + (*I).rotation.x);
							ry = ((*N).rotation.y + (*T).rotation.y + (*I).rotation.y);
							rz = ((*N).rotation.z + (*T).rotation.z + (*I).rotation.z);

							ex = ((*N).escala.x * (*T).escala.x * (*I).escala.x);
							ey = ((*N).escala.y * (*T).escala.y * (*I).escala.y);
							ez = ((*N).escala.z * (*T).escala.z * (*I).escala.z);

							//Puerta(TGraphicEngine * motorApp, int ident, glm::vec3 posicion, glm::vec3 rotacion, glm::vec3 escala, std::string llave, std::string tipo,
							//std::string model, glm::vec3 posicion2, glm::vec3 rotacion2, glm::vec3 escala2, std::string modelB);

							Puerta * door = new Puerta(engine, num, glm::vec3(txA, tyA, -tzA),
								glm::vec3(rxA, ryA, -rzA),
								glm::vec3(exA, eyA, ezA), "ABIERTA", "LATERAL", aux,
								glm::vec3(tx, ty, -tz),
								glm::vec3(rx, ry, -rz),
								glm::vec3(ex, ey, ez),
								(*N).nombre);

							door->setFisica(mundo, num);
							door->setFisicas(mundo, num, glm::vec3(tx, ty, -tz),
								glm::vec3(rx, ry, -rz),
								glm::vec3(ex, ey, ez));
							puertas.push_back(door);
							num++;
						}

					}

				}

			}
		}

		if ((*I).nombre == "VESTUARIO") {
			for (std::vector<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {
				

				if ((*T).nombre == "Modelo") {

					tx = ((*T).position.x + (*I).position.x);
					ty = ((*T).position.y + (*I).position.y);
					tz = ((*T).position.z + (*I).position.z);

					rx = ((*T).rotation.x + (*I).rotation.x);
					ry = ((*T).rotation.y + (*I).rotation.y);
					rz = ((*T).rotation.z + (*I).rotation.z);

					ex = ((*T).escala.x * (*I).escala.x);
					ey = ((*T).escala.y * (*I).escala.y);
					ez = ((*T).escala.z * (*I).escala.z);

					std::cout << "ROTACIONES 1" << std::endl;
					std::cout << "X: " << rx << std::endl;
					std::cout << "Y: " << ry << std::endl;
					std::cout << "Z: " << rz << std::endl;
					std::cout << "///////////" << std::endl;
					std::cout << "trans 1" << std::endl;
					std::cout << "X: " << tx << std::endl;
					std::cout << "Y: " << ty << std::endl;
					std::cout << "Z: " << tz << std::endl;
					Pared * wall = new Pared(engine, glm::vec3(tx, ty, -tz),
						glm::vec3(rx, ry, rz),
						glm::vec3(ex, ey, ez), "vestuario");

				}

				if ((*T).nombre == "Modelo-Puerta-ABIERTA-LATERAL-H") {
					//	std::cout << "entra" << std::endl;
					for (std::vector<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						if (N == (*T).ObjetosEscena.begin()) {

							txA = ((*N).position.x + (*T).position.x + (*I).position.x);
							tyA = ((*N).position.y + (*T).position.y + (*I).position.y);
							tzA = ((*N).position.z + (*T).position.z + (*I).position.z);

							rxA = ((*N).rotation.x + (*T).rotation.x + (*I).rotation.x);
							ryA = ((*N).rotation.y + (*T).rotation.y + (*I).rotation.y);
							rzA = ((*N).rotation.z + (*T).rotation.z + (*I).rotation.z);

							exA = ((*N).escala.x * (*T).escala.x * (*I).escala.x);
							eyA = ((*N).escala.y * (*T).escala.y * (*I).escala.y);
							ezA = ((*N).escala.z * (*T).escala.z * (*I).escala.z);

							aux = (*N).nombre;

						}

						else {

							tx = ((*N).position.x + (*T).position.x + (*I).position.x);
							ty = ((*N).position.y + (*T).position.y + (*I).position.y);
							tz = ((*N).position.z + (*T).position.z + (*I).position.z);

							rx = ((*N).rotation.x + (*T).rotation.x + (*I).rotation.x);
							ry = ((*N).rotation.y + (*T).rotation.y + (*I).rotation.y);
							rz = ((*N).rotation.z + (*T).rotation.z + (*I).rotation.z);

							ex = ((*N).escala.x * (*T).escala.x * (*I).escala.x);
							ey = ((*N).escala.y * (*T).escala.y * (*I).escala.y);
							ez = ((*N).escala.z * (*T).escala.z * (*I).escala.z);

							//Puerta(TGraphicEngine * motorApp, int ident, glm::vec3 posicion, glm::vec3 rotacion, glm::vec3 escala, std::string llave, std::string tipo,
							//std::string model, glm::vec3 posicion2, glm::vec3 rotacion2, glm::vec3 escala2, std::string modelB);

							Puerta * door = new Puerta(engine, num, glm::vec3(txA, tyA, -tzA),
								glm::vec3(rxA, ryA - 180, -rzA),
								glm::vec3(exA, eyA, ezA), "ABIERTA", "LATERAL", aux,
								glm::vec3(tx, ty, -tz),
								glm::vec3(rx, ry - 180, -rz),
								glm::vec3(ex, ey, ez),
								(*N).nombre);

							door->setFisica(mundo, num);
							door->setFisicas(mundo, num, glm::vec3(tx, ty, -tz),
								glm::vec3(rx, ry - 180, -rz),
								glm::vec3(ex, ey, ez));
							puertas.push_back(door);
							num++;
						}

					}

				}

			}
		}

		if ((*I).nombre == "ARSENAL") {

			for (std::vector<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {


				if ((*T).nombre == "Modelo") {

					tx = ((*T).position.x + (*I).position.x);
					ty = ((*T).position.y + (*I).position.y);
					tz = ((*T).position.z + (*I).position.z);

					rx = ((*T).rotation.x + (*I).rotation.x);
					ry = ((*T).rotation.y + (*I).rotation.y);
					rz = ((*T).rotation.z + (*I).rotation.z);

					ex = ((*T).escala.x * (*I).escala.x);
					ey = ((*T).escala.y * (*I).escala.y);
					ez = ((*T).escala.z * (*I).escala.z);

					std::cout << "ROTACIONES 1" << std::endl;
					std::cout << "X: " << rx << std::endl;
					std::cout << "Y: " << ry << std::endl;
					std::cout << "Z: " << rz << std::endl;
					std::cout << "///////////" << std::endl;
					std::cout << "trans 1" << std::endl;
					std::cout << "X: " << tx << std::endl;
					std::cout << "Y: " << ty << std::endl;
					std::cout << "Z: " << tz << std::endl;
					Pared * wall = new Pared(engine, glm::vec3(tx, ty, -tz),
						glm::vec3(rx, ry, rz),
						glm::vec3(ex, ey, ez), "arsenal");

				}


				if ((*T).nombre == "Modelo-Puerta-ABIERTA-LATERAL-H") {
					//	std::cout << "entra" << std::endl;
					for (std::vector<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						if (N == (*T).ObjetosEscena.begin()) {

							txA = ((*N).position.x + (*T).position.x + (*I).position.x);
							tyA = ((*N).position.y + (*T).position.y + (*I).position.y);
							tzA = ((*N).position.z + (*T).position.z + (*I).position.z);

							rxA = ((*N).rotation.x + (*T).rotation.x + (*I).rotation.x);
							ryA = ((*N).rotation.y + (*T).rotation.y + (*I).rotation.y);
							rzA = ((*N).rotation.z + (*T).rotation.z + (*I).rotation.z);

							exA = ((*N).escala.x * (*T).escala.x * (*I).escala.x);
							eyA = ((*N).escala.y * (*T).escala.y * (*I).escala.y);
							ezA = ((*N).escala.z * (*T).escala.z * (*I).escala.z);

							aux = (*N).nombre;

						}

						else {

							tx = ((*N).position.x + (*T).position.x + (*I).position.x);
							ty = ((*N).position.y + (*T).position.y + (*I).position.y);
							tz = ((*N).position.z + (*T).position.z + (*I).position.z);

							rx = ((*N).rotation.x + (*T).rotation.x + (*I).rotation.x);
							ry = ((*N).rotation.y + (*T).rotation.y + (*I).rotation.y);
							rz = ((*N).rotation.z + (*T).rotation.z + (*I).rotation.z);

							ex = ((*N).escala.x * (*T).escala.x * (*I).escala.x);
							ey = ((*N).escala.y * (*T).escala.y * (*I).escala.y);
							ez = ((*N).escala.z * (*T).escala.z * (*I).escala.z);

							//Puerta(TGraphicEngine * motorApp, int ident, glm::vec3 posicion, glm::vec3 rotacion, glm::vec3 escala, std::string llave, std::string tipo,
							//std::string model, glm::vec3 posicion2, glm::vec3 rotacion2, glm::vec3 escala2, std::string modelB);

							Puerta * door = new Puerta(engine, num, glm::vec3(txA, tyA, -tzA),
								glm::vec3(rxA, ryA - 180, -rzA),
								glm::vec3(exA, eyA, ezA), "ABIERTA", "LATERAL", aux,
								glm::vec3(tx, ty, -tz),
								glm::vec3(rx, ry - 180, -rz),
								glm::vec3(ex, ey, ez),
								(*N).nombre);

							door->setFisica(mundo, num);
							door->setFisicas(mundo, num, glm::vec3(tx, ty, -tz),
								glm::vec3(rx, ry - 180, -rz),
								glm::vec3(ex, ey, ez));
							puertas.push_back(door);
							num++;
						}

					}

				}
			}
		}

		if ((*I).nombre == "PASILLO_1") {
			for (std::vector<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {
				

				if ((*T).nombre == "Modelo") {
					//	std::cout << "entra" << std::endl;

					tx = ((*T).position.x + (*I).position.x);
					ty = ((*T).position.y + (*I).position.y);
					tz = ((*T).position.z + (*I).position.z);

					rx = ((*T).rotation.x + (*I).rotation.x);
					ry = ((*T).rotation.y + (*I).rotation.y);
					rz = ((*T).rotation.z + (*I).rotation.z);

					ex = ((*T).escala.x * (*I).escala.x);
					ey = ((*T).escala.y * (*I).escala.y);
					ez = ((*T).escala.z * (*I).escala.z);

					std::cout << "ROTACIONES 1" << std::endl;
					std::cout << "X: " << rx << std::endl;
					std::cout << "Y: " << ry << std::endl;
					std::cout << "Z: " << rz << std::endl;
					std::cout << "///////////" << std::endl;
					std::cout << "trans 1" << std::endl;
					std::cout << "X: " << tx << std::endl;
					std::cout << "Y: " << ty << std::endl;
					std::cout << "Z: " << tz << std::endl;
					Pared * wall = new Pared(engine, glm::vec3(tx, ty, -tz),
						glm::vec3(rx, ry, rz),
						glm::vec3(ex, ey, ez), "pasillo_1");

				}

	
			}
		}

		if ((*I).nombre == "PASILLO_2") {

			for (std::vector<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {


				if ((*T).nombre == "Modelo") {

					tx = ((*T).position.x + (*I).position.x);
					ty = ((*T).position.y + (*I).position.y);
					tz = ((*T).position.z + (*I).position.z);

					rx = ((*T).rotation.x + (*I).rotation.x);
					ry = ((*T).rotation.y + (*I).rotation.y);
					rz = ((*T).rotation.z + (*I).rotation.z);

					ex = ((*T).escala.x * (*I).escala.x);
					ey = ((*T).escala.y * (*I).escala.y);
					ez = ((*T).escala.z * (*I).escala.z);

					std::cout << "ROTACIONES 1" << std::endl;
					std::cout << "X: " << rx << std::endl;
					std::cout << "Y: " << ry << std::endl;
					std::cout << "Z: " << rz << std::endl;
					std::cout << "///////////" << std::endl;
					std::cout << "trans 1" << std::endl;
					std::cout << "X: " << tx << std::endl;
					std::cout << "Y: " << ty << std::endl;
					std::cout << "Z: " << tz << std::endl;

					Pared * wall = new Pared(engine, glm::vec3(tx, ty, -tz),
						glm::vec3(rx, ry, rz),
						glm::vec3(ex, ey, ez), "pasillo_2");

				}

			}
		}

		if ((*I).nombre == "PASILLO_3") {
	
			

		for (std::vector<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {
			

			if ((*T).nombre == "Modelo") {

				tx = ((*T).position.x + (*I).position.x);
				ty = ((*T).position.y + (*I).position.y);
				tz = ((*T).position.z + (*I).position.z);

				rx = ((*T).rotation.x + (*I).rotation.x);
				ry = ((*T).rotation.y + (*I).rotation.y);
				rz = ((*T).rotation.z + (*I).rotation.z);

				ex = ((*T).escala.x * (*I).escala.x);
				ey = ((*T).escala.y * (*I).escala.y);
				ez = ((*T).escala.z * (*I).escala.z);

				std::cout << "ROTACIONES 1" << std::endl;
				std::cout << "X: " << rx << std::endl;
				std::cout << "Y: " << ry << std::endl;
				std::cout << "Z: " << rz << std::endl;
				std::cout << "///////////" << std::endl;
				std::cout << "trans 1" << std::endl;
				std::cout << "X: " << tx << std::endl;
				std::cout << "Y: " << ty << std::endl;
				std::cout << "Z: " << tz << std::endl;

				Pared * wall = new Pared(engine, glm::vec3(tx, ty, -tz),
					glm::vec3(rx, ry, rz),
					glm::vec3(ex, ey, ez), "pasillo_3");

			}


			}
		}

		if ((*I).nombre == "PASILLO_4") {

			for (std::vector<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {


				if ((*T).nombre == "Modelo") {

					tx = ((*T).position.x + (*I).position.x);
					ty = ((*T).position.y + (*I).position.y);
					tz = ((*T).position.z + (*I).position.z);

					rx = ((*T).rotation.x + (*I).rotation.x);
					ry = ((*T).rotation.y + (*I).rotation.y);
					rz = ((*T).rotation.z + (*I).rotation.z);

					ex = ((*T).escala.x * (*I).escala.x);
					ey = ((*T).escala.y * (*I).escala.y);
					ez = ((*T).escala.z * (*I).escala.z);

					std::cout << "ROTACIONES 1" << std::endl;
					std::cout << "X: " << rx << std::endl;
					std::cout << "Y: " << ry << std::endl;
					std::cout << "Z: " << rz << std::endl;
					std::cout << "///////////" << std::endl;
					std::cout << "trans 1" << std::endl;
					std::cout << "X: " << tx << std::endl;
					std::cout << "Y: " << ty << std::endl;
					std::cout << "Z: " << tz << std::endl;

					Pared * wall = new Pared(engine, glm::vec3(tx, ty, -tz),
						glm::vec3(rx, ry, rz),
						glm::vec3(ex, ey, ez), "pasillo_4");

				}
			}
		}

		if ((*I).nombre == "PASILLO_5") {

			for (std::vector<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {
				

	//		

	//	////		if ((*T).nombre == "Terminal") {
	//	////			for (std::list<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

	//	////				IMeshSceneNode *objeto = SM->addCubeSceneNode(10.0f, 0, -1,
	//	////					vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
	//	////					vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
	//	////					vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z));
	//	////				objeto->getMaterial(0).EmissiveColor.set(0, 96, 110, 174);

	//	////				Terminal *ter = new Terminal(vector3df(10 * ((*N).position.x + ((*T).position.x + (*I).position.x)), 10 * ((*N).position.y + ((*T).position.y + (*I).position.y)), 10 * ((*N).position.z + (*T).position.z + (*I).position.z)),
	//	////					vector3df((*N).rotation.x + (*T).rotation.x + (*I).rotation.x, (*N).rotation.y + (*T).rotation.y + (*I).rotation.y, (*N).rotation.z + (*T).rotation.z + (*I).rotation.z),
	//	////					vector3df(((*N).escala.x * (*T).escala.x * (*I).escala.x), (*N).escala.y * (*T).escala.y * (*I).escala.y, (*N).escala.z * (*T).escala.z * (*I).escala.z),
	//	////					mundo, objeto, this);

	//	////			}
	//	////		}

					if ((*T).nombre == "Modelo") {

						tx = ((*T).position.x + (*I).position.x);
						ty = ((*T).position.y + (*I).position.y);
						tz = ((*T).position.z + (*I).position.z);

						rx = ((*T).rotation.x + (*I).rotation.x);
						ry = ((*T).rotation.y + (*I).rotation.y);
						rz = ((*T).rotation.z + (*I).rotation.z);

						ex = ((*T).escala.x * (*I).escala.x);
						ey = ((*T).escala.y * (*I).escala.y);
						ez = ((*T).escala.z * (*I).escala.z);

						std::cout << "ROTACIONES 1" << std::endl;
						std::cout << "X: " << rx << std::endl;
						std::cout << "Y: " << ry << std::endl;
						std::cout << "Z: " << rz << std::endl;
						std::cout << "///////////" << std::endl;
						std::cout << "trans 1" << std::endl;
						std::cout << "X: " << tx << std::endl;
						std::cout << "Y: " << ty << std::endl;
						std::cout << "Z: " << tz << std::endl;

						Pared * wall = new Pared(engine, glm::vec3(tx, ty, -tz),
							glm::vec3(rx, ry, rz),
							glm::vec3(ex, ey, ez), "pasillo_5");

					}


			}
		}


		if ((*I).nombre == "ALMACEN_1") {

			for (std::vector<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {


				if ((*T).nombre == "Modelo") {

					tx = ((*T).position.x + (*I).position.x);
					ty = ((*T).position.y + (*I).position.y);
					tz = ((*T).position.z + (*I).position.z);

					rx = ((*T).rotation.x + (*I).rotation.x);
					ry = ((*T).rotation.y + (*I).rotation.y);
					rz = ((*T).rotation.z + (*I).rotation.z);

					ex = ((*T).escala.x * (*I).escala.x);
					ey = ((*T).escala.y * (*I).escala.y);
					ez = ((*T).escala.z * (*I).escala.z);

					std::cout << "ROTACIONES 1" << std::endl;
					std::cout << "X: " << rx << std::endl;
					std::cout << "Y: " << ry << std::endl;
					std::cout << "Z: " << rz << std::endl;
					std::cout << "///////////" << std::endl;
					std::cout << "trans 1" << std::endl;
					std::cout << "X: " << tx << std::endl;
					std::cout << "Y: " << ty << std::endl;
					std::cout << "Z: " << tz << std::endl;

					Pared * wall = new Pared(engine, glm::vec3(tx, ty, -tz),
						glm::vec3(rx, ry, rz),
						glm::vec3(ex, ey, ez), "almacen_1");

				}


				if ((*T).nombre == "Modelo-Puerta-ABIERTA-LATERAL-H") {
					//	std::cout << "entra" << std::endl;
					for (std::vector<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						if (N == (*T).ObjetosEscena.begin()) {

							txA = ((*N).position.x + (*T).position.x + (*I).position.x);
							tyA = ((*N).position.y + (*T).position.y + (*I).position.y);
							tzA = ((*N).position.z + (*T).position.z + (*I).position.z);

							rxA = ((*N).rotation.x + (*T).rotation.x + (*I).rotation.x);
							ryA = ((*N).rotation.y + (*T).rotation.y + (*I).rotation.y);
							rzA = ((*N).rotation.z + (*T).rotation.z + (*I).rotation.z);

							exA = ((*N).escala.x * (*T).escala.x * (*I).escala.x);
							eyA = ((*N).escala.y * (*T).escala.y * (*I).escala.y);
							ezA = ((*N).escala.z * (*T).escala.z * (*I).escala.z);

							aux = (*N).nombre;

						}

						else {

							tx = ((*N).position.x + (*T).position.x + (*I).position.x);
							ty = ((*N).position.y + (*T).position.y + (*I).position.y);
							tz = ((*N).position.z + (*T).position.z + (*I).position.z);

							rx = ((*N).rotation.x + (*T).rotation.x + (*I).rotation.x);
							ry = ((*N).rotation.y + (*T).rotation.y + (*I).rotation.y);
							rz = ((*N).rotation.z + (*T).rotation.z + (*I).rotation.z);

							ex = ((*N).escala.x * (*T).escala.x * (*I).escala.x);
							ey = ((*N).escala.y * (*T).escala.y * (*I).escala.y);
							ez = ((*N).escala.z * (*T).escala.z * (*I).escala.z);

							//Puerta(TGraphicEngine * motorApp, int ident, glm::vec3 posicion, glm::vec3 rotacion, glm::vec3 escala, std::string llave, std::string tipo,
							//std::string model, glm::vec3 posicion2, glm::vec3 rotacion2, glm::vec3 escala2, std::string modelB);

							Puerta * door = new Puerta(engine, num, glm::vec3(txA, tyA, -tzA),
								glm::vec3(rxA, ryA - 180, -rzA),
								glm::vec3(exA, eyA, ezA), "ABIERTA", "LATERAL", aux,
								glm::vec3(tx, ty, -tz),
								glm::vec3(rx, ry - 180, -rz),
								glm::vec3(ex, ey, ez),
								(*N).nombre);

							door->setFisica(mundo, num);
							door->setFisicas(mundo, num, glm::vec3(tx, ty, -tz),
								glm::vec3(rx, ry - 180, -rz),
								glm::vec3(ex, ey, ez));
							puertas.push_back(door);
							num++;
						}

					}

				}

			}
		}

		if ((*I).nombre == "ALMACEN_2") {

			for (std::vector<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {


				if ((*T).nombre == "Modelo") {

					tx = ((*T).position.x + (*I).position.x);
					ty = ((*T).position.y + (*I).position.y);
					tz = ((*T).position.z + (*I).position.z);

					rx = ((*T).rotation.x + (*I).rotation.x);
					ry = ((*T).rotation.y + (*I).rotation.y);
					rz = ((*T).rotation.z + (*I).rotation.z);

					ex = ((*T).escala.x * (*I).escala.x);
					ey = ((*T).escala.y * (*I).escala.y);
					ez = ((*T).escala.z * (*I).escala.z);

					std::cout << "ROTACIONES 1" << std::endl;
					std::cout << "X: " << rx << std::endl;
					std::cout << "Y: " << ry << std::endl;
					std::cout << "Z: " << rz << std::endl;
					std::cout << "///////////" << std::endl;
					std::cout << "trans 1" << std::endl;
					std::cout << "X: " << tx << std::endl;
					std::cout << "Y: " << ty << std::endl;
					std::cout << "Z: " << tz << std::endl;

					Pared * wall = new Pared(engine, glm::vec3(tx, ty, -tz),
						glm::vec3(rx, ry, -rz),
						glm::vec3(ex, ey, ez), "almacen_2");

				}

				if ((*T).nombre == "Modelo-Puerta-ABIERTA-LATERAL-H") {
					//	std::cout << "entra" << std::endl;
					for (std::vector<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						if (N == (*T).ObjetosEscena.begin()) {

							txA = ((*N).position.x + (*T).position.x + (*I).position.x);
							tyA = ((*N).position.y + (*T).position.y + (*I).position.y);
							tzA = ((*N).position.z + (*T).position.z + (*I).position.z);

							rxA = ((*N).rotation.x + (*T).rotation.x + (*I).rotation.x);
							ryA = ((*N).rotation.y + (*T).rotation.y + (*I).rotation.y);
							rzA = ((*N).rotation.z + (*T).rotation.z + (*I).rotation.z);

							exA = ((*N).escala.x * (*T).escala.x * (*I).escala.x);
							eyA = ((*N).escala.y * (*T).escala.y * (*I).escala.y);
							ezA = ((*N).escala.z * (*T).escala.z * (*I).escala.z);

							aux = (*N).nombre;

						}

						else {

							tx = ((*N).position.x + (*T).position.x + (*I).position.x);
							ty = ((*N).position.y + (*T).position.y + (*I).position.y);
							tz = ((*N).position.z + (*T).position.z + (*I).position.z);

							rx = ((*N).rotation.x + (*T).rotation.x + (*I).rotation.x);
							ry = ((*N).rotation.y + (*T).rotation.y + (*I).rotation.y);
							rz = ((*N).rotation.z + (*T).rotation.z + (*I).rotation.z);

							ex = ((*N).escala.x * (*T).escala.x * (*I).escala.x);
							ey = ((*N).escala.y * (*T).escala.y * (*I).escala.y);
							ez = ((*N).escala.z * (*T).escala.z * (*I).escala.z);

							//Puerta(TGraphicEngine * motorApp, int ident, glm::vec3 posicion, glm::vec3 rotacion, glm::vec3 escala, std::string llave, std::string tipo,
							//std::string model, glm::vec3 posicion2, glm::vec3 rotacion2, glm::vec3 escala2, std::string modelB);

							Puerta * door = new Puerta(engine, num, glm::vec3(txA, tyA, -tzA),
								glm::vec3(rxA, ryA - 180, -rzA),
								glm::vec3(exA, eyA, ezA), "ABIERTA", "LATERAL", aux,
								glm::vec3(tx, ty, -tz),
								glm::vec3(rx, ry - 180, -rz),
								glm::vec3(ex, ey, ez),
								(*N).nombre);

							door->setFisica(mundo, num);
							door->setFisicas(mundo, num, glm::vec3(tx, ty, -tz),
								glm::vec3(rx, ry - 180, -rz),
								glm::vec3(ex, ey, ez));
							puertas.push_back(door);
							num++;
						}

					}

				}


			}
		}

		if ((*I).nombre == "ALMACEN_3") {

			

			for (std::vector<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {


				if ((*T).nombre == "Modelo") {

					tx = ((*T).position.x + (*I).position.x);
					ty = ((*T).position.y + (*I).position.y);
					tz = ((*T).position.z + (*I).position.z);

					rx = ((*T).rotation.x + (*I).rotation.x);
					ry = ((*T).rotation.y + (*I).rotation.y);
					rz = ((*T).rotation.z + (*I).rotation.z);

					ex = ((*T).escala.x * (*I).escala.x);
					ey = ((*T).escala.y * (*I).escala.y);
					ez = ((*T).escala.z * (*I).escala.z);

					std::cout << "ROTACIONES 1" << std::endl;
					std::cout << "X: " << rx << std::endl;
					std::cout << "Y: " << ry << std::endl;
					std::cout << "Z: " << rz << std::endl;
					std::cout << "///////////" << std::endl;
					std::cout << "trans 1" << std::endl;
					std::cout << "X: " << tx << std::endl;
					std::cout << "Y: " << ty << std::endl;
					std::cout << "Z: " << tz << std::endl;

					Pared * wall = new Pared(engine, glm::vec3(tx, ty, -tz),
						glm::vec3(rx, ry, rz),
						glm::vec3(ex, ey, ez), "almacen_3");

				}


				if ((*T).nombre == "Modelo-Puerta-ABIERTA-LATERAL-V") {
					//	std::cout << "entra" << std::endl;
					for (std::vector<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						if (N == (*T).ObjetosEscena.begin()) {

							txA = ((*N).position.x + (*T).position.x + (*I).position.x);
							tyA = ((*N).position.y + (*T).position.y + (*I).position.y);
							tzA = ((*N).position.z + (*T).position.z + (*I).position.z);

							rxA = ((*N).rotation.x + (*T).rotation.x + (*I).rotation.x);
							ryA = ((*N).rotation.y + (*T).rotation.y + (*I).rotation.y);
							rzA = ((*N).rotation.z + (*T).rotation.z + (*I).rotation.z);

							exA = ((*N).escala.x * (*T).escala.x * (*I).escala.x);
							eyA = ((*N).escala.y * (*T).escala.y * (*I).escala.y);
							ezA = ((*N).escala.z * (*T).escala.z * (*I).escala.z);

							aux = (*N).nombre;

						}

						else {

							tx = ((*N).position.x + (*T).position.x + (*I).position.x);
							ty = ((*N).position.y + (*T).position.y + (*I).position.y);
							tz = ((*N).position.z + (*T).position.z + (*I).position.z);

							rx = ((*N).rotation.x + (*T).rotation.x + (*I).rotation.x);
							ry = ((*N).rotation.y + (*T).rotation.y + (*I).rotation.y);
							rz = ((*N).rotation.z + (*T).rotation.z + (*I).rotation.z);

							ex = ((*N).escala.x * (*T).escala.x * (*I).escala.x);
							ey = ((*N).escala.y * (*T).escala.y * (*I).escala.y);
							ez = ((*N).escala.z * (*T).escala.z * (*I).escala.z);

							//Puerta(TGraphicEngine * motorApp, int ident, glm::vec3 posicion, glm::vec3 rotacion, glm::vec3 escala, std::string llave, std::string tipo,
							//std::string model, glm::vec3 posicion2, glm::vec3 rotacion2, glm::vec3 escala2, std::string modelB);

							Puerta * door = new Puerta(engine, num, glm::vec3(txA, tyA, -tzA),
								glm::vec3(rxA, ryA, -rzA),
								glm::vec3(exA, eyA, ezA), "ABIERTA", "LATERAL", aux,
								glm::vec3(tx, ty, -tz),
								glm::vec3(rx, ry, -rz),
								glm::vec3(ex, ey, ez),
								(*N).nombre);

							door->setFisica(mundo, num);
							door->setFisicas(mundo, num, glm::vec3(tx, ty, -tz),
								glm::vec3(rx, ry, -rz),
								glm::vec3(ex, ey, ez));
							puertas.push_back(door);
							num++;
						}

					}

				}

			}
		}

		if ((*I).nombre == "ALMACEN_4") {

			for (std::vector<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {

				if ((*T).nombre == "Paredes") {
					for (std::vector<Elemento>::iterator N = (*T).ObjetosEscena.begin(); N != (*T).ObjetosEscena.end(); N++) {

						tx = ((*N).position.x + (*T).position.x + (*I).position.x);
						ty = ((*N).position.y + (*T).position.y + (*I).position.y);
						tz = ((*N).position.z + (*T).position.z + (*I).position.z);

						rx = ((*N).rotation.x + (*T).rotation.x + (*I).rotation.x);
						ry = ((*N).rotation.y + (*T).rotation.y + (*I).rotation.y);
						rz = ((*N).rotation.z + (*T).rotation.z + (*I).rotation.z);

						ex = ((*N).escala.x * (*T).escala.x * (*I).escala.x);
						ey = ((*N).escala.y * (*T).escala.y * (*I).escala.y);
						ez = ((*N).escala.z * (*T).escala.z * (*I).escala.z);

						Pared * wall = new Pared(engine, glm::vec3(tx, 0, -tz),
							glm::vec3(rx, ry, rz),
							glm::vec3(ex, ey, ez), "");
						wall->setFisicas(mundo);



						Listparedes.push_back(wall);

					}
				}

				if ((*T).nombre == "Modelo") {

					tx = ((*T).position.x + (*I).position.x);
					ty = ((*T).position.y + (*I).position.y);
					tz = ((*T).position.z + (*I).position.z);

					rx = ((*T).rotation.x + (*I).rotation.x);
					ry = ((*T).rotation.y + (*I).rotation.y);
					rz = ((*T).rotation.z + (*I).rotation.z);

					ex = ((*T).escala.x * (*I).escala.x);
					ey = ((*T).escala.y * (*I).escala.y);
					ez = ((*T).escala.z * (*I).escala.z);

					std::cout << "ROTACIONES 1" << std::endl;
					std::cout << "X: " << rx << std::endl;
					std::cout << "Y: " << ry << std::endl;
					std::cout << "Z: " << rz << std::endl;
					std::cout << "///////////" << std::endl;
					std::cout << "trans 1" << std::endl;
					std::cout << "X: " << tx << std::endl;
					std::cout << "Y: " << ty << std::endl;
					std::cout << "Z: " << tz << std::endl;

					Pared * wall = new Pared(engine, glm::vec3(tx, ty, -tz),
						glm::vec3(rx, ry, rz),
						glm::vec3(ex, ey, ez), "almacen_4");

				}

			}
		}

		if ((*I).nombre == "WAYPOINTS_ZONA1") {
			for (std::vector<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {

				tx = ((*T).position.x + (*I).position.x);
				ty = ((*T).position.y + (*I).position.y);
				tz = ((*T).position.z + (*I).position.z);

				//TNodo * caja = engine->addMalla();
				//engine->trasladar(caja, tx, ty, -tz);


				zona1->creaPuntos((*T).nombre, glm::vec3(tx, ty, tz));
				//puntos->MuestraPuntos();
				//puntos->creaPesos();
				//puntos->mostrarPesos();
			}
		}

		if ((*I).nombre == "WAYPOINTS_ZONA2") {
			for (std::vector<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {
				

				tx = ((*T).position.x + (*I).position.x);
				ty = ((*T).position.y + (*I).position.y);
				tz = ((*T).position.z + (*I).position.z);

				//TNodo * caja = engine->addMalla();
				//engine->trasladar(caja, tx, ty, -tz);


				zona2->creaPuntos((*T).nombre, glm::vec3(tx, ty, tz));
				//puntos->MuestraPuntos();
				//puntos->creaPesos();
				//puntos->mostrarPesos();
			}
		}
		if ((*I).nombre == "WAYPOINTS_ZONA3") {
		//	
			for (std::vector<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {


				tx = ((*T).position.x + (*I).position.x);
				ty = ((*T).position.y + (*I).position.y);
				tz = ((*T).position.z + (*I).position.z);

				//TNodo * caja = engine->addMalla();
				//engine->trasladar(caja, tx, ty, -tz);


				zona3->creaPuntos((*T).nombre, glm::vec3(tx, ty, tz));
				//puntos->MuestraPuntos();
				//puntos->creaPesos();
				//puntos->mostrarPesos();
			}
		}

		if ((*I).nombre == "WAYPOINTS_ZONA4") {
			for (std::vector<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {


				tx = ((*T).position.x + (*I).position.x);
				ty = ((*T).position.y + (*I).position.y);
				tz = ((*T).position.z + (*I).position.z);

				//TNodo * caja = engine->addMalla();
				//engine->trasladar(caja, tx, ty, -tz);


				zona4->creaPuntos((*T).nombre, glm::vec3(tx, ty, tz));
				//puntos->MuestraPuntos();
				//puntos->creaPesos();
				//puntos->mostrarPesos();
			}
		}

		if ((*I).nombre == "TAM") {
			tam = (*I).escala.x* (*I).escala.z;
		}
		//
		////0: botiquin
		////1: llave
		////2: municion de pistola
		////3:   " " de subfusil
		////4:   " " de escopeta

		if((*I).nombre == "BOTIQUINES") {
			for (std::vector<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {

				tx = ((*T).position.x + (*I).position.x);
				ty = ((*T).position.y + (*I).position.y);
				tz = ((*T).position.z + (*I).position.z);

				rx = ((*T).rotation.x + (*I).rotation.x);
				ry = ((*T).rotation.y + (*I).rotation.y);
				rz = ((*T).rotation.z + (*I).rotation.z);

				ex = ((*T).escala.x * (*I).escala.x);
				ey = ((*T).escala.y * (*I).escala.y);
				ez = ((*T).escala.z * (*I).escala.z);



				//engine, mundo
				Botiquines *bot = new Botiquines(glm::vec3(tx, ty, -tz),
					glm::vec3(rx, ry, rz),
					glm::vec3(ex, ey, ez), 0, engine);
				bot->setFisica(mundo);
				objConsumables.push_back(bot);
			}
		}
		if ((*I).nombre == "MUNICION_PISTOLA") {
			for (std::vector<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {

				tx = ((*T).position.x + (*I).position.x);
				ty = ((*T).position.y + (*I).position.y);
				tz = ((*T).position.z + (*I).position.z);

				rx = ((*T).rotation.x + (*I).rotation.x);
				ry = ((*T).rotation.y + (*I).rotation.y);
				rz = ((*T).rotation.z + (*I).rotation.z);

				ex = ((*T).escala.x * (*I).escala.x);
				ey = ((*T).escala.y * (*I).escala.y);
				ez = ((*T).escala.z * (*I).escala.z);

				MunicionPistola *pistola = new MunicionPistola(glm::vec3(tx, ty, -tz),
					glm::vec3(rx, ry, rz),
					glm::vec3(ex, ey, ez), 2, 2, 7, engine);
				pistola->setFisica(mundo);
				objConsumables.push_back(pistola);
			}
		}
		
		if ((*I).nombre == "MUNICION_ESCOPETA") {
			for (std::vector<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {

				tx = ((*T).position.x + (*I).position.x);
				ty = ((*T).position.y + (*I).position.y);
				tz = ((*T).position.z + (*I).position.z);

				rx = ((*T).rotation.x + (*I).rotation.x);
				ry = ((*T).rotation.y + (*I).rotation.y);
				rz = ((*T).rotation.z + (*I).rotation.z);

				ex = ((*T).escala.x * (*I).escala.x);
				ey = ((*T).escala.y * (*I).escala.y);
				ez = ((*T).escala.z * (*I).escala.z);

				MunicionEscopeta *escopeta = new MunicionEscopeta(glm::vec3(tx, ty, -tz),
					glm::vec3(rx, ry, rz),
					glm::vec3(ex, ey, ez), 4, 4, 2, engine);
				escopeta->setFisica(mundo);
				objConsumables.push_back(escopeta);
			}
		}
		if ((*I).nombre == "LLAVES") {
			for (std::vector<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {

				tx = ((*T).position.x + (*I).position.x);
				ty = ((*T).position.y + (*I).position.y);
				tz = ((*T).position.z + (*I).position.z);

				rx = ((*T).rotation.x + (*I).rotation.x);
				ry = ((*T).rotation.y + (*I).rotation.y);
				rz = ((*T).rotation.z + (*I).rotation.z);

				ex = ((*T).escala.x * (*I).escala.x);
				ey = ((*T).escala.y * (*I).escala.y);
				ez = ((*T).escala.z * (*I).escala.z);

				Llave *llave = new Llave(glm::vec3(tx, ty, -tz),
					glm::vec3(rx, ry, rz),
					glm::vec3(ex, ey, ez), 1, (*T).nombre, engine);
				llave->setFisica(mundo);
				objConsumables.push_back(llave);
			}
		}
	}


	for (std::size_t i = 0; i < listaDeCamaras.size(); i++) {
		if (listaDeCamaras[i]->getId() != 0) {

			listaDeCamaras[i]->getTCamara()->desactivar();

		}
		else {
			listaDeCamaras[i]->getTCamara()->activar();

		}

	}

	//for (std::size_t i = 0; i < ListLuces.size(); i++) {
	//	if (ListLuces[i]->getID() == 0) {
	//		ListLuces[i]->activar();
	//	}
	//}

	cambioDeLuces(0);

	jugador->asignarVectorDirector(glm::vec3(-1,0,0), buscarCamara(0)->getAnguloInicial());

	std::cout << "-------------------------------------->" << tam << std::endl;

	waypoints.push_back(zona1); waypoints.push_back(zona2); waypoints.push_back(zona3); waypoints.push_back(zona4);

	inicializarWaypoints();
	fabricaDeEnemigos();
	//destroyWaypoints();
}

void Escenario::fabricaDeEnemigos() {

	float tx, ty, tz;

	for (std::vector<ElementoPadre>::iterator I = Padres.begin(); I != Padres.end(); I++) {

		if ((*I).nombre == "CRIAS_ALIENS") {

			for (std::vector<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {

				tx = ((*T).position.x + (*I).position.x);
				ty = ((*T).position.y + (*I).position.y);
				tz = ((*T).position.z + (*I).position.z);


				if ((*T).nombre == "zona1") {

					//CriaAlien::CriaAlien(TGraphicEngine *motor, Mundo* mundo, glm::vec3 posicion, Escenario* esce, Waypoints* puntos)

					CriaAlien *ene = new CriaAlien(engine, mundo,
						glm::vec3(tx, ty, -tz), 
						this, waypoints.at(0));

					enemigos.push_back(ene);
				}

				else if ((*T).nombre == "zona2") {

					CriaAlien *ene = new CriaAlien(engine, mundo,
						glm::vec3(tx, ty, -tz),
						this, waypoints.at(1));

					enemigos.push_back(ene);
				}

				else if ((*T).nombre == "zona3") {

					CriaAlien *ene = new CriaAlien(engine, mundo,
						glm::vec3(tx, ty, -tz),
						this, waypoints.at(2));

					enemigos.push_back(ene);
				}

				else if ((*T).nombre == "zona4") {

					CriaAlien *ene = new CriaAlien(engine, mundo,
						glm::vec3(tx, ty, -tz),
						this, waypoints.at(3));

					enemigos.push_back(ene);
				}
			}

		}

		else if ((*I).nombre == "ALIEN_BERSERKER") {

			

			for (std::vector<ElementoHijo>::iterator T = (*I).ObjetosEscena.begin(); T != (*I).ObjetosEscena.end(); T++) {


				tx = ((*T).position.x + (*I).position.x);
				ty = ((*T).position.y + (*I).position.y);
				tz = ((*T).position.z + (*I).position.z);


				if ((*T).nombre == "zona1") {

					AlienBerserker *ene = new AlienBerserker(engine, mundo,
						glm::vec3(tx, ty, -tz),
						this, waypoints.at(0));

					enemigos.push_back(ene);
				}

				else if ((*T).nombre == "zona2") {

					AlienBerserker *ene = new AlienBerserker(engine, mundo,
						glm::vec3(tx, ty, -tz),
						this, waypoints.at(1));

					enemigos.push_back(ene);
				}

				else if ((*T).nombre == "zona3") {

					AlienBerserker *ene = new AlienBerserker(engine, mundo,
						glm::vec3(tx, ty, -tz),
						this, waypoints.at(2));

					enemigos.push_back(ene);
				}

				else if ((*T).nombre == "zona4") {

					AlienBerserker *ene = new AlienBerserker(engine, mundo,
						glm::vec3(tx, ty, -tz),
						this, waypoints.at(3));

					enemigos.push_back(ene);

				}
			}

		}

	}

}

void Escenario::destroyWaypoints() {

	/*if (!waypoints.empty()) {
		for (std::vector<Waypoints*>::iterator it = waypoints.begin(); it != waypoints.end();) {
			if ((*it) != NULL) {

				delete(*it);
				it = waypoints.erase(it);

			}
			else
				it++;
		}

	}*/
}


void Escenario::actualizarEstadoPersonaje()
{
	////cambiar el NULL por nullptr
	//if (pers!=nullptr)
	//{
	//	if (pers->getVivo() == false)
	//	{		
	//		delete(pers);
	//		pers = nullptr;
	//	}
	//}
	//
}


void Escenario::destroyPared() {

	/*if (!paredes.empty()) {
		for (std::list<Pared*>::iterator it = paredes.begin(); it != paredes.end();) {
			if ((*it) != NULL) {
				
					delete(*it);
					it = paredes.erase(it);
				
			}
			else
				it++;
		}

	}*/
}

void Escenario::actualizarEstadoPuerta()
{
	if (!puertas.empty())
	{
		for (std::vector<Puerta*>::iterator it = puertas.begin(); it != puertas.end(); it++) {
			if ((*it) != NULL ) {
			
					(*it)->Update();
				
			}
		
		}

	}
}

Camara * Escenario::getCamara()
{
	Camara * cam=nullptr;
	if (!listaDeCamaras.empty())
	{
		for (std::size_t i = 0; i < listaDeCamaras.size(); i++) {
			if (listaDeCamaras[i] != NULL && listaDeCamaras[i]->getTCamara()->getActiva() == true) {

				cam = listaDeCamaras[i];
			}

		}

	}

	return cam;
}

void Escenario::actualizarCamaras() {

	if (!listaDeCamaras.empty())
	{
		for (std::size_t i = 0; i < listaDeCamaras.size(); i++) {
			if (listaDeCamaras[i] != NULL && listaDeCamaras[i]->getTCamara()->getActiva() == true) {

				//listaDeCamaras[i]->updateCam(engine, engine->getPosicion(listaDeCamaras[i]->getNodo()), engine->getPosicion(jugador->getNodo()) ); //pasar la creacion del personaje aqui, ver que eye tiene que tener y pasar el engine

			}

		}

	}
}


void Escenario::actualizarObjetosConsumables()
{

	if (!objConsumables.empty()) {
		for (std::vector<Objetos*>::iterator it = objConsumables.begin(); it != objConsumables.end();) {
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
		//waypoints[i]->mostrarPesos();
		//waypoints[i]->MostrarAdyacencia();
	}

}

void Escenario::actualizarListaEnemigos(float dt) {

	if (!enemigos.empty()) {
		for (std::vector<Enemigo*>::iterator it = enemigos.begin(); it != enemigos.end();) {
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

		for (std::vector<Enemigo*>::iterator it = enemigos.begin(); it != enemigos.end(); it++) {
			if ((*it) != NULL && (*it)->estaVivo() == true) {

				//estados que usan / necesitan de la logica difusa
				if((*it)->getEstado() == 3 || (*it)->getEstado() == 6 || (*it)->getEstado() == 7) {
					(*it)->setPosJugador(jugador->getPos().x, jugador->getPos().z);
				}

				(*it)->Update(dt);

			}
		}
	}
}



void Escenario::cambiaEstado(std::string mensaje)
{
	/* jue->cambioEstado(mensaje);*/
}

player* Escenario::getPersonaje()
{
	return jugador;
}

void Escenario::eleminarEnemigos()
{
	/*if (!enemigos.empty()) {
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
	}*/
}

void Escenario::cambioDeLuces(int ID) {

	//ListLuces
	//luces del ID que no se tienen que activar 


	for (std::size_t i = 0; i < ListLuces.size(); i++) {
		//ListLuces[i]->desactivar();
	std::cout << "ID: " << ListLuces[i]->getID() << " IDpara: " << i<<" "<< ID << std::endl;
		if (ListLuces[i]->getID() == ID) {
			engine->resetTransform(luzActual->getNodo(),'t');
			engine->trasladar(luzActual->getNodo(), ListLuces[i]->getPos().x, ListLuces[i]->getPos().y, ListLuces[i]->getPos().z);
		}
	}

	
	

	//if (ID == 12 || ID == 18 || ID == 9)
	//{
	//	for (std::size_t i = 0; i < ListLuces.size(); i++) {
	//		if (ListLuces[i]->getID() == 0) {
	//			ListLuces[i]->activar();
	//		}
	//	}
	//}


}