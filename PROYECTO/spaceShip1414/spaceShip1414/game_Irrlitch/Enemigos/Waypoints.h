#pragma once
/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   Waypoints.h
* Author: Hector
*
* Created on 24 de enero de 2017, 18:00
*/

#ifndef WAYPOINTS_H
#define WAYPOINTS_H


#include <irrlicht.h>
#include <iostream>
#include <string>
#include <vector>


class Entity2D;
class Nodo;

using namespace irr;
using namespace core;

class Waypoints {

private:

	std::vector<Nodo*> puntos;
	float **pesos;
	int tamDelMapa;


public:
	Waypoints();
	Waypoints(const Waypoints& orig);
	virtual ~Waypoints();

	void MuestraPuntos();
	void creaPuntos(std::string nombre, vector3df posicion);
	void creaPesos(Entity2D * entity);
	void crearMatriz();
	void mostrarPesos();
	void setTamDelMapa(int tam);
	float** getMatriz();
	float getPeso(const int i, const int j);
	std::vector<Nodo*> getNodos();
	Nodo* getNodoX(int x);
	int getTamMapa();



};

#endif /* WAYPOINTS_H */

