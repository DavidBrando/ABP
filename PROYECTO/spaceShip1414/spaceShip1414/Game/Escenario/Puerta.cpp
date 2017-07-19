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
#include "../Fisicas\Mundo.h"
#include "../graphicEngine\TGraphicEngine.h"
#include "../graphicEngine\entityTree\TTransform.h"
#include "../graphicEngine\entityTree\TNodo.h"
#include "../graphicEngine\entityTree\TMalla.h"
#include "../graphicEngine\entityTree\TCamara.h"

#define VEL 200.0f

Puerta::Puerta(TGraphicEngine * motorApp, int ident, glm::vec3 posicion, glm::vec3 rotacion, glm::vec3 escala, std::string llave, std::string tipo, std::string model){
	
	id = ident;
	pos = posicion;
	rot = rotacion;
	escal = escala;
	posIni = posicion;
	t_puerta = tipo;
	motor = motorApp;
	rotation = motorApp->crearTransform();
	scale = motorApp->crearTransform();
	translation = motorApp->crearTransform();
	scale->escalar(escal.x, escal.y, escal.z);
	//rotation->rotar(rot.x, 1.0f, 0.0f, 0.0f);
	//rotation->rotar(rot.y, 0.0f, 1.0f, 0.0f);
	//rotation->rotar(rot.z, 0.0f, 0.0f, 1.0f);
	rotation->rotarYPR(rot.y, rot.x, rot.z);
	translation->trasladar(pos.x, pos.y, pos.z);

	TNodo* nodoTransfRM = motorApp->crearNodo(motorApp->nodoRaiz(), rotation);
	TNodo* nodoTransfEM = motorApp->crearNodo(nodoTransfRM, scale);
	TNodo* nodoTransfTM = motorApp->crearNodo(nodoTransfEM, translation);
	nodoMalla = motorApp->crearNodo(nodoTransfTM, motorApp->crearMalla("resourse/models/Escenario/puertas/"+model+".obj"));

	abierta = false;
	limiteApX = pos.x + (escal.x / 2);
	limiteApZ = -(pos.z + (escal.z / 2));
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
	nodoB = nullptr;
	entityB = nullptr;
	//if (modelB != "") {

	//}
	//else {
	//	nodoB = nullptr;
	//}
}

