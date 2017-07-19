/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   RayCastCallback.cpp
* Author: User
*
* Created on 9 de diciembre de 2016, 15:27
*/

#include <iostream>
#include <string>
#include "RayCastCallback.h"
#include "Entity2D.h"
//#include "../Escenario/Puerta.h"

RayCastCallback::RayCastCallback() {
	distancia = 0;
	//std::cout<<"ENTRO1 "<<std::endl;

}

RayCastCallback::RayCastCallback(const RayCastCallback& orig) {
}

RayCastCallback::~RayCastCallback() {
}

float32 RayCastCallback::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) {

	std::cout << "ENTRO AL CALLBACK " << std::endl;
	std::cout << "//////////////////////////////////////////" << std::endl;
	std::cout << "" << std::endl;

	if (fraction != 0) {
		void* bodyUserData = fixture->GetBody()->GetUserData();
		
		if (bodyUserData && fixture->IsSensor() == false) {
			if (static_cast<Entity2D*>(bodyUserData)) {
				Entity2D *entity = static_cast<Entity2D*>(bodyUserData);
				
				x = false;

				punto = point;
				nor = normal;

				std::cout << "//////////////////////////////////////////" << std::endl;

				std::cout << "ID ENTITY " << entity->getIDEN() << std::endl;
				std::cout << "Posicion de la Entity X: " << entity->getCuerpo2D()->GetPosition().x << " Y: " << entity->getCuerpo2D()->GetPosition().y << std::endl;
				std::cout << "//////////////////////////////////////////" << std::endl;
				std::cout << "" << std::endl;

				//hay que mirar si el objeto con el que choca el rayo es una puerta
				//que esta cerrada con llave no puede llegar a ese waypoint el enemigo
				//como su fuese una pared u otro objeto

				std::cout << "RAY DE CHOQUE" << std::endl;
				std::cout << "X: " << punto.x << std::endl;
				std::cout << "Y: " << punto.y << std::endl;
			//	std::cout << "Z: " << entity->getPuntoDeChoque().Z << std::endl;

			
				entidadChocada = entity->getIDEN();
				//if (punto.x <= -4.31602E8 && punto.y <= -4.31602E8) {
				////if (entidadChocada == 0) {
				//	std::cout << "HOOOOLIIIIIIS" << std::endl;
				//	punto = b2Vec2(0,0);
				//	nor = b2Vec2(0, 0);
				//}

				//if (entidadChocada == 2) {

				//	Puerta *p = static_cast<Puerta*>(entity->getObjeto3D());
				//	if (p->getEstado() == "BLOQLLAVE") {
				//		std::cout << "ESTOY CERRADA PAPITO" << std::endl;

				//		x = true;
				//		distancia = fraction;
				//		return fraction;
				//	}

				//}

			


				distancia = fraction;
				return fraction;

				

		/*		if (fraction < distancia || distancia == 0) {
					distancia = fraction;

					return fraction;

				}
				

				else {
					if (distancia == 0) {
						distancia = 0;
					}

					return -1;
				}*/

			}
		}
	}
	punto = point;
	nor = normal;
	return 0.0f;
}

float32 RayCastCallback::getDistancia() {
	return distancia;
}

int RayCastCallback::getEntidadChocada() {
	return entidadChocada;
}

bool RayCastCallback::getEsPuertaCerrada()
{
	return x;
}

b2Vec2 RayCastCallback::getNormal()
{
	return nor;
}

b2Vec2 RayCastCallback::getPuntoDeChoque()
{
	return punto;
}


