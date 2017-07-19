#pragma once
/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   AlienBerserker.h
* Author: David
*
* Created on 18 de enero de 2017, 16:50
*/

#ifndef ALIENBERSERKER_H
#define ALIENBERSERKER_H



#include "Enemigo.h"

class navmeshes;
class Escenario;
class BehaivorTree;


class AlienBerserker : public Enemigo {

public:

	AlienBerserker(TGraphicEngine*, Mundo*, glm::vec3 posicion, Escenario* esce, Waypoints* puntos);
	//AlienBerserker(const CriaAlien& orig);
	virtual ~AlienBerserker();
	void crearArbol();
	void Update(float dt);
	void CQC();
	void empezarFlocking(float dt);
	void Patrullar();
	void Atacar(float dt);
	void BuscarWaypoint();
	void quitarVida(float damage);
	void recuperarResistencia();
	//void dibujaGrid(ISceneManager *grid);
	void setLider(bool c);


private:

	navmeshes* nav;
	BehaivorTree *tree;

};

#endif /* ALIENBERSERKER_H */

