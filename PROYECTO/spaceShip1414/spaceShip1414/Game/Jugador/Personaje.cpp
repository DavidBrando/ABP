/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   Personaje.cpp
* Author: User
*
* Created on 16 de noviembre de 2016, 15:41
*/


#include "Personaje.h"
#include "Bala.h"
#include "Pistola.h"
#include "Fusil.h"
#include "Escopeta.h"
#include "../Fisicas/Entity2D.h"
#include "../Juego.h"
#include "Inventario.h"
#include <Math.h>
#include "../Escenario/ObjConsumables/Botiquines.h"

#define PISTOLA 0
#define FUSIL 1
#define ESCOPETA 2

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

Personaje::Personaje(ISceneManager* smgr, IVideoDriver* driver, b2World *world, Juego* j) {

	maya = smgr->addCubeSceneNode(10); //se crea de tamanyo 10x10x10

	if (maya) {
		maya->setMaterialFlag(EMF_LIGHTING, false);
		maya->setPosition(vector3df(0, 10, 0));
		maya->setMaterialTexture(0, driver->getTexture("./textura/bruce.jpg"));
		//primer parametro del setVertexColors es de la maya que quieres cambiar el color y con su getMesh se consigue
		// smgr -> getMeshManipulator()->setVertexColors(cube->getMesh(), SColor(0, 0, 255, 128));//lus, R, G, B

	}




	vel = 300.0f;
	vida = 100.0f;
	vidaMax = vida;
	pos = maya->getPosition();
	entity = new Entity2D(world, pos, this, smgr);
	game = j;
	tiempoDisparo = 0.0f;

	disparo = false;
	teclaE = false;
	teclaQ = false;

	pistola = new Pistola();
	fusil = new Fusil();
	escopeta = new Escopeta();

	armaActual = PISTOLA;
	cargador = pistola->getCargador();
	municionTotal = pistola->getCapacidadDeMun();
	inv = new Inventario();

	irr::core::stringw wideString(vida);
	GVida = smgr->addTextSceneNode(smgr->getGUIEnvironment()->getBuiltInFont(), wideString.c_str(), video::SColor(255, 255, 0, 0), 0);
	RVida = smgr->addTextSceneNode(smgr->getGUIEnvironment()->getBuiltInFont(), L"Vida: ", video::SColor(255, 255, 0, 0), 0);
	//napis a lo mejor estaria bien que estuviese en el .h de enemigo
	//tambien se tiene que borrar con el destructor
	GVida->setPosition(pos);
	RVida->setPosition(vector3df(pos.X - 8, pos.Y, pos.Z));
}

Personaje::Personaje(const Personaje& orig) {
}

Personaje::~Personaje() {
	//this->destroyBalas();
	std::cout << "POS PERS ANTES" << std::endl;
	listaBalas.clear();
	delete(entity);
	//GVida->getParent()->removeChild(GVida);
	//RVida->getParent()->removeChild(RVida);
//	maya->getParent()->removeChild(maya);
	delete(pistola);
	delete(fusil);
	delete(escopeta);
	destroyBalas();
}

