/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   Camara.cpp
* Author: User
*
* Created on 21 de noviembre de 2016, 17:37
*/


#include "../Jugador/Personaje.h"
#include "Camara.h"

//cuando esten las fisicas hay que hacer una camara con resorte para que sea fluido el movimiento
Camara::Camara(ISceneManager* smgr, vector3df posPers) {


	smgr->addCameraSceneNode(0, vector3df(0, 90, -60), posPers);

	camara = smgr->getActiveCamera();
	posicion = camara->getPosition();
	foco = camara->getTarget();
	cont = 0;
	vel = 100.0f;
	//     std::cout<<"CREO"<<std::endl;
	//    std::cout<<"X: "<<posicion.X<<" Y: "<<posicion.Y<<" Z: "<<posicion.Z<<std::endl;
}

Camara::Camara(const Camara& orig) {
}

Camara::~Camara() {
}

void Camara::actualizarCamara(vector3df posPers, vector3df rotPers, f32 dt) {

	//     std::cout<<"//////////////////////////////////////////"<<std::endl;
	//            std::cout<<""<<std::endl;
	//    std::cout<<"ANTES"<<std::endl;
	//    std::cout<<"X: "<<posicion.X<<" Y: "<<posicion.Y<<" Z: "<<posicion.Z<<std::endl;

	vector3df vecRel = posicion - posPers;
	//      std::cout<<"//////////////////////////////////////////"<<std::endl;
	//            std::cout<<""<<std::endl;
	//     std::cout<<"vecRel"<<std::endl;
	//    std::cout<<"X: "<<vecRel.X<<" Y: "<<vecRel.Y<<" Z: "<<vecRel.Z<<std::endl;
	//    //vector3df newPos = (posPers + vecRel)*vel*dt;

	vector3df newPos = newPos.set(posPers.X, 90, posPers.Z - 60);
	//newPos.X = (posPers.X + vecRel.X);

	// newPos.Z = (posPers.Z + vecRel.Z);

	//newPos.Y = 70;
	setPos(newPos);
	setFoco(posPers);
	//      std::cout<<"//////////////////////////////////////////"<<std::endl;
	//            std::cout<<""<<std::endl;
	//      std::cout<<"Despues"<<std::endl;
	//    std::cout<<"X: "<<posicion.X<<" Y: "<<posicion.Y<<" Z: "<<posicion.Z<<std::endl;
	/* switch(modo){

	case 0:
	posicion.X += vel*dt;
	foco.X += vel*dt;
	break;

	case 1:
	posicion.X -= vel*dt;
	foco.X -= vel*dt;
	break;

	case 2:

	posicion.Z += vel*dt;
	foco.Z += vel*dt;

	break;

	case 3:

	posicion.Z -= vel*dt;
	foco.Z -= vel*dt;

	break;

	}*/

}

vector3df Camara::getFoco() {
	return foco;
}

vector3df Camara::getPos() {
	return posicion;
}

void Camara::setFoco(vector3df f) {
	foco = f;
	camara->setTarget(f);
}
void Camara::setPos(vector3df pos) {
	posicion = pos;
	camara->setPosition(pos);


}