Puerta::Puerta(TGraphicEngine * motorApp, int ident, glm::vec3 posicion, glm::vec3 rotacion, glm::vec3 escala, std::string llave, std::string tipo, std::string model, 
	glm::vec3 posicion2, glm::vec3 rotacion2, glm::vec3 escala2, std::string modelB)
{

	id = ident;
	pos = posicion;
	rot = rotacion;
	escal = escala;
	posIni = posicion;
	t_puerta = tipo;
	motor = motorApp;
	rotation = motorApp->crearTransform();
	scale = motorApp->crearTransform();
	translation = motorApp->crearTransform();
	scale->escalar(escal.x, escal.y, escal.z);
	//rotation->rotar(rot.x, 1.0f, 0.0f, 0.0f);
	//rotation->rotar(rot.y, 0.0f, 1.0f, 0.0f);
	//rotation->rotar(rot.z, 0.0f, 0.0f, 1.0f);
	rotation->rotarYPR(rot.y, rot.x, rot.z);

	translation->trasladar(pos.x, pos.y, pos.z);

	TNodo* nodoTransfRM = motorApp->crearNodo(motorApp->nodoRaiz(), rotation);
	TNodo* nodoTransfEM = motorApp->crearNodo(nodoTransfRM, scale);
	TNodo* nodoTransfTM = motorApp->crearNodo(nodoTransfEM, translation);
	nodoMalla = motorApp->crearNodo(nodoTransfTM, motorApp->crearMalla("resourse/models/Escenario/puertas/" + model + ".obj"));

	rotation2 = motorApp->crearTransform();
	scale2 = motorApp->crearTransform();
	translation2 = motorApp->crearTransform();


	scale2->escalar(escala2.x, escala2.y, escala2.z);
	rotation2->rotarYPR(rotacion2.y, rotacion2.x, rotacion2.z);

	translation2->trasladar(posicion2.x, posicion2.y, posicion2.z);


	nodoTransfRM = motorApp->crearNodo(motorApp->nodoRaiz(), rotation2);
	nodoTransfEM = motorApp->crearNodo(nodoTransfRM, scale2);
	nodoTransfTM = motorApp->crearNodo(nodoTransfEM, translation2);

	nodoB = motorApp->crearNodo(nodoTransfTM, motorApp->crearMalla("resourse/models/Escenario/puertas/" + modelB + ".obj"));

	abierta = false;
	limiteApX = pos.x + (escal.x / 4);
	limiteApZ = -(pos.z + (escal.z / 4));
	limiteX = posicion2.x + (escala2.x / 4);
	limiteZ = -(posicion2.z + (escala2.z / 4));

	posIniB = posicion2;

	CERRADA = new Estados("CERRADA");
	ABIERTA = new Estados("ABIERTA");
	BLOQUEADA = new Estados("BLOQUEADA");
	BLOQLLAVE = new Estados("BLOQLLAVE");
	Maquina = new MaquinaEstados();
	Maquina->addEstado(CERRADA);
	Maquina->addEstado(ABIERTA);

	if (llave != "ABIERTA") {
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

	delete(scale);
	delete(rotation);
	delete(translation);
	delete entity;
	delete entityB;
	delete CERRADA;
	delete ABIERTA;
	delete BLOQLLAVE;
	delete BLOQUEADA;
	delete Maquina;
}

TTransform * Puerta::Rotation()
{
	return rotation;
}

TTransform * Puerta::Scale()
{
	return scale;
}

TTransform * Puerta::Translation()
{
	return translation;
}


glm::vec3 Puerta::getPosicion() {
	return pos;
}

glm::vec3 Puerta::getRotacion() {
	return rot;
}

glm::vec3 Puerta::getEscala() {
	return escal;
}

bool Puerta::getTotalAbierta() {
	return abierta;
}

bool Puerta::getAbierta() {
	return abrir;
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


	if (detectado == true)
	{
	
		/*if (Maquina->getEstadoActivo()->getEstado() == "BLOQLLAVE")*/
			//maya->getMaterial(0).EmissiveColor.set(0, 0, 180, 0);

		Maquina->cambiaEstado("ABIERTA");
	}

	if (detectado == false && abierta == true)
	{
		std::cout << "entra" << std::endl;
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


void Puerta::setFisica(Mundo *world, int ident) {
	//std::cout<<"CREO PARED! "<<std::endl;

	entity = new Entity2D(world->getWorldBox2D(), pos, rot, escal, true, this,ident);

}

void Puerta::setFisicas(Mundo *world, int ident, glm::vec3 p, glm::vec3 r, glm::vec3 e) {

	entityB = new Entity2D(world->getWorldBox2D(), p, r, e, true, this, ident);

}

TNodo * Puerta::getNodo()
{
	return nodoMalla;
}

void Puerta::abrirPuerta() {


	//si tiene rotacion en Y van | sino van -

	if (t_puerta=="ARRIBA")
	{
		
		
		if (entity->getCuerpo2D()->GetPosition().x  < limiteApX+10)
		{
			entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(120, 0));
			
		}


		else
		{
			abierta = true;
			//std::cout << detectado << std::endl;
			entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(0, 0));
			if(entityB != nullptr){
				entityB->getCuerpo2D()->SetLinearVelocity(b2Vec2(0, 0));

			}


			if (detectado == false)
			{
				ABIERTA->limpiarEstado();
				Maquina->cambiaEstado("CERRADA");
			}
		}

		if (motor->getPosicion(this->getNodo()).y<10)
		{
			std::cout << motor->getPosicion(this->getNodo()).y << " " << limiteApX << std::endl;
			motor->trasladar(this->getNodo(), 0, 2, 0);  //:*
		}

	}

	else if (t_puerta == "LATERAL") {

		if (rot.y==0)
		{
			if (entity->getCuerpo2D()->GetPosition().x < -limiteApX + 10)
			{
				entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(120, 0));

			}

			if (entityB != nullptr && entityB->getCuerpo2D()->GetPosition().x < limiteX + 10) {
				entityB->getCuerpo2D()->SetLinearVelocity(b2Vec2(120, 0));

			}

			else
			{
				abierta = true;
				//std::cout << detectado << std::endl;
				entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(0, 0));
				if (entityB != nullptr) {
					entityB->getCuerpo2D()->SetLinearVelocity(b2Vec2(0, 0));

				}


				if (detectado == false)
				{
					ABIERTA->limpiarEstado();
					Maquina->cambiaEstado("CERRADA");
				}
			}

			if (motor->getPosicion(this->getNodo()).x > posIni.x - 10)
			{
				//std::cout << motor->getPosicion(this->getNodo()).y << " " << limiteApX << std::endl;
				motor->trasladar(this->getNodo(), -2, 0, 0);  //:*
			}

			if (nodoB != nullptr && motor->getPosicion(nodoB).x < posIniB.x + 10)
			{
				//std::cout << motor->getPosicion(nodoB).y << " " << limiteX << std::endl;
				motor->trasladar(nodoB, 2, 0, 0);  //:*
			}
		}
		else
		{
			if (entity->getCuerpo2D()->GetPosition().y < limiteApZ + 20)
			{
				entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(0, 120));

			}

			if (entityB != nullptr && entityB->getCuerpo2D()->GetPosition().y < limiteZ + 20) {
				entityB->getCuerpo2D()->SetLinearVelocity(b2Vec2(0, 120));

			}

			else
			{
				abierta = true;
				//std::cout << detectado << std::endl;
				entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(0, 0));
				if (entityB != nullptr) {
					entityB->getCuerpo2D()->SetLinearVelocity(b2Vec2(0, 0));

				}


				if (detectado == false)
				{
					ABIERTA->limpiarEstado();
					Maquina->cambiaEstado("CERRADA");
				}
			}

			if (motor->getPosicion(this->getNodo()).z < posIni.z + 10)
			{
			//	std::cout <<"Alllla: "<< motor->getPosicion(this->getNodo()).z << " " << posIni.z-10 << std::endl;
				motor->trasladar(this->getNodo(), 0, 0, 2);  //:*
			}

			if (nodoB != nullptr && motor->getPosicion(nodoB).z > posIniB.z - 10)
			{
				//std::cout << motor->getPosicion(nodoB).y << " " << limiteX << std::endl;
				motor->trasladar(nodoB, 0, 0, -2);  //:*
			}
		}
	}

}

