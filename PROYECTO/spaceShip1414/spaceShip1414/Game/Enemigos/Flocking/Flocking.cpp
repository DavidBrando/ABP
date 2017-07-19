

#include "Flocking.h"
#include "../Fisicas/Entity2D.h"
#include "../Enemigo.h"
#include <math.h>

Flocking::Flocking(bool x)
{
	lider = x;
	escala = 0.5f;
	distanciaSeparacion = 50.0f / 10.0f;
	distanciaSeparacion = powf(distanciaSeparacion, 2);
}


Flocking::~Flocking()
{
}

//estos metodos se les pasa por parametro la entity
//que quiere meterse en el flocking

glm::vec3 Flocking::cohesion(Entity2D * entity)
{

	glm::vec3 vectorU(0,0,0);
	glm::vec3 centroMasas(0, 0, 0);
	glm::vec3 pos(0, 0, 0);
	glm::vec3 posE(entity->getCuerpo2D()->GetPosition().x,
		0,
		entity->getCuerpo2D()->GetPosition().y);
	
	for (std::size_t i = 0; i < vecindario.size(); i++) {

		if (vecindario.at(i) != entity){

			pos.x = vecindario.at(i)->getCuerpo2D()->GetPosition().x;
			pos.y = 0;
			pos.z = vecindario.at(i)->getCuerpo2D()->GetPosition().y;

			centroMasas += pos;
		}

	}

	if(vecindario.size() > 0) {

		centroMasas = media(centroMasas, static_cast<int>(vecindario.size()));
		vectorU = centroMasas - posE;
		vectorU = glm::normalize(vectorU);
	}
	return vectorU;
}

glm::vec3 Flocking::alineacion(Entity2D * entity)
{

	glm::vec3 vectorU(0, 0, 0);
	glm::vec3 vel(0, 0, 0);
	glm::vec3 posE(entity->getCuerpo2D()->GetPosition().x,
		0,
		entity->getCuerpo2D()->GetPosition().y);

	for (std::size_t i = 0; i < vecindario.size(); i++) {

		if (vecindario.at(i) != entity) {

			Enemigo *e = static_cast<Enemigo*>(vecindario.at(i)->getObjeto3D());

			vel.x = vecindario.at(i)->getCuerpo2D()->GetLinearVelocity().x / e->getVel();
			vel.y = 0;
			vel.z = vecindario.at(i)->getCuerpo2D()->GetLinearVelocity().y / e->getVel();

			vectorU += vel;
		}

	}

	if (vecindario.size() > 0) {

		vectorU = media(vectorU, static_cast<int>(vecindario.size()));
		vectorU = glm::normalize(vectorU);
	}
	return vectorU;
}

glm::vec3 Flocking::separacion(Entity2D * entity)
{
	glm::vec3 vectorU(0, 0, 0);
	glm::vec3 pos(0, 0, 0);
	glm::vec3 posE(entity->getCuerpo2D()->GetPosition().x,
		0,
		entity->getCuerpo2D()->GetPosition().y);
	
	for (std::size_t i = 0; i < vecindario.size(); i++) {

		if (vecindario[i] != entity) {

			pos.x = vecindario.at(i)->getCuerpo2D()->GetPosition().x;
			pos.y = 0;
			pos.z = vecindario.at(i)->getCuerpo2D()->GetPosition().y;

			if (distanciaAlCuadrado(pos, posE) < distanciaSeparacion) {

				glm::vec3 handing = posE - pos;

				float dis = powf(handing.x, 2) + powf(handing.z, 2);

				float scale = dis / sqrtf(distanciaSeparacion);


				vectorU = glm::normalize(handing) / scale;
			}


		}

	}
	return vectorU;
	
}

