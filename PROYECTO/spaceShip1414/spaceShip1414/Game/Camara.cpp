#include "Camara.h"
#include <iostream>
#include "../graphicEngine\TGraphicEngine.h"
#include "../graphicEngine\entityTree\TTransform.h"
#include "../graphicEngine\entityTree\TNodo.h"
#include "../graphicEngine\entityTree\TMalla.h"
#include "../graphicEngine\entityTree\TCamara.h"
#include "../graphicEngine\entityTree\TNodo.h"
#include "player.h"
#include <glm\gtx\string_cast.hpp>

//tipo 0 = librePerspectiva, 1 = jugadorPerspectiva, 2 = libreOrto, 3 = jugadorOrto 
Camara::Camara(TGraphicEngine * motorApp, char tipo, bool activa, player * jugador) : velocity{ 5.0f }, yaw{ 0 }, pitch{ 0 }
{
	switch (tipo)
	{
	case 0:
		nodo = motorApp->addCamaraLibre(activa);
		//motorApp->setCamaraMove(this);
		//motorApp->trasladar(nodo, 0, 10, -2.0f);
		break;
	case 1:
		nodo = motorApp->addCamaraPerspectivaSeguidora(activa, motorApp->getPadreX(jugador->getNodo()));
		//motorApp->setCamaraMove(this);

		break;
	case 2:
		nodo = motorApp->addCamaraParalelaFija(activa);
		motorApp->trasladar(nodo, 0, 10, -2.0f);
		break;
	case 3:
		nodo = motorApp->addCamaraParalelaSeguidora(activa, motorApp->getPadreX(jugador->getNodo()));
		break;
	default:
		std::cout << "Este tipo de camara no existe" << std::endl;
		break;
	}
}

Camara::Camara(TGraphicEngine * motorApp, int ident, bool activa, bool move, glm::vec3 pos, glm::vec3 rot, glm::vec3 escala) : velocity{ 5.0f }, yaw{ 0 }, pitch{ 0 }
{
	std::cout << "*******************ry:  " << rot.y << std::endl;
	nodo = motorApp->addCamaraPerspectivaFija(activa);
	motorApp->resetTransform(nodo, 'r');
	if (rot.y == 0 || rot.y == 180) {
		motorApp->rotarYPR(nodo, rot.y , 0.0f, 0.0f);
		yaw = rot.y;

	}
	
	else {
		motorApp->rotarYPR(nodo, rot.y - 180, 0.0f, 0.0f);
		yaw = rot.y - 180;
	}

	motorApp->trasladar(nodo, pos.x, pos.y, pos.z);
	p = pos;
	r = rot;
	
	anguloInicial = yaw;
	pitch = rot.x;
	rotX = rot.x;
	rotAnterior = anguloInicial;
	fija = move;
	id = ident;
	movil = false;
}

Camara::Camara(TGraphicEngine * motorApp, int ident, bool movimiento, glm::vec3 pos, glm::vec3 rot, glm::vec3 escala, player * jugador) : velocity{ 5.0f }, yaw{ 0 }, pitch{ 0 }
{
	nodo = motorApp->addCamaraPerspectivaSeguidora(false, motorApp->getPadreX(jugador->getNodo()));
	motorApp->resetTransform(nodo, 'r');
	if (rot.y == 0 || rot.y == 180) {
		motorApp->rotarYPR(nodo, rot.y, 0.0f, 0.0f);
		yaw = rot.y;

	}

	else {
		motorApp->rotarYPR(nodo, rot.y - 180, 0.0f, 0.0f);
		yaw = rot.y - 180;
	}

	motorApp->trasladar(nodo, pos.x, pos.y, pos.z);
	p = pos;
	r = rot;

	anguloInicial = yaw;
	movil = movimiento;
}


Camara::~Camara()
{
}


int Camara::getId()
{
	return id;
}


float Camara::getVelocity()
{
	return velocity;
}

float Camara::getYaw()
{
	return yaw;
}

float Camara::getPitch()
{
	return pitch;
}



void Camara::setVelocity(float v)
{
	velocity = v;
}

void Camara::setYaw(float y)
{
	yaw = y;
}

void Camara::setPitch(float p)
{
	pitch = p;
}


TCamara * Camara::getTCamara()
{
	return static_cast<TCamara*>(nodo->getEntidad());
}

TNodo * Camara::getNodo()
{
	return nodo;
}

bool Camara::getMovil()
{
	return movil;
}

void Camara::rotation(TGraphicEngine * motorApp, float a, float x, float y, float z)
{
	motorApp->rotar(nodo, a, x, y, z);
}

void Camara::rotationYPR(TGraphicEngine * motorApp, float y, float p, float r)
{
	motorApp->rotarYPR(nodo, y, p, r);
}

void Camara::scale(TGraphicEngine * motorApp, float x, float y, float z)
{
	motorApp->escalar(nodo, x, y, z);
}

void Camara::translation(TGraphicEngine * motorApp, float x, float y, float z)
{
	motorApp->trasladar(nodo, x, y, z);
}


float Camara::anguloEntreDosVectores(glm::vec3 u, glm::vec3 v) {

	float nominador = u.x * v.x + u.z * v.z;
	float x = (powf(u.x, 2)) + powf(u.z, 2);
	float y = (powf(v.x, 2)) + powf(v.z, 2);
	float moduloU = sqrtf(x);
	float moduloV = sqrtf(y);
	float denominador = moduloU * moduloV;

	if ((nominador / denominador) > 1.0f) {
		return yaw;
	}

	else {
		yaw = acosf((nominador / denominador)) * 180 / 3.14;
		return yaw;
	}
}


void Camara::updateCam(TGraphicEngine *motorApp, glm::vec3 posPers, int tecla) {

	

	//if (fija!=false)
	//{
	//	glm::vec3 u = posPers - p;
	//	float anguloRaton = atan2f(u.x, u.z) * 180 / 3.14f;
	//	float anguloX = acosf(u.y / u.x) * 180 / 3.14f;
	//	//glm::vec3 rotazione = motorApp->getRotacion(nodo);
	//	/*std::cout << "VEC: " << glm::to_string(u) << std::endl;
	//	std::cout << "ANGLEEEEE X: " << anguloX << std::endl;*/
	//		//motorApp->resetTransform(nodo, 'r');
	//	
	//	//para evitar que la camara gire mas de lo que debe
	//	if(tecla == 0 || tecla == 1) {
	//	
	//		rotAnterior = anguloRaton - 180;
	//		//motorApp->rotarYPR(nodo, rotAnterior, rotX, 0);

	//			if (rotAnterior < 0.0f) {
	//				rotAnterior += 360;
	//			}

	//			else if (rotAnterior > 360.0f) {
	//				rotAnterior -= 360;
	//			}

	//	}

	//	else if (tecla == 3) {

	//		rotX += 0.5;
	//		//rotAnterior = anguloRaton + 180;

	//		if (rotX > pitch) {
	//			rotX = pitch;
	//			
	//		//motorApp->rotarYPR(nodo, rotAnterior, rotX, 0);
	//		}
	//	}

	//	else if (tecla == 2) {

	//		rotX -= 0.5;
	//		//rotAnterior =  anguloRaton - 180;

	//		if (rotX < -75) {
	//			rotX = -75;
	//		}

	//		//motorApp->rotarYPR(nodo, rotAnterior, rotX, 0);
	//	}

	//		//motorApp->rotarYPR(nodo, rotAnterior, rotX, 0);
	//		motorApp->rotarYPR(nodo, rotAnterior, rotX, 0);


	//}

	//else
	//{
	//	motorApp->resetTransform(nodo, 'r');
	//	motorApp->rotarYPR(nodo, yaw - 180, pitch, 0);
	//}


	float distancia = 0;
	if (fija != false)
	{
		distancia =  p.x - posPers.x;
		//std::cout << "se lo dijisteh a la wah se lo dijisteh a mah, ya verah   " << distancia << std::endl;
		if(anguloInicial == 90.0f && id != 5) {
			if (distancia <= 150.0f) {
				motorApp->rotarYPR(this->getNodo(), posPers.z + anguloInicial, 0, 0);
			}

			else {
				motorApp->rotarYPR(this->getNodo(), posPers.z + anguloInicial, 0, 0);

			}
		}

		else if(anguloInicial == 180.0f) {
			
			if (distancia <= 150.0f) {
				motorApp->rotarYPR(this->getNodo(), posPers.x + (anguloInicial - 180), 0, 0); 
			}

			else {
				motorApp->rotarYPR(this->getNodo(), posPers.x + (anguloInicial - 180), 0, 0);

			}
		}

		else if (anguloInicial == 0.0f) {

			if (distancia <= 70.0f) {
				motorApp->rotarYPR(this->getNodo(), -posPers.x + (anguloInicial - 90), 0, 0);
			}

			else {
				motorApp->rotarYPR(this->getNodo(), posPers.z + (anguloInicial + 90), 0, 0);

			}
		}

		else if (r.y == 270.0f) {
			if (distancia <= 150.0f) {
				motorApp->rotarYPR(this->getNodo(), posPers.z + (anguloInicial + 180) , 0, 0);
			}

			else {
				motorApp->rotarYPR(this->getNodo(), posPers.z + (anguloInicial + 180), 0, 0);

			}
		}

	}
	else
	{
		motorApp->resetTransform(nodo, 'r');
		motorApp->rotarYPR(nodo, yaw, pitch, 0);
		
	}
}

float Camara::getAnguloInicial()
{
	return anguloInicial;
}

float Camara::getRotY() 
{
	return r.y;
}