void Personaje::moverPersonaje(int modo, f32 dt) {

	//std::cout<<"//////////////////////////////////////////"<<std::endl;
	//            std::cout<<""<<std::endl;
	//            std::cout<<"POS PERS ANTES"<<std::endl;
	//                 std::cout<<"Pos 3D X: "<<pos.X<<"Pos 3D Z: "<<pos.Z<<std::endl;
	//                 std::cout<<"Pos 2D X: "<<entity->getCuerpo2D()->GetPosition().x<<"Pos 2D Z: "<<entity->getCuerpo2D()->GetPosition().y<<std::endl;

	switch (modo) {

	case 0:
		/* std::cout<<"case 0: Sntes"<<std::endl;
		std::cout<<"Pos X: "<<pos.X<<std::endl;
		std::cout<<"Pos2D X: "<<body->GetPosition().x<<std::endl;*/
		// body->ApplyForceToCenter(b2Vec2(5.0,0.0), true);

		entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(vel, 0.0f));
		// entity->getSombraP2D()->SetLinearVelocity(b2Vec2(vel, 0.0f));
		//pos.X = entity->getCuerpo2D()->GetPosition().x;

		/* std::cout<<"Des"<<std::endl;
		std::cout<<"Pos X: "<<pos.X<<std::endl;
		std::cout<<"Pos2D X: "<<entity->getBody2D->GetPosition().x<<std::endl;*/

		break;

	case 1:

		/*  std::cout<<"case 1: Sntes"<<std::endl;
		std::cout<<"Pos X: "<<pos.X<<std::endl;
		std::cout<<"Pos2D X: "<<entity->getBody2D->GetPosition().x<<std::endl;*/

		entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(-vel, 0.0f));
		//  entity->getSombraP2D()->SetLinearVelocity(b2Vec2(-vel, 0.0f));
		//pos.X = entity->getCuerpo2D()->GetPosition().x;


		/*std::cout<<"Des"<<std::endl;
		std::cout<<"Pos X: "<<pos.X<<std::endl;
		std::cout<<"Pos2D X: "<<entity->getBody2D->GetPosition().x<<std::endl;*/

		break;

	case 2:

		/*   std::cout<<"case 2: Sntes"<<std::endl;
		std::cout<<"Pos Z: "<<pos.Z<<std::endl;
		std::cout<<"Pos2D Z: "<<entity->getCuerpo2D()->GetPosition().y<<std::endl;*/

		entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(0.0f, vel));
		// entity->getSombraP2D()->SetLinearVelocity(b2Vec2(0.0f, vel));
		//pos.Z = entity->getCuerpo2D()->GetPosition().y;


		/*  std::cout<<"Des"<<std::endl;
		std::cout<<"Pos Z: "<<pos.Z<<std::endl;
		std::cout<<"Pos2D Z: "<<entity->getCuerpo2D()->GetPosition().y<<std::endl;*/

		break;

	case 3:

		/*   std::cout<<"case 3: Sntes"<<std::endl;
		std::cout<<"Pos Z: "<<pos.Z<<std::endl;
		std::cout<<"Pos2D Z: "<<entity->getCuerpo2D()->GetPosition().y<<std::endl;*/

		entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(0.0f, -vel));
		//entity->getSombraP2D()->SetLinearVelocity(b2Vec2(0.0f, -vel));
		//pos.Z = entity->getCuerpo2D()->GetPosition().y;

		/* std::cout<<"Des"<<std::endl;
		std::cout<<"Pos Z: "<<pos.Z<<std::endl;
		std::cout<<"Pos2D Z: "<<entity->getCuerpo2D()->GetPosition().y<<std::endl;*/


		break;

		//W+D
	case 4:

		entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(vel, vel));
		//entity->getSombraP2D()->SetLinearVelocity(b2Vec2(vel, vel));
		//pos.X = entity->getCuerpo2D()->GetPosition().x;
		//pos.Z = entity->getCuerpo2D()->GetPosition().y;


		break;

		//D+S
	case 5:
		entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(vel, -vel));
		//entity->getSombraP2D()->SetLinearVelocity(b2Vec2(vel, -vel));
		//pos.X = entity->getCuerpo2D()->GetPosition().x;
		//pos.Z = entity->getCuerpo2D()->GetPosition().y;
		break;

		//A+S
	case 6:

		entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(-vel, -vel));
		// entity->getSombraP2D()->SetLinearVelocity(b2Vec2(-vel, -vel));
		//pos.X = entity->getCuerpo2D()->GetPosition().x;
		//pos.Z = entity->getCuerpo2D()->GetPosition().y;

		break;

		//A+W
	case 7:

		entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(-vel, vel));
		//   entity->getSombraP2D()->SetLinearVelocity(b2Vec2(-vel, vel));
		//pos.X = entity->getCuerpo2D()->GetPosition().x;
		//pos.Z = entity->getCuerpo2D()->GetPosition().y;

		break;

	}
	//    std::cout<<"//////////////////////////////////////////"<<std::endl;
	//            std::cout<<""<<std::endl;
	//            std::cout<<"POS PERS DESPUES"<<std::endl;
	//                 std::cout<<"Pos 3D X: "<<pos.X<<"Pos 3D Z: "<<pos.Z<<std::endl;
	//                 std::cout<<"Pos 2D X: "<<entity->getCuerpo2D()->GetPosition().x<<"Pos 2D Z: "<<entity->getCuerpo2D()->GetPosition().y<<std::endl;


	actualizarPosicion();
	direccion = modo;
	setPos(pos);
}




vector3df Personaje::getPos() {
	return pos;
}

vector3df Personaje::getRot() {
	return maya->getRotation();
}

void Personaje::setPos(vector3df pos) {
	maya->setPosition(pos);
}

float Personaje::getVel() {
	return vel;
}

int Personaje::getDireccion() {
	return direccion;
}

void Personaje::actualizarPosicion() {

	pos.X = entity->getCuerpo2D()->GetPosition().x;
	pos.Z = entity->getCuerpo2D()->GetPosition().y;

	setPos(pos);
	GVida->setPosition(pos);
	RVida->setPosition(vector3df(pos.X - 8, pos.Y, pos.Z));

}

