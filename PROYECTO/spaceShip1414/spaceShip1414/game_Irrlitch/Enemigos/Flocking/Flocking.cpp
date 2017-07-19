

#include "Flocking.h"
#include "../../Fisicas/Entity2D.h"
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

vector3df Flocking::cohesion(Entity2D * entity)
{

	vector3df vectorU(0,0,0);
	vector3df centroMasas(0, 0, 0);
	vector3df pos(0, 0, 0);
	vector3df posE(entity->getCuerpo2D()->GetPosition().x,
		0,
		entity->getCuerpo2D()->GetPosition().y);
	
	for (std::size_t i = 0; i < vecindario.size(); i++) {

		if (vecindario.at(i) != entity){
			pos.set(vecindario.at(i)->getCuerpo2D()->GetPosition().x,
				0,
				vecindario.at(i)->getCuerpo2D()->GetPosition().y);
			centroMasas += pos;
		}

	}

	if(vecindario.size() > 0) {

		centroMasas = media(centroMasas, vecindario.size());
		vectorU = centroMasas - posE;
		vectorU = vectorU.normalize();
	}
	return vectorU;
}

vector3df Flocking::alineacion(Entity2D * entity)
{

	vector3df vectorU(0, 0, 0);
	vector3df vel(0, 0, 0);
	vector3df posE(entity->getCuerpo2D()->GetPosition().x,
		0,
		entity->getCuerpo2D()->GetPosition().y);

	for (std::size_t i = 0; i < vecindario.size(); i++) {

		if (vecindario.at(i) != entity) {

			Enemigo *e = static_cast<Enemigo*>(vecindario.at(i)->getObjeto3D());

			vel.set(vecindario.at(i)->getCuerpo2D()->GetLinearVelocity().x / e->getVel(),
				0,
				vecindario.at(i)->getCuerpo2D()->GetLinearVelocity().y / e->getVel());

			vectorU += vel;
		}

	}

	if (vecindario.size() > 0) {

		vectorU = media(vectorU, vecindario.size());
		vectorU = vectorU.normalize();
	}
	return vectorU;
}

vector3df Flocking::separacion(Entity2D * entity)
{
	vector3df vectorU(0, 0, 0);
	vector3df pos(0, 0, 0);
	vector3df posE(entity->getCuerpo2D()->GetPosition().x,
		0,
		entity->getCuerpo2D()->GetPosition().y);
	
	for (std::size_t i = 0; i < vecindario.size(); i++) {

		if (vecindario[i] != entity) {
			pos.set(vecindario.at(i)->getCuerpo2D()->GetPosition().x,
				0,
				vecindario.at(i)->getCuerpo2D()->GetPosition().y);
			if (distanciaAlCuadrado(pos, posE) < distanciaSeparacion) {

				vector3df handing = posE - pos;

				float dis = powf(handing.X, 2) + powf(handing.Z, 2);

				float scale = dis / sqrtf(distanciaSeparacion);

				vectorU = handing.normalize() / scale;
			}


		}

	}
	return vectorU;
	
}

void Flocking::colisionAvoidance(Entity2D *e) {

	float radio = 5.0f;
	float distance;
	float minSeparation;
	float shortestTime = INT_MAX;

	Entity2D *firstEntity = nullptr;
	float fisrtMinSeparation = -1.0f;
	float fisrtDistance;
	vector3df fisrtRelPos, fisrtRelVel;


		vector3df posE(e->getCuerpo2D()->GetPosition().x,
			0,
			e->getCuerpo2D()->GetPosition().y);

		vector3df velE(e->getCuerpo2D()->GetLinearVelocity().x,
			0,
			e->getCuerpo2D()->GetLinearVelocity().y);
	
	vector3df pos, vel;
	//std::cout << "VEL-E" << std::endl;
	//std::cout << "X: " << velE.X<< std::endl;
	//std::cout << "Z: " << velE.Z <<std::endl;

	/*vector3df posRel = e->st.posicion - this->st.posicion;
	vector3df velRel = e->st.velocidad - this->st.velocidad;*/

	vector3df posRel(0,0,0);
	vector3df velRel;

	float speedRel;

	for (std::size_t i = 0; i < vecindario.size(); i++) {

		if (vecindario[i] != e && vecindario[i]!=nullptr ) {



			pos.set(vecindario.at(i)->getCuerpo2D()->GetPosition().x,
				0,
				vecindario.at(i)->getCuerpo2D()->GetPosition().y);


			vel.set(vecindario.at(i)->getCuerpo2D()->GetLinearVelocity().x,
				0,
				vecindario.at(i)->getCuerpo2D()->GetLinearVelocity().y);


			//std::cout << "----VEL" << std::endl;
			//std::cout << "X: " << vel.X << std::endl;
			//std::cout << "Z: " << vel.Z << std::endl;

			posRel = pos - posE;
			velRel = vel - velE;


			float x = powf(velRel.X, 2);
			float y = powf(velRel.Z, 2);

			speedRel = sqrtf(x + y);


			float time = (posRel.getLength() * velRel.getLength()) / (speedRel * speedRel);

			//std::cout << "TIME: " << time << std::endl;
			//std::cout << "shortestTime: " << shortestTime << std::endl;

			x = powf(posRel.X, 2);
			y = powf(posRel.Z, 2);

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

					static_cast<Enemigo*>(e->getObjeto3D())->collisionAvoidance(vector3df(0, 0, 0));

				}
				else
				{
					if (fisrtMinSeparation <= 0.0f || distance < 2 * radio) {

						//std::cout << "ENTRO" << std::endl;

						vector3df posF(firstEntity->getCuerpo2D()->GetPosition().x,
							0,
							firstEntity->getCuerpo2D()->GetPosition().y);



							posRel = posF - posE;

									//std::cout << "POSREL1" << std::endl;
									//std::cout << "X: " << posRel.X << std::endl;
									//std::cout << "Y: " << posRel.Y << std::endl;
									//std::cout << "Z: " << posRel.Z << std::endl;



					}

					else {

						posRel = fisrtRelPos + fisrtRelVel * shortestTime;

						
					}

					posRel = posRel.normalize();

					//std::cout << "POSREL2" << std::endl;
					//std::cout << "X: " << posRel.X << std::endl;
					//std::cout << "Y: " << posRel.Y << std::endl;
					//std::cout << "Z: " << posRel.Z << std::endl;

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
			vecindario.at(i) == nullptr;
		}

	}

}


vector3df Flocking::media(vector3df v, int cont)
{

	v.X / cont;
	v.Z / cont;

	return v;
	
}

float Flocking::distanciaAlCuadrado(vector3df u, vector3df v)
{
	float dis;
	float x = u.X - v.X;
	float z = u.Z - v.Z;

	dis = powf(x, 2) + powf(z, 2);

	return dis;


}

