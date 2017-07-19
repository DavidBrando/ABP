/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   Pared.cpp
* Author: David
*
* Created on 1 de diciembre de 2016, 19:35
*/
#include <iostream>
#include "Pared.h"
#include "../Fisicas/Entity2D.h"


Pared::Pared(vector3df posicion, vector3df rotacion, vector3df escala) {


	//    std::cout<<"///////////////////////////////////"<<std::endl;
	//    std::cout<<""<<std::endl;
	//    std::cout<<this<<std::endl;
	//    std::cout<<"X: "<<posicion.X<<" Y: "<<posicion.Y<<" Z: "<<posicion.Z<<std::endl;

	pos = posicion;
	rot = rotacion;
	escal = escala;

}

Pared::Pared(const Pared& orig) {
}

Pared::~Pared() {
}

vector3df Pared::getPosicion() {
	return pos;
}

vector3df Pared::getRotacion() {
	return rot;
}

vector3df Pared::getEscala() {
	return escal;
}



void Pared::setPosicion(vector3df newPos) {
	pos = newPos;
}

void Pared::setRotacion(vector3df newRot) {
	rot = newRot;
}

void Pared::setEscala(vector3df newEscala) {
	escal = newEscala;
}



void Pared::setFisica(b2World* world) {
	//std::cout<<"CREO PARED! "<<std::endl;

	entity = new Entity2D(world, pos, rot, escal, this);

}
