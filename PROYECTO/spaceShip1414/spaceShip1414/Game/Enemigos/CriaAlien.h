
/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   CriaAlien.h
* Author: Hector
*
* Created on 16 de enero de 2017, 18:00
*/

#ifndef CRIAALIEN_H
#define CRIAALIEN_H

#include "Enemigo.h"

class navmeshes;
class Escenario;
class BehaivorTree;
class TNodo;
class TGraphicEngine;

class CriaAlien : public Enemigo {
public:

	CriaAlien(TGraphicEngine*, Mundo*, glm::vec3 posicion, Escenario* esce, Waypoints* puntos);
	//CriaAlien(const CriaAlien& orig);
	virtual ~CriaAlien();
	void crearArbol();
	void Update(float dt);
	void CQC();
	void emepzarFlocking(float dt);
	void Patrullar();
	void Atacar(float dt);
	void BuscarWaypoint();
	void quitarVida(float damage);
	void recuperarResistencia();
	//void dibujaGrid(ISceneManager *grid);
	void setLider(bool c);
	void load_cria();

	
private:

	navmeshes* nav;
	BehaivorTree *tree;
	TNodo *godfather, *Nreposo, *Naranar, *Nandar;
	TGraphicEngine * engine;
};

#endif /* CRIAALIEN_H */