void Personaje::setVelocidad() {

	entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
	this->actualizarPosicion();
	// entity->getSombraP2D()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
}

void Personaje::rotar(vector3df raton) {

	float anguloRaton;
	anguloRaton = -atan2f(raton.X - 683, raton.Y - 384) * 180 / 3.14; //pasar tamanyo pantalla por parametro

																	  //std::cout << "ANGULO: " << anguloRaton << std::endl;
	maya->setRotation(vector3df(0, anguloRaton + 90, 0));
	angulo = maya->getRotation();

	//    line3df linea = getRay

}

vector3df Personaje::getAngulo() {
	return angulo;
}


bool Personaje::getDisparo() {
	return disparo;
}

int Personaje::getCargador() {
	return cargador;
}

//aqui
int Personaje::getMunicionActual()
{
	return municionTotal;
}

f32 Personaje::getTiempoDisparo() {
	return tiempoDisparo;
}

int Personaje::getArmaActual() {
	return armaActual;
}

bool Personaje::getTeclaE()
{
	return teclaE;
}

bool Personaje::getTeclaQ()
{
	return teclaQ;
}

bool Personaje::getImpulso()
{
	return impulso;
}

void Personaje::setImpulso(bool x)
{
	impulso = x;
}

void Personaje::quitarVida(float damage)
{
	std::cout << std::endl;
	std::cout <<"VIDA ANTES: "<<vida<< std::endl;

	vida = vida - damage;
	irr::core::stringw wideString(vida);
	GVida->setText(wideString.c_str());

	std::cout << std::endl;
	std::cout << "VIDA DESPUES: " << vida << std::endl;
}

void Personaje::curar(float recup)
{
	vida += recup;
	irr::core::stringw wideString(vida);
	GVida->setText(wideString.c_str());
}

void Personaje::usarBotiquin()
{

	Botiquines *bot = static_cast<Botiquines*>(inv->usarObjeto(0));
	
	if (bot != nullptr) {


		float dif = vidaMax - vida;

		if (dif >= bot->getVida()) {
			curar(bot->getVida());
			inv->deleteObj(bot);
		}

		else if(vida != vidaMax) {
			curar(dif);
			inv->deleteObj(bot);

		}

		else {
			std::cout << std::endl;
			std::cout << "TIENES LA VIDA MAX " << std::endl;
			std::cout << std::endl;
		}

		
	}

	else {
		std::cout << std::endl;
		std::cout << "NO TIENES BOTIQUINES " << std::endl;
		std::cout << std::endl;

	}


	
}

float Personaje::getVida()
{
	return vida;
}

void Personaje::pasarMensaje() {

	game->cambioEstado("menu");
}


void Personaje::iniciarTiempoImpulso() {

	temporizador = 8.0f;

}

void Personaje::disminuirTem() {
	
	temporizador -= 0.5f;
}

float Personaje::getTemporizador() {

	return temporizador;
}

Inventario * Personaje::getInventario()
{
	return inv;
}


float Personaje::getDamage() {

	switch (armaActual) {

	case 0:
		return pistola->getDamage();
		break;

	case 1:
		return fusil->getDamage();
		break;

	case 2:
		return escopeta->getDamage();
		break;

	}
}

float Personaje::getTiempoArma() {

	switch (armaActual) {

	case 0:
		return pistola->getTiempoDisparo();
		break;

	case 1:
		return fusil->getTiempoDisparo();
		break;

	case 2:
		return escopeta->getTiempoDisparo();
		break;

	}
}

void Personaje::setArmaActual(int newArma) {

	//habria que poner tambien el de total de municion del arma actual (llamar al seter)
	//y devolver tambien el cargador total del arma
	switch (armaActual) {

	case 0:

		pistola->setMunicionAcutal(cargador);
		pistola->setCapacidadDeMun(municionTotal);

		break;

	case 1:

		fusil->setMunicionAcutal(cargador);
		fusil->setCapacidadDeMun(municionTotal);

		break;

	case 2:

		escopeta->setMunicionAcutal(cargador);
		escopeta->setCapacidadDeMun(municionTotal);
		break;

	}

	std::cout << "" << std::endl;
	std::cout << "ARMA: "<<armaActual << std::endl;
	std::cout << "MUNICION TOTAL: " << municionTotal << std::endl;
	std::cout << "" << std::endl;


	armaActual = newArma;

	switch (armaActual) {

	case 0:
		std::cout << "CAMBIO A PISTOLA " << armaActual << std::endl;
		cargador = pistola->getMunicionActual();
		municionTotal = pistola->getCapacidadDeMun();

		break;

	case 1:

		std::cout << "CAMBIO A FUSIL " << armaActual << std::endl;
		cargador = fusil->getMunicionActual();
		municionTotal = fusil->getCapacidadDeMun();


		break;

	case 2:

		std::cout << "CAMBIO A ESCOPETA " << armaActual << std::endl;
		cargador = escopeta->getMunicionActual();
		municionTotal = escopeta->getCapacidadDeMun();


		break;

	

	}
		std::cout << "" << std::endl;
		std::cout << "ARMA CAMBIADA: " << armaActual << std::endl;
		std::cout << "MUNICION TOTAL: " << municionTotal << std::endl;
		std::cout << "" << std::endl;
}

