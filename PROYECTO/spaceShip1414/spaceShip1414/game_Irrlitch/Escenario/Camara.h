#pragma once
/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   Camara.h
* Author: User
*
* Created on 21 de noviembre de 2016, 17:37
*/
#include <irrlicht.h>
#ifndef CAMARA_H
#define CAMARA_H

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Camara {

private:

	vector3df posicion;
	vector3df foco;
	float vel;
	int cont;
	ICameraSceneNode* camara;


public:
	Camara(ISceneManager* smgr, vector3df posPers);
	Camara(const Camara& orig);
	virtual ~Camara();
	void actualizarCamara(vector3df posPers, vector3df rotPers, f32 dt);
	vector3df getPos();
	vector3df getFoco();
	void setPos(vector3df pos);
	void setFoco(vector3df f);

};
#endif /* CAMARA_H */

