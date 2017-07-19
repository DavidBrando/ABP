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

class AlienBerserker : public Enemigo {

public:
	AlienBerserker(ISceneManager* smgr, IVideoDriver* driver, b2World *world, vector3df posicion, Waypoints* puntos);
	// AlienBerserker(const AlienBerserker& orig);
	virtual ~AlienBerserker();
	void Update(f32 dt);
	void Patrullar();
	void Atacar(f32 dt);
	void CQC();
	void BuscarWaypoint();
	void quitarVida(float damage);
	void recuperarResistencia();


private:

};

#endif /* ALIENBERSERKER_H */