void Puerta::cerrarPuerta() {


	if (t_puerta == "ARRIBA")
	{

		if (motor->getPosicion(this->getNodo()).y > 0)
		{
			std::cout << "pos puerta: " << motor->getPosicion(this->getNodo()).y << " " << limiteApX << std::endl;
			motor->trasladar(this->getNodo(), 0, -2, 0);
		}


		if (entity->getCuerpo2D()->GetPosition().x >= limiteApX)
		{
			entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(-120, 0));

		}



		else
		{
			abierta = false;
			entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(0, 0));

			Maquina->cambiaEstado("BLOQUEADA");
		}

	
	}
	/*}*/

	//else {
	//	
	//	if (limiteApX - 2 < entity->getCuerpo2D()->GetPosition().x)
	//	{
	//		entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(-VEL, 0.0f));
	//		pos.x = entity->getCuerpo2D()->GetPosition().x;
	//		translation->resetMatriz();
	//		translation->trasladar(pos.x, pos.y, pos.z);

	//	}
	//	else
	//	{
	//		abierta = false;
	//		entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(0, 0));

	//		//Maquina->cambiaEstado("BLOQUEADA");

	//	}
	//	//  entity->getSombraP2D()->SetLinearVelocity(b2Vec2(-vel, 0.0f));


	//}

	else if (t_puerta == "LATERAL") {
		if (rot.y == 0)
		{
			if (motor->getPosicion(this->getNodo()).x < posIni.x - 1)
			{
				std::cout << "pos puerta: " << motor->getPosicion(this->getNodo()).y << " " << limiteApX << std::endl;
				motor->trasladar(this->getNodo(), 2, 0, 0);
			}

			if (nodoB != nullptr && motor->getPosicion(nodoB).x > posIniB.x + 1)
			{
				std::cout << motor->getPosicion(nodoB).y << " " << limiteX << std::endl;
				motor->trasladar(nodoB, -2, 0, 0);  //:*
			}

			if (entity->getCuerpo2D()->GetPosition().x >= limiteApX)
			{
				entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(-120, 0));

			}

			if (entityB != nullptr && entityB->getCuerpo2D()->GetPosition().x >= limiteX) {
				entityB->getCuerpo2D()->SetLinearVelocity(b2Vec2(-120, 0));

			}

			else
			{
				abierta = false;
				entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(0, 0));

				if (entityB != nullptr) {
					entityB->getCuerpo2D()->SetLinearVelocity(b2Vec2(0, 0));

				}
				Maquina->cambiaEstado("BLOQUEADA");
			}
		}
		else
		{
			if (motor->getPosicion(this->getNodo()).z > posIni.z + 1)
			{
				std::cout << "pos puerta: " << motor->getPosicion(this->getNodo()).y << " " << limiteApX << std::endl;
				motor->trasladar(this->getNodo(), 0, 0,-2);
			}

			if (nodoB != nullptr && motor->getPosicion(nodoB).z < posIniB.z - 1)
			{
				std::cout << motor->getPosicion(nodoB).y << " " << limiteX << std::endl;
				motor->trasladar(nodoB, 0, 0, 2);  //:*
			}

			if (entity->getCuerpo2D()->GetPosition().y >= limiteApZ)
			{
				entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(0, -400));

			}

			if (entityB != nullptr && entityB->getCuerpo2D()->GetPosition().y >= limiteZ) {
				entityB->getCuerpo2D()->SetLinearVelocity(b2Vec2(0, -400));

			}

			else
			{
				abierta = false;
				entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(0, 0));

				if (entityB != nullptr) {
					entityB->getCuerpo2D()->SetLinearVelocity(b2Vec2(0, 0));

				}
				Maquina->cambiaEstado("BLOQUEADA");
			}
		}

	}


}

void Puerta::Update()
{
	//std::cout << "ABIERTA: " << ABIERTA->getEstadoActivo() <<"CERRADA: "<< CERRADA->getEstadoActivo() <<std::endl;

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