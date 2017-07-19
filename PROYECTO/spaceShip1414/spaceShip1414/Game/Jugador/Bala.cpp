/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

#include "Bala.h"
#include <Math.h>
#include "../Fisicas/Entity2D.h"
#include "../Fisicas/Mundo.h"
#include "../graphicEngine\TGraphicEngine.h"
#include "../graphicEngine\entityTree\TNodo.h"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

Bala::Bala(TGraphicEngine * motorApp, Mundo *world, glm::vec3 posPers, glm::vec3 mousePosition, 
	float dumug, int tipo, float velocidad, float rotBala) {



	vel = velocidad;
	//pos = maya->getPosition();

	nodo = motorApp->addMalla("resourse/models/Objetos/bullet.obj");
	motorApp->escalar(nodo, 0.1f, 0.1f, 0.1f);
	motorApp->trasladar(nodo, posPers.x, posPers.y + 5.0f, posPers.z);
	engine = motorApp;

	posRaton = mousePosition; //vector direccion del personaje donde esta mirando
	//rotar las balas dependiendo del vector direccion que se le pasa si la bala es del jugador
	posInicial = posPers;

	damage = dumug;

	if (tipo == 1) { //jugador
		motorApp->rotarYPR(nodo, rotBala, 0, 0);
		entity = new Entity2D(world->getWorldBox2D(), posPers, glm::vec3(0,0,0), true, this, tipo);
	}
	else {
		//maya->getMaterial(0).EmissiveColor.set(0, 0, 140, 255);
		entity = new Entity2D(world->getWorldBox2D(), posPers, glm::vec3(0, 0, 0), true, this, tipo);

	}

}

Bala::Bala(const Bala& orig) {
}

Bala::~Bala() {
	std::cout << "MUERO BALA" << std::endl;

	//nodo->destruirEntidad();
	engine->buscarNodoPadre(nodo);
	nodo = nullptr;
	delete(entity);
}

void Bala::setPosition(glm::vec3 v) {
	//maya->setPosition(v);
}

void Bala::mover() {


	if (entity != NULL) {

		//glm::vec2 direction(posRaton.x - 683, posRaton.y - 384); //pasar tamanyo pantalla por parametro
		//direction = glm::normalize(direction);

		//float v1 = direction.x * vel;
		//float v2 = -direction.y * vel;

		b2Vec2 v(posRaton.x, posRaton.z);
		v = vel * v;
		//float x = entity->getCuerpo2D()->GetPosition().x + v1;
		//float y = entity->getCuerpo2D()->GetPosition().y + v2;
		//entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(v1, v2));
		entity->getCuerpo2D()->SetLinearVelocity(v);

		engine->resetTransform(this->getNodo(), 't');
		engine->trasladar(this->getNodo(), entity->getCuerpo2D()->GetPosition().x, 
			posInicial.y + 1.0f, -entity->getCuerpo2D()->GetPosition().y);


	}
}


void Bala::moverEnemigoDisparo() {

	if (entity != NULL) {
		//posraton en este metodo es la posicion del jugador

		glm::vec2 direction(posRaton.x - posInicial.x, posRaton.y - posInicial.z); //pasar tamanyo pantalla por parametro
		direction = glm::normalize(direction);


		float v1 = direction.x * vel;
		float v2 = direction.y * vel;

		entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(v1, v2));

		//maya->setPosition(vector3df(entity->getCuerpo2D()->GetPosition().x, 10, entity->getCuerpo2D()->GetPosition().y));
		// maya->setPosition(vector3df(x, 10, y));

		//pos = maya->getPosition();

	}
}

glm::vec3 Bala::getPos() {

	return pos;
}

void Bala::setPosRaton() {

}

bool Bala::estaViva() {
	if (entity != NULL)
		return entity->getLive();
	else
		return false;
	//    return life;
}

//bool Bala::update() {

	//float hola = pos.getDistanceFrom(posInicial);
	////std::cout << "Distancia: " << hola << std::endl;

	//if (hola > 100) {
	//	if (entity != NULL)
	//		entity->setLive(false);
	//	//        life = false;
	//	return false;
	//}
	//else
	//	return true;


//}

float Bala::getDamage() {
	return damage;
}


Entity2D* Bala::getEntity()
{
	return entity;
}

void Bala::rotation(TGraphicEngine * motorApp, float a, float x, float y, float z)
{
	motorApp->rotar(nodo, a, x, y, z);
}

void Bala::rotationYPR(TGraphicEngine * motorApp, float y, float p, float r)
{
	motorApp->rotarYPR(nodo, y, p, r);
}

void Bala::scale(TGraphicEngine * motorApp, float x, float y, float z)
{
	motorApp->escalar(nodo, x, y, z);
}

void Bala::translation(TGraphicEngine * motorApp, float x, float y, float z)
{
	motorApp->trasladar(nodo, x, y, z);
}

TNodo * Bala::getNodo()
{
	return nodo;
}
