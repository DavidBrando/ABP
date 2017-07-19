/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   Puerta.cpp
* Author: David
*
* Created on 15 de diciembre de 2016, 20:03
*/
#include <iostream>
#include "Puerta.h"
#include "../MaquinaEstados/FSM/Estados.h"
#include "../MaquinaEstados/FSM/MaquinaEstados.h"
#include "../Fisicas/Entity2D.h"

#define VEL 200.0f

Puerta::Puerta(int ident, vector3df posicion, vector3df rotacion, vector3df escala, IMeshSceneNode *objeto, std::string llave){
	
	id = ident;
	pos = posicion;
	rot = rotacion;
	escal = escala;
	posIni = posicion;
	maya = objeto;
	abierta = false;
	limiteApX = this->getPosicion().X + (this->getEscala().X / 2);
	limiteApZ = this->getPosicion().Z + (this->getEscala().Z / 2);
	CERRADA = new Estados("CERRADA");
	ABIERTA = new Estados("ABIERTA");
	BLOQUEADA = new Estados("BLOQUEADA");
	BLOQLLAVE = new Estados("BLOQLLAVE");
	Maquina = new MaquinaEstados();
	Maquina->addEstado(CERRADA);
	Maquina->addEstado(ABIERTA);

	if(llave != "ABIERTA") {
		Maquina->addEstado(BLOQUEADA);
		Maquina->addEstado(BLOQLLAVE, true);
	}

	else {
		Maquina->addEstado(BLOQUEADA, true);
	}

	
	 //dependiendo de que string se le pase se inicia en un estado o otro
	llaveAsociada = llave;
	detectado = false;
	idDetect = -1;
}

Puerta::Puerta(const Puerta& orig) {
}

Puerta::~Puerta() {
}

vector3df Puerta::getPosicion() {
	return pos;
}

vector3df Puerta::getRotacion() {
	return rot;
}

vector3df Puerta::getEscala() {
	return escal;
}

bool Puerta::getTotalAbierta() {
	return abierta;
}

bool Puerta::getAbierta() {
	return abrir;
}

void Puerta::setPosicion(vector3df newPos) {
	pos = newPos;
}

void Puerta::setRotacion(vector3df newRot) {
	rot = newRot;
}

void Puerta::setEscala(vector3df newEscala) {
	escal = newEscala;
}

void Puerta::setDetectado(bool x,int ident)
{

		detectado = x;
		idDetect = ident;
	
}

void Puerta::setAbierta() {
	if (detectado==true)
	{
		Maquina->cambiaEstado("ABIERTA");
	}
	
}

void Puerta::setCerrada()
{
	if (detectado==false)
	{
		Maquina->cambiaEstado("CERRADA");
	}
}

void Puerta::UpdateEstado()
{
	if (detectado == true && id == idDetect)
	{
		if (Maquina->getEstadoActivo()->getEstado() == "BLOQLLAVE")
			maya->getMaterial(0).EmissiveColor.set(0, 0, 180, 0);

		Maquina->cambiaEstado("ABIERTA");
	}

	if (detectado == false && abierta == true)
	{
		Maquina->cambiaEstado("CERRADA");
	}


}

bool Puerta::getDetectado()
{
	return detectado;
}

std::string Puerta::getEstado()
{
	return Maquina->getEstadoActivo()->getEstado();
}

std::string Puerta::getLlaveAsociada()
{
	return llaveAsociada;
}


void Puerta::setFisica(b2World* world , ISceneManager* smgr,int ident) {
	//std::cout<<"CREO PARED! "<<std::endl;

	entity = new Entity2D(world, pos, rot, escal, true, this,smgr,ident);

}

void Puerta::abrirPuerta() {


	//si tiene rotacion en Y van | sino van -


	if (escal.Z != 1) {

		if (limiteApZ + 70>entity->getCuerpo2D()->GetPosition().y)
		{
			entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(0, VEL));
			pos.Z = entity->getCuerpo2D()->GetPosition().y;
			maya->setPosition(pos);

		}
		else
		{
			abierta = true;
			//std::cout << detectado << std::endl;
			entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(0, 0));
			if (detectado == false)
			{
				Maquina->cambiaEstado("CERRADA");
			}
		}
	}

	else {
		
		if (limiteApX+70>entity->getCuerpo2D()->GetPosition().x)
		{
			entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(VEL, 0.0f));
			pos.X = entity->getCuerpo2D()->GetPosition().x;
			maya->setPosition(pos);
		}
		else
		{
			abierta = true;
			//std::cout << detectado << std::endl;
			entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(0, 0));

			if (detectado == false)
			{
				Maquina->cambiaEstado("CERRADA");
			}
		}
		//  entity->getSombraP2D()->SetLinearVelocity(b2Vec2(-vel, 0.0f));
		

	}


}

void Puerta::cerrarPuerta() {



	if (escal.Z != 1) {

		if (limiteApZ-5<entity->getCuerpo2D()->GetPosition().y)
		{
			entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(0, -VEL));
			pos.Z = entity->getCuerpo2D()->GetPosition().y;
			maya->setPosition(pos);
		}
		else
		{
			abierta = false;
			entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(0, 0));

			//manejador.cambiaEstado("BLOQUEADA");
		}
	}

	else {
		
		if (limiteApX-5<entity->getCuerpo2D()->GetPosition().x)
		{
			entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(-VEL, 0.0f));
			pos.X = entity->getCuerpo2D()->GetPosition().x;
			maya->setPosition(pos);
		}
		else
		{
			abierta = false;
			entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(0, 0));

	//		manejador.cambiaEstado("BLOQUEADA");

		}
		//  entity->getSombraP2D()->SetLinearVelocity(b2Vec2(-vel, 0.0f));


	}


}

void Puerta::Update()
{
	

	if (ABIERTA->getEstadoActivo())
	{
		this->abrirPuerta();
	}

	if (CERRADA->getEstadoActivo())
	{
		this->cerrarPuerta();
	}
	//std::cout << Maquina->getEstadoActivo()->getEstado() << " COMPLETA: " << abierta << " id: " << id << " idEn: " << entity->getId() << " Detect: " << idDetect << std::endl;
	
	
	if (BLOQUEADA->getEstadoActivo())
	{
		
	}

}