void Flocking::colisionAvoidance(Entity2D *e) {

	float radio = 5.0f;
	float distance;
	float minSeparation;
	float shortestTime = INT_MAX*1.0f;

	Entity2D *firstEntity = nullptr;
	float fisrtMinSeparation = -1.0f;
	float fisrtDistance;
	glm::vec3 fisrtRelPos, fisrtRelVel;


	glm::vec3 posE(e->getCuerpo2D()->GetPosition().x,
			0,
			e->getCuerpo2D()->GetPosition().y);

	glm::vec3 velE(e->getCuerpo2D()->GetLinearVelocity().x,
			0,
			e->getCuerpo2D()->GetLinearVelocity().y);
	
	glm::vec3 pos, vel;
	//std::cout << "VEL-E" << std::endl;
	//std::cout << "X: " << velE.x<< std::endl;
	//std::cout << "Z: " << velE.z <<std::endl;

	/*vector3df posRel = e->st.posicion - this->st.posicion;
	vector3df velRel = e->st.velocidad - this->st.velocidad;*/

	glm::vec3 posRel(0,0,0);
	glm::vec3 velRel;

	float speedRel;

	for (std::size_t i = 0; i < vecindario.size(); i++) {

		if (vecindario[i] != e && vecindario[i]!=nullptr ) {


			pos.x = vecindario.at(i)->getCuerpo2D()->GetPosition().x;
			pos.y = 0;
			pos.z = vecindario.at(i)->getCuerpo2D()->GetPosition().y;

			vel.x = vecindario.at(i)->getCuerpo2D()->GetLinearVelocity().x;
			vel.y = 0;
			vel.z = vecindario.at(i)->getCuerpo2D()->GetLinearVelocity().y;


			//std::cout << "----VEL" << std::endl;
			//std::cout << "X: " << vel.x << std::endl;
			//std::cout << "Z: " << vel.z << std::endl;

			posRel = pos - posE;
			velRel = vel - velE;


			float x = powf(velRel.x, 2);
			float y = powf(velRel.z, 2);

			speedRel = sqrtf(x + y);


			float time = (glm::length(posRel)  * glm::length(velRel)) / (speedRel * speedRel);

			//std::cout << "TIME: " << time << std::endl;
			//std::cout << "shortestTime: " << shortestTime << std::endl;

			x = powf(posRel.x, 2);
			y = powf(posRel.z, 2);

			distance = sqrtf(x + y);

			minSeparation = abs( distance - speedRel * shortestTime);
			//std::cout << "MINSEP: " << minSeparation << std::endl;
			//std::cout << "RADIO: " << 2 * radio << std::endl;


			if (minSeparation > 2 * radio) {

				if (time > 0.0f && time < shortestTime) {
					shortestTime = time;
					firstEntity = vecindario[i];
					fisrtMinSeparation = minSeparation;
					fisrtDistance = distance;
					fisrtRelPos = posRel;
					fisrtRelVel = velRel;

				}
				//std::cout << "ENTRO CHINGON " << firstEntity << std::endl;
				if (firstEntity == nullptr) {

					static_cast<Enemigo*>(e->getObjeto3D())->collisionAvoidance(glm::vec3(0, 0, 0));

				}
				else
				{
					if (fisrtMinSeparation <= 0.0f || distance < 2 * radio) {

						//std::cout << "ENTRO" << std::endl;

						glm::vec3 posF(firstEntity->getCuerpo2D()->GetPosition().x,
							0,
							firstEntity->getCuerpo2D()->GetPosition().y);



							posRel = posF - posE;

									//std::cout << "POSREL1" << std::endl;
									//std::cout << "X: " << posRel.x << std::endl;
									//std::cout << "Y: " << posRel.y << std::endl;
									//std::cout << "Z: " << posRel.z << std::endl;



					}

					else {

						posRel = fisrtRelPos + fisrtRelVel * shortestTime;

						
					}

					posRel = glm::normalize(posRel);

					//std::cout << "POSREL2" << std::endl;
					//std::cout << "X: " << posRel.x << std::endl;
					//std::cout << "Y: " << posRel.y << std::endl;
					//std::cout << "Z: " << posRel.z << std::endl;

					if(i % 2 == 0)
						static_cast<Enemigo*>(e->getObjeto3D())->collisionAvoidance(posRel);

					else
						static_cast<Enemigo*>(e->getObjeto3D())->collisionAvoidance(-posRel);


				}
			}
		}
	
	}

	
}


void Flocking::cambiarEstadoSequito(Entity2D *e, int estado)
{

	for (std::size_t i = 0; i < vecindario.size(); i++) {

		 Enemigo *en = static_cast<Enemigo*>(e->getObjeto3D());

		 if(en->getLider() != true) {
			 en->setEstado(estado);
		 }

		
	}
}


bool Flocking::getLider()
{
	return lider;
}

void Flocking::setLider(bool x) {
	lider = x;
}

void Flocking::addEntity(Entity2D * e)
{
	vecindario.push_back(e);
}

void Flocking::removeEntity(Entity2D * e)
{

	for(std::size_t i = 0; i < vecindario.size(); i++) {
		if(vecindario.at(i) != nullptr && vecindario.at(i) == e) {
			vecindario.at(i) = nullptr;
		}

	}

}


glm::vec3 Flocking::media(glm::vec3 v, int cont)
{

	v.x / cont;
	v.z / cont;

	return v;
}

float Flocking::distanciaAlCuadrado(glm::vec3 u, glm::vec3 v)
{
	float dis;
	float x = u.x - v.x;
	float z = u.z - v.z;

	dis = powf(x, 2) + powf(z, 2);

	return dis;


}

