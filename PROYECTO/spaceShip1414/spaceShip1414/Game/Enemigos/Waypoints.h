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


#include <iostream>
#include <string>
#include <vector>
#include <glm/vec3.hpp>

class Entity2D;
class Nodo;


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
	void MostrarAdyacencia();
	void creaPuntos(std::string nombre, glm::vec3 posicion);
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

