/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Enemigo.cpp
 * Author: Iván
 *
 * Created on 29 de noviembre de 2016, 17:52
 */



#include <Math.h>
#include "Enemigo.h"
#include "Nodo.h"
#include "../Fisicas/Entity2D.h"
#include "Waypoints.h"
#include "AStar.h"
#include "../Jugador/Bala.h"
#include "LogicaDifusa.h"
#include "Flocking\Flocking.h"




#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

Enemigo::Enemigo(ISceneManager* smgr, IVideoDriver* driver, b2World *world, vector3df posicion, Waypoints* puntos) {
    


	smgr1 = smgr;
	mundo = world;
	VD = driver;
	puntoIni = nullptr;
	puntoFin = nullptr;
	dir = -1;
	vista = false;


}

//Enemigo::Enemigo(const Enemigo& orig) {
//}

Enemigo::~Enemigo() {
    std::cout << "" << std::endl;

    std::cout << "////////////////////////" << std::endl;
    std::cout << "MUERE: " << maya << std::endl;
	listaBalas.clear();
	estadoActual = -1;
	maya->getParent()->removeChild(maya);
    GVida->getParent()->removeChild(GVida);
    RVida->getParent()->removeChild(RVida);

	delete(path);
	delete(logica);
	/*delete(puntoIni);
	delete(puntoFin);*/
	delete(floc);
    delete(entity);
	puntoFin = nullptr;
	puntoIni = nullptr;
}

void Enemigo::Update(f32 dt) {

}


void Enemigo::Mover()
{
	//vector3df v = vel * u;
	//vecVel = v;
	//b2Vec2 vec;
	//
	//vec.Set(u.posicion.X, u.posicion.Z);
	//entity->getCuerpo2D()->SetLinearVelocity(vec);
	//entity->getSombraE2D()->SetLinearVelocity(vec);

	//pos.X = entity->getCuerpo2D()->GetPosition().x;
	//pos.Z = entity->getCuerpo2D()->GetPosition().y;

	//setPos(pos);

	

	b2Vec2 vec;

	vec.Set(st.velocidad.X, st.velocidad.Z);
	entity->getCuerpo2D()->SetLinearVelocity(vec);
	entity->getSombraE2D()->SetLinearVelocity(vec);
	st.posicion.X = entity->getCuerpo2D()->GetPosition().x;
	st.posicion.Z = entity->getCuerpo2D()->GetPosition().y;

	setPos(st.posicion);


}

Kinematic Enemigo::seek(const vector3df target)
{
	/*vector3df desireVelocity(0, 0, 0);

	desireVelocity = target - pos;

	desireVelocity = desireVelocity.normalize() * 55;
	float desireAngle = atan2f(-target.X, target.Z) * 180 / 3.14;
	maya->setRotation(vector3df(0, desireAngle - 90, 0));
*/

	
	float maxAcceleration = MULTIVEL * 2.5;
//	std::cout << "target  " << target.X << " " << target.Z << std::endl;
	sto.linear = target - st.posicion;
	//std::cout << "linear  " << sto.linear.X << " " << sto.linear.Z << std::endl;
	sto.linear = sto.linear.normalize();
	sto.linear *= maxAcceleration;

	float desireAngle = atan2f(-target.X, target.Z) * 180 / 3.14;
	maya->setRotation(vector3df(0, desireAngle - 90, 0));

	align(target);

	sto.angular = 0;
	
	Mover();

	return st;

}

