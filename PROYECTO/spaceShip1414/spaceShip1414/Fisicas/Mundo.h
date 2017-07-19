#pragma once
#include <Box2D\Box2D.h>


class MiContactListener;
class MyContactFilter;
class TGraphicEngine;
class TGameEngine;

class Mundo{

public:
	Mundo();
	~Mundo();
	void init();
	b2World* getWorldBox2D();
	void stepBox2D(double dt, int t, int s);
	void clearForcesBox2D();

	void setMotorGame(TGraphicEngine * motor, TGameEngine * juego);

private:

	b2World *world;
	MiContactListener* contactListenerInstance;
	MyContactFilter* filtroContact;
	b2Vec2 gravity;
};

