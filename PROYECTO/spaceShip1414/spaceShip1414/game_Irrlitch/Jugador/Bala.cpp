/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

#include "Bala.h"
#include "../Escenario/readJson.h"
#include <Math.h>


#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

Bala::Bala(ISceneManager* smgr, IVideoDriver* driver, b2World *world, vector3df posPers, vector2df mousePosition, float dumug, int tipo, float velocidad) {

	maya = smgr->addSphereSceneNode(2);

	if (maya) {


		maya->setPosition(posPers);
		// maya->setMaterialTexture(0, driver->getTexture("texture/bruce.jpg"));
		//primer parametro del setVertexColors es de la maya que quieres cambiar el color y con su getMesh se consigue
		maya->getMaterial(0).EmissiveColor.set(0, 255, 140, 0);
	}


	vel = velocidad;
	pos = maya->getPosition();
	//    bodyDef.type = b2_dynamicBody;
	//    bodyDef.position.Set(pos.X, pos.Z);
	//    bodyShape.SetAsBox(2, 2);
	//    body = world->CreateBody(&bodyDef);
	//    body -> CreateFixture(&bodyShape, 1.0f);



	posRaton = vector2df(mousePosition.X, mousePosition.Y);

	posInicial = posPers;

	damage = dumug;

	if (tipo == 1) {
		entity = new Entity2D(world, pos, maya->getRotation(), true, this, tipo);
	}
	else {
		maya->getMaterial(0).EmissiveColor.set(0, 0, 140, 255);
		entity = new Entity2D(world, pos, maya->getRotation(), true, this, tipo);

	}

}

Bala::Bala(const Bala& orig) {
}

Bala::~Bala() {
	std::cout << "MUERO BALA" << std::endl;

	maya->getParent()->removeChild(maya);
	delete(entity);
}

void Bala::setPosition(vector3df v) {
	maya->setPosition(v);
}

void Bala::mover(f32 tiempo) {


	if (entity != NULL) {

		vector2df direction(posRaton.X - 683, posRaton.Y - 384); //pasar tamanyo pantalla por parametro
		direction.normalize();


		float v1 = direction.X * vel;
		float v2 = -direction.Y * vel;

		//float x = entity->getCuerpo2D()->GetPosition().x + v1;
		//float y = entity->getCuerpo2D()->GetPosition().y + v2;
		entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(v1, v2));

		maya->setPosition(vector3df(entity->getCuerpo2D()->GetPosition().x, 10, entity->getCuerpo2D()->GetPosition().y));
		// maya->setPosition(vector3df(x, 10, y));

		pos = maya->getPosition();

	}
}


void Bala::moverEnemigoDisparo() {

	if (entity != NULL) {
		//posraton en este metodo es la posicion del jugador

		vector2df direction(posRaton.X - posInicial.X, posRaton.Y - posInicial.Z); //pasar tamanyo pantalla por parametro
		direction.normalize();


		float v1 = direction.X * vel;
		float v2 = direction.Y * vel;

		entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(v1, v2));

		maya->setPosition(vector3df(entity->getCuerpo2D()->GetPosition().x, 10, entity->getCuerpo2D()->GetPosition().y));
		// maya->setPosition(vector3df(x, 10, y));

		pos = maya->getPosition();

	}
}

vector3df Bala::getPos() {

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

bool Bala::update() {

	float hola = pos.getDistanceFrom(posInicial);
	//std::cout << "Distancia: " << hola << std::endl;

	if (hola > 100) {
		if (entity != NULL)
			entity->setLive(false);
		//        life = false;
		return false;
	}
	else
		return true;


}

float Bala::getDamage() {
	return damage;
}


Entity2D* Bala::getEntity()
{
	return entity;
}