Kinematic Enemigo::arrive(const vector3df target) {

	vector3df direction;
	float distance;
	float targetSpeed;
	vector3df targetVelocity;
	float timeTarget = 0.1;
	direction = target - st.posicion;
	//distance = direction.getLength();
	distance = sqrtf(powf(direction.X, 2) + powf(direction.Z, 2));

	float maxAcceleration = MULTIVEL * 2.5;

	if (distance < 5.0f)
	{
		//deberia se nulo
		targetSpeed = 0.0f;
	}

	if (distance > 40.0f)
	{
		targetSpeed = 55;
	}

	else
	{
		targetSpeed = 55 * distance / 10.0f;
	}
	
	targetVelocity = direction;
	targetVelocity = targetVelocity.normalize();
	targetVelocity *= targetSpeed;

	sto.linear = targetVelocity - st.velocidad;
	sto.linear = sto.linear /= timeTarget;

	float distancia = sqrtf(powf(sto.linear.X, 2) + powf(sto.linear.Z, 2));

	//std::cout << "DISTANCIA SIN Y: " << distancia << std::endl;

	//esto da la curva
	if (distancia > maxAcceleration)
	{
		sto.linear=sto.linear.normalize();
		sto.linear *= maxAcceleration;
	}

	sto.angular = 0;

	Mover();

	
	return st;

}

void Enemigo::align(const vector3df target){


	float targetRotation;
	float timeTarget = 0.1;

	float maxAngularAcceleration = MULTIVEL * 2.5;
	float maxRotation = 135.0f;
	float desireAngle = atan2f(-target.X, target.Z) * 180 / 3.14;
	float rotationSize;
	float rotation = desireAngle - st.orientacion;
	rotationSize = abs(rotation);

	if (rotationSize < 5.0f) //target radio
	{
		//deberia se nulo
		targetRotation = 0.0f;
	}

	if (rotationSize > 40.0f) //slow radio
	{
		targetRotation = maxRotation;
	}

	else
	{
		targetRotation = maxRotation * rotationSize / 10.0f;
	}


	targetRotation *= rotation / rotationSize;



	sto.angular = targetRotation - st.rotacion;
	sto.angular = sto.angular /= timeTarget;

	float angularAcceleration = abs(sto.angular);



	//esto da la curva
	if (angularAcceleration > maxAngularAcceleration)
	{
		sto.angular /= angularAcceleration;
		sto.angular *= maxAngularAcceleration;
	}

	//sto.linear = 0;
	
	maya->setRotation(vector3df(0, sto.angular, 0));

}

void Enemigo::collisionAvoidance(vector3df vecU) {

	float maxAcceleration = MULTIVEL * 1.25f;


	sto.linear = vecU * maxAcceleration;
//	std::cout<<"--> "<< sto.linear.X<<" "<< sto.linear.Z<<std::endl;
	Mover();
}

void Enemigo::obstacleAvoidance()
{

	float look = 50.0f;
	float avoidDistance = 70.0f; //cuanto mayor es el numero mas rapido esquivan
	float lim = -4.31602000;
	std::cout << "OBSTACLE!!" << std::endl;
	vector3df target(0, 0, 0);
	vector3df rayVector = st.velocidad;
	rayVector = rayVector.normalize();

	rayVector *= look;

	//std::cout << "RAYVECTOR" << std::endl;
	//std::cout << "X: " << rayVector.X << std::endl;
	//std::cout << "Y: " << rayVector.Y << std::endl;
	//std::cout << "Z: " << rayVector.Z << std::endl;
	//std::cout << "////////////////////////////" << std::endl;
	//std::cout << "POS ACTUAL" << std::endl;
	//std::cout << "X: " << st.posicion.X << std::endl;
	//std::cout << "Y: " << st.posicion.Y << std::endl;
	//std::cout << "Z: " << st.posicion.Z << std::endl;
	
	if(rayVector.X!=0 && rayVector.Z!=0)
	{
		float distansia = entity->rayCasting(b2Vec2(st.posicion.X, st.posicion.Z), b2Vec2(rayVector.X + st.posicion.X, rayVector.Z + st.posicion.Z));
		
		if(distansia != 0.0f) {
		
			std::cout << "PUNTO DE CHOQUE "<<this << std::endl;
			std::cout << "X: " << entity->getPuntoDeChoque().X << std::endl;
			std::cout << "Y: " << entity->getPuntoDeChoque().Y << std::endl;
			std::cout << "Z: " << entity->getPuntoDeChoque().Z << std::endl;
			target = entity->getPuntoDeChoque() + entity->getNormal() * avoidDistance;

			seek(target);
		}

	}


}


vector3df Enemigo::getPos() {
    return pos;
}

vector3df Enemigo::getVectorVel()
{
	return vecVel;
}

void Enemigo::setPos(vector3df pos) {

    maya->setPosition(pos);
}

float Enemigo::getVel() {
    return vel;
}

void Enemigo::setVelocidad() {

    if (entity->getSombraE2D() != NULL) {
        entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
        entity->getSombraE2D()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
		setPos(st.posicion);
		st.velocidad = vector3df(0, 0, 0);
		sto.linear = vector3df(0, 0, 0);
		sto.angular = 0.0f;

    }
}

void Enemigo::Patrullar() {


}

void Enemigo::Atacar(f32 dt)
{
}

void Enemigo::BuscarWaypoint()
{
}

bool Enemigo::estaVivo() {

    if (entity != NULL)
        return entity->getLive();
    else
        return false;

}

float Enemigo::getVida() {
    return vida;
}

void Enemigo::quitarVida(float damage) {


}

Entity2D* Enemigo::getEntity()
{
	return entity;
}

float Enemigo::getDamageChoque()
{
	return damageChoque;
}

void Enemigo::setEstado(int num)
{
	estadoActual = num;
}

int Enemigo::getEstado()
{
	return estadoActual;
}

void Enemigo::setDisparo(bool x)
{
	disparado = x;
}

void Enemigo::aumentarTiempoDisparo(float t)
{
	tiempoDisparo += t;
}

void Enemigo::resetTiempoDisparo()
{
	tiempoDisparo = 0.0f;
}

void Enemigo::setTime(f32 t) {
	time = t;
}

float Enemigo::getTiempoDisparo()
{
	return tiempoDisparo;
}

bool Enemigo::getDisparado()
{
	return disparado;
}

void Enemigo::disparar(float dt)
{
	tiempoDisparo += dt;
	disparado = true;
	Bala *bullet = new Bala(smgr1, VD, mundo, st.posicion, posJugador, damageBala, 2, 300.0f);
	listaBalas.push_back(bullet);

}

void Enemigo::actualizarLista()
{
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
				(*it)->moverEnemigoDisparo();
				//(*it)->update();
			}
		}
	}
}

void Enemigo::setPosJugador(float x, float y)
{
	posJugador.X = x;
	posJugador.Y = y;

	//std::cout << std::endl;
	//std::cout << "SET ENEMIGO" << std::endl;
	//std::cout << "POS X: " << posJugador.X << "POS Y(Z): " << posJugador.Y << std::endl;
	//std::cout << std::endl;

}

Nodo * Enemigo::getNodoInicio()
{
	return puntoIni;
}

Nodo * Enemigo::getNodoFin()
{
	return puntoFin;
}

void Enemigo::setPesoMaximoLogicaDifusa(float x)
{
	logica->setPesoMaximo(x);
}

void Enemigo::iniLogicaDifusa()
{
	//std::cout << std::endl;
	//std::cout << "ESTADO ANTES: " << std::endl;
	//std::cout << estadoActual << std::endl;
	//std::cout << std::endl;
	
	logica->fusificador(vida, st.posicion, posJugador, moral, resistencia);
	estadoActual = logica->getEstadoDecidido();

	//std::cout << std::endl;
	//std::cout << "ESTADO DESPUES: " << std::endl;
	//std::cout << estadoActual << std::endl;
	//std::cout << std::endl;
}



bool Enemigo::getVista()
{
	return vista;
}

void Enemigo::setVista(bool x)
{
	vista = x;
}

bool Enemigo::getEsquivarPared()
{
	return esquivarPared;
}

void Enemigo::setEsquivarPared(bool x)
{
	esquivarPared = x;
}

bool Enemigo::getVision()
{
	return vision;
}

void Enemigo::setVision(bool x)
{
	vision = x;
}

bool Enemigo::getLider()
{
	return floc->getLider();
}


void Enemigo::setGrupoFlocking(Entity2D *e) {
	floc->addEntity(e);
}

void Enemigo::deleteEntity(Entity2D *e) {
	floc->removeEntity(e);
}