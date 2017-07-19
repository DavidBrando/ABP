#include "Mundo.h"
#include "MiContactListener.h"
#include "MyContactFilter.h"
#include "../graphicEngine/TGraphicEngine.h"


Mundo::Mundo()
{
	world = new b2World(gravity);


	init();
}


Mundo::~Mundo()
{
	delete(contactListenerInstance);
	delete(filtroContact);
	delete(world);

}

void Mundo::init()
{
	contactListenerInstance = new MiContactListener();
	filtroContact = new MyContactFilter();
	gravity.Set(0.0f, 0.0f);

	world->SetContactListener(contactListenerInstance);
	world->SetContactFilter(filtroContact);
}

b2World * Mundo::getWorldBox2D()
{
	return world;
}

void Mundo::stepBox2D(double dt, int t, int s)
{
	world->Step(static_cast<float>(dt), t, s);
}

void Mundo::clearForcesBox2D()
{
	world->ClearForces();
}

void Mundo::setMotorGame(TGraphicEngine * motor, TGameEngine * juego)
{
	contactListenerInstance->setMotor(motor);
	contactListenerInstance->setJuego(juego);
}