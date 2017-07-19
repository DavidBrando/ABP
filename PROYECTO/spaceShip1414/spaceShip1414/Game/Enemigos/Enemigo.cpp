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
//#include "../Jugador/Bala.h"
#include "LogicaDifusa.h"
#include "Flocking\Flocking.h"
#include "../graphicEngine/TGraphicEngine.h"




#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif




Enemigo::Enemigo(TGraphicEngine *motor, Mundo *m, glm::vec3 posicion, Waypoints * puntos)
{
		
	engine = motor;
	puntoIni = nullptr;
	puntoFin = nullptr;
	dir = -1;
	vista = false;

}

//Enemigo::Enemigo(const Enemigo& orig) {
//}

Enemigo::~Enemigo() {
 //   std::cout << "" << std::endl;

 //   std::cout << "////////////////////////" << std::endl;
 //   std::cout << "MUERE: " << maya << std::endl;
	//listaBalas.clear();
	//estadoActual = -1;
	//maya->getParent()->removeChild(maya);
 //   GVida->getParent()->removeChild(GVida);
 //   RVida->getParent()->removeChild(RVida);

	delete(path);
	delete(logica);
	/*delete(puntoIni);
	delete(puntoFin);*/
	delete(floc);
    delete(entity);
	puntoFin = nullptr;
	puntoIni = nullptr;
	engine->buscarNodoPadre(nodo);
	nodo = nullptr;
}

void Enemigo::Update(float dt) {

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

	vec.Set(st.velocidad.x, st.velocidad.z);
	entity->getCuerpo2D()->SetLinearVelocity(vec);
	//entity->getSombraE2D()->SetLinearVelocity(vec);
	st.posicion.x = entity->getCuerpo2D()->GetPosition().x;
	st.posicion.z = entity->getCuerpo2D()->GetPosition().y;

	if (raza == CRIA) {
		st.posicion.y = 0.0f;
	}

	setPos(st.posicion);


}

Kinematic Enemigo::seek(const glm::vec3 target)
{
	/*vector3df desireVelocity(0, 0, 0);

	desireVelocity = target - pos;

	desireVelocity = desireVelocity.normalize() * 55;
	float desireAngle = atan2f(-target.X, target.Z) * 180 / 3.14;
	maya->setRotation(vector3df(0, desireAngle - 90, 0));
*/

	
	float maxAcceleration = vel * PROPCURVA ;
//	std::cout << "target  " << target.X << " " << target.Z << std::endl;
	sto.linear = target - st.posicion;
	//std::cout << "linear  " << sto.linear.X << " " << sto.linear.Z << std::endl;
	sto.linear = glm::normalize(sto.linear);
	sto.linear *= maxAcceleration;

	float desireAngle = atan2f(-target.x, target.z) * 180 / 3.14f;
	//maya->setRotation(glm::vec3(0, desireAngle - 90, 0));

	align(target);

	sto.angular = 0;
	
	Mover();

	return st;

}

Kinematic Enemigo::arrive(const glm::vec3 target) {

	glm::vec3 direction;
	float distance;
	float targetSpeed;
	glm::vec3 targetVelocity;
	float timeTarget = 0.1f;
	direction = target - st.posicion;
	//distance = direction.getLength();
	distance = sqrtf(powf(direction.x, 2) + powf(direction.z, 2));

	float maxAcceleration = vel * PROPCURVA;

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

	targetVelocity = glm::normalize(targetVelocity);
	targetVelocity *= targetSpeed;

	sto.linear = targetVelocity - st.velocidad;
	sto.linear = sto.linear /= timeTarget;

	float distancia = sqrtf(powf(sto.linear.x, 2) + powf(sto.linear.z, 2));

	//std::cout << "DISTANCIA SIN Y: " << distancia << std::endl;

	//esto da la curva
	if (distancia > maxAcceleration)
	{
		
		sto.linear = glm::normalize(sto.linear);
		sto.linear *= maxAcceleration;
	}

	sto.angular = 0;
	//align(target);

	Mover();

	
	return st;

}

void Enemigo::align(const glm::vec3 target){


	float targetRotation;
	float timeTarget = 0.1f;

	float maxAngularAcceleration = vel * PROPCURVA;
	float maxRotation = 45.0f;
	float desireAngle = atan2f(-target.x, -target.z) * RADTODEG;
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

	if (desireAngle < 0.0f) {
		desireAngle += 360;
	}

	else if (desireAngle > 360) {
		desireAngle -= 360;
	}

	//sto.linear = 0;
	//std::cout << "---- ANGLE: " << sto.angular << std::endl;
	//maya->setRotation(vector3df(0, sto.angular, 0));
	/*
	Smooth rotazione
	Use setPosition to set the actual body angle to: body.angle = body.angle + (angleTarget - body.angle) * 0.05
	*/
	engine->resetTransform(nodo, 'r');
	engine->rotarYPR(nodo, desireAngle - 180, 0.0f, 0.0f);
	entity->getCuerpo2D()->SetTransform(entity->getCuerpo2D()->GetPosition(), (desireAngle ) * DEGTORAD);
	//entity->getCuerpo2D()->SetAngularVelocity(0.0f);
	//entity->getCuerpo2D()->SetAngularVelocity(sto.angular * DEGTORAD);
	std::cout << "--------> ANGLE CUERPO: " <<this<<" ---> "<<entity->getCuerpo2D()->GetAngle() * RADTODEG << std::endl;
	
}

void Enemigo::collisionAvoidance(glm::vec3 vecU) {

	float maxAcceleration = vel * (PROPCURVA * 0.5);


	sto.linear = vecU * maxAcceleration;
//	std::cout<<"--> "<< sto.linear.X<<" "<< sto.linear.Z<<std::endl;
	Mover();
}

//esquiva paredes
void Enemigo::obstacleAvoidance()
{

	float look = 10.0f;
	float avoidDistance = 30.0f; //cuanto mayor es el numero mas rapido esquivan
	float lim = -4.31602000f;
	std::cout << "OBSTACLE!!" << std::endl;
	glm::vec3 target(0, 0, 0);
	glm::vec3 rayVector = st.velocidad;

	rayVector = glm::normalize(rayVector);

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
	
	if(rayVector.x!=0 && rayVector.z!=0)
	{
		float distansia = entity->rayCasting(b2Vec2(st.posicion.x, -st.posicion.z), 
			b2Vec2(rayVector.x + st.posicion.x, -rayVector.z - st.posicion.z));
		
		if(distansia != 0.0f) {
		
			std::cout << "PUNTO DE CHOQUE "<<this << std::endl;
			std::cout << "X: " << entity->getPuntoDeChoque().x << std::endl;
			std::cout << "Y: " << entity->getPuntoDeChoque().y << std::endl;
			std::cout << "Z: " << entity->getPuntoDeChoque().z << std::endl;
			target = entity->getPuntoDeChoque() + entity->getNormal() * avoidDistance;

			seek(target);
		}

	}


}


glm::vec3 Enemigo::getPos() {
    return pos;
}

glm::vec3 Enemigo::getRot()
{
	return rot;
}

glm::vec3 Enemigo::getVectorVel()
{
	return vecVel;
}

void Enemigo::setPos(glm::vec3 p) {

    //maya->setPosition(pos);

	engine->resetTransform(this->getNodo(), 't');
	//setPos(entity->getCuerpo2D()->GetPosition().x, this->getPos().y, -entity->getCuerpo2D()->GetPosition().y);
	pos = p;
	engine->trasladar(this->getNodo(), entity->getCuerpo2D()->GetPosition().x, this->getPos().y, -entity->getCuerpo2D()->GetPosition().y);
	entity->getCuerpo2D()->SetAngularVelocity(0.0f);

}

float Enemigo::getVel() {
    return vel;
}

void Enemigo::setVelocidad() {

    
    entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
	entity->getCuerpo2D()->SetAngularVelocity(0.0f);
	setPos(st.posicion);
	st.velocidad = glm::vec3(0, 0, 0);
	sto.linear = glm::vec3(0, 0, 0);
	sto.angular = 0.0f;

    
}

void Enemigo::Patrullar() {


}

void Enemigo::Atacar(float dt)
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

void Enemigo::setTime(float t) {
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
	//tiempoDisparo += dt;
	//disparado = true;
	//Bala *bullet = new Bala(smgr1, VD, mundo, st.posicion, posJugador, damageBala, 2, 300.0f);
	//listaBalas.push_back(bullet);

}

void Enemigo::actualizarLista()
{
	//if (!listaBalas.empty()) {
	//	for (std::list<Bala*>::iterator it = listaBalas.begin(); it != listaBalas.end();) {
	//		if ((*it) != NULL) {
	//			if (!(*it)->estaViva()) {

	//				delete(*it);
	//				it = listaBalas.erase(it);
	//			}
	//			else
	//				it++;
	//		}
	//		else
	//			it++;
	//	}

	//	for (std::list<Bala*>::iterator it = listaBalas.begin(); it != listaBalas.end(); it++) {
	//		if ((*it) != NULL && (*it)->estaViva() == true) {
	//			(*it)->moverEnemigoDisparo();
	//			//(*it)->update();
	//		}
	//	}
	//}
}

void Enemigo::setPosJugador(float x, float y)
{
	posJugador.x = x;
	posJugador.y = y;

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
	std::cout << std::endl;
	std::cout << "ESTADO ANTES: " << std::endl;
	std::cout << estadoActual << std::endl;
	std::cout << std::endl;
	
	logica->fusificador(vida, st.posicion, posJugador, moral, resistencia);
	estadoActual = logica->getEstadoDecidido();

	std::cout << std::endl;
	std::cout << "ESTADO DESPUES: " << std::endl;
	std::cout << estadoActual << std::endl;
	std::cout << std::endl;
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

float Enemigo::getYaw()
{
	return yaw;
}

float Enemigo::getPitch()
{
	return pitch;
}

void Enemigo::rotation(TGraphicEngine * motorApp, float a, float x, float y, float z)
{
	motorApp->rotar(nodo, a, x, y, z);
}

void Enemigo::rotationYPR(TGraphicEngine * motorApp, float y, float p, float r)
{
	motorApp->rotarYPR(nodo, y, p, r);
}

void Enemigo::scale(TGraphicEngine * motorApp, float x, float y, float z)
{
	motorApp->escalar(nodo, x, y, z);
}

void Enemigo::translation(TGraphicEngine * motorApp, float x, float y, float z)
{
	motorApp->trasladar(nodo, x, y, z);
}

void Enemigo::setYaw(float y)
{
	yaw = y;
}

void Enemigo::setPitch(float p)
{
	pitch = p;
}

TNodo * Enemigo::getNodo()
{
	return nodo;
}