void Personaje::recargar() {

	//restar de la recarga al total de balas que se tiene actualmente
	int recarga;

	switch (armaActual) {

	case 0:
		recarga = pistola->getCargador() - cargador;
	
		break;

	case 1:
		recarga = fusil->getCargador() - cargador;

		break;

	case 2:
		recarga = escopeta->getCargador() - cargador;

		break;

	}


	cargador += recarga;
	municionTotal -= recarga;
}

//cuando colisione contra una caja de municion se le suma hasta el maximo de cargador del arma
//hay que distinguir a que arma tiene que subir
void Personaje::cogerMunicion(int municionCogida, int arma)
{
	//usar armaActual para el switch
	//municionTotal += municionCogida;
	int auxMunicion;

	switch(arma) {

	case 0:

		auxMunicion = pistola->getCapacidadDeMun();
		auxMunicion += municionCogida;
		
		if(auxMunicion > pistola->getTotalMunicion()) {
			auxMunicion = pistola->getTotalMunicion();
		}

		pistola->setCapacidadDeMun(auxMunicion);

		if(arma == armaActual) {
			municionTotal = auxMunicion;
		}


		break;

	case 1:

		auxMunicion = fusil->getCapacidadDeMun();
		auxMunicion += municionCogida;

		if (auxMunicion > fusil->getTotalMunicion()) {
			auxMunicion = fusil->getTotalMunicion();
		}

		fusil->setCapacidadDeMun(auxMunicion);

		if (arma == armaActual) {
			municionTotal = auxMunicion;
		}

		break;

	case 2:

		auxMunicion = escopeta->getCapacidadDeMun();
		auxMunicion += municionCogida;

		if (auxMunicion > escopeta->getTotalMunicion()) {
			auxMunicion = escopeta->getTotalMunicion();
		}

		escopeta->setCapacidadDeMun(auxMunicion);

		if (arma == armaActual) {
			municionTotal = auxMunicion;
		}

		break;

	}

}

void Personaje::setDisparo(bool x) {
	disparo = x;
}

void Personaje::setTiempoDisparo(f32 t) {
	tiempoDisparo = t;
}


void Personaje::disparar(ISceneManager* smgr, IVideoDriver* driver, b2World *world, f32 dt, vector2df posRaton) {
	std::cout << "CARGADOR: " << cargador << std::endl;
	tiempoDisparo += dt;
	disparo = true;
	Bala *bullet = new Bala(smgr, driver, world, pos, posRaton, getDamage(), 1, 300.0f);
	listaBalas.push_back(bullet);
	cargador--;

}

void Personaje::destroyBalas() {
	if (!listaBalas.empty()) {
		for (std::list<Bala*>::iterator it = listaBalas.begin(); it != listaBalas.end();) {
			if ((*it) != NULL) {
				if (!(*it)->estaViva()) {

					(*it)->getEntity()->setLive(false);
				}
				else
					it++;
			}
			else
				it++;
		}
	}

}


void Personaje::actualizarLista(f32 dt) {
	if (!listaBalas.empty()) {
		for (std::list<Bala*>::iterator it = listaBalas.begin(); it != listaBalas.end();) {
			if ((*it) != NULL) {
				if (!(*it)->estaViva()) {

					delete(*it);
					it = listaBalas.erase(it);
				}
				else
					it++;
			}
			else
				it++;
		}

		for (std::list<Bala*>::iterator it = listaBalas.begin(); it != listaBalas.end(); it++) {
			if ((*it) != NULL && (*it)->estaViva() == true) {
				(*it)->mover(dt);
				//(*it)->update();
			}
		}
	}

}


void Personaje::setTeclaE(bool x)
{
	teclaE = x;
}

void Personaje::setTeclaQ(bool x)
{
	teclaQ = x;
}



bool Personaje::getVivo()
{

	if (entity != NULL)
		return entity->getLive();
	else
		return false;
}

Entity2D* Personaje::getEntity()
{
	return entity;
}