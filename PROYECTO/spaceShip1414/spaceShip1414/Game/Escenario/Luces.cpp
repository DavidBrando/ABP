#include "Luces.h"
#include <iostream>
#include "..\graphicEngine\TGraphicEngine.h"
#include "..\graphicEngine\entityTree\TNodo.h"
#include "..\graphicEngine\entityTree\TLuz.h"


Luces::Luces(TGraphicEngine * motorApp, glm::vec3 tras, glm::vec3 r, glm::vec3 sca, int iden) : velocity{ 1.0f }
{

	

	pos = tras;

	if (iden==0)
	{
		nodo = motorApp->addLuz();
		motorApp->trasladar(nodo, tras.x, tras.y, tras.z);
		motorApp->rotarYPR(nodo, r.x, r.y, r.z);
		motorApp->escalar(nodo, sca.x, sca.y, sca.z);
		motorApp->addRegistroLuz(nodo);
	}
	ID = iden;
}

Luces::~Luces()
{
	std::cout << "Escenario::Luz delete" << std::endl;
	//delete nodo;
}


float Luces::getVelocity()
{
	return velocity;
}

void Luces::setVelocity(float v)
{
	velocity = v;
}

void Luces::activar()
{
	static_cast<TLuz*>(nodo->getEntidad())->activar();
}

void Luces::desactivar()
{
	static_cast<TLuz*>(nodo->getEntidad())->desactivar();
}

bool Luces::estaActiva()
{
	return static_cast<TLuz*>(nodo->getEntidad())->estaActiva();
}

bool Luces::esAmbiental()
{
	return static_cast<TLuz*>(nodo->getEntidad())->esAmbiental();
}

bool Luces::esPuntual()
{
	return static_cast<TLuz*>(nodo->getEntidad())->esPuntual();
}

bool Luces::esFocal()
{
	return static_cast<TLuz*>(nodo->getEntidad())->esFocal();
}

void Luces::setLocal(bool l)
{
	static_cast<TLuz*>(nodo->getEntidad())->setLocal(l);
}

void Luces::setFoco(bool f)
{
	static_cast<TLuz*>(nodo->getEntidad())->setFoco(f);
}

void Luces::setAmbient(float v[])
{
	static_cast<TLuz*>(nodo->getEntidad())->setAmbient(v);
}

void Luces::setColor(float v[])
{
	static_cast<TLuz*>(nodo->getEntidad())->setColor(v);
}

void Luces::setDireccionLuz(float v[])
{
	static_cast<TLuz*>(nodo->getEntidad())->setDireccionLuz(v);
}

void Luces::setDireccionCono(float v[])
{
	static_cast<TLuz*>(nodo->getEntidad())->setDireccionCono(v);
}

void Luces::setCosCutOffFoco(float f)
{
	static_cast<TLuz*>(nodo->getEntidad())->setCosCutOffFoco(f);
}

void Luces::setExponentFoco(float f)
{
	static_cast<TLuz*>(nodo->getEntidad())->setExponentFoco(f);
}

void Luces::setAtenuacionConstante(float f)
{
	static_cast<TLuz*>(nodo->getEntidad())->setAtenuacionConstante(f);
}

void Luces::setAtenuacionLiniar(float f)
{
	static_cast<TLuz*>(nodo->getEntidad())->setAtenuacionLiniar(f);
}

void Luces::setAtenuacionCuadratica(float f)
{
	static_cast<TLuz*>(nodo->getEntidad())->setAtenuacionCuadratica(f);
}

glm::vec3 Luces::getAmbient()
{
	return static_cast<TLuz*>(nodo->getEntidad())->getAmbient();
}

glm::vec3 Luces::getColor()
{
	return static_cast<TLuz*>(nodo->getEntidad())->getColor();
}

glm::vec3 Luces::getDireccionLuz()
{
	return static_cast<TLuz*>(nodo->getEntidad())->getDireccionLuz();
}

glm::vec3 Luces::getDireccionCono()
{
	return static_cast<TLuz*>(nodo->getEntidad())->getDireccionCono();
}

float Luces::getCosCutOffFoco()
{
	return static_cast<TLuz*>(nodo->getEntidad())->getCosCutOffFoco();
}

float Luces::getExponentFoco()
{
	return static_cast<TLuz*>(nodo->getEntidad())->getExponentFoco();
}

float Luces::getAtenuacionConstante()
{
	return static_cast<TLuz*>(nodo->getEntidad())->getAtenuacionConstante();
}

float Luces::getAtenuacionLiniar()
{
	return static_cast<TLuz*>(nodo->getEntidad())->getAtenuacionLiniar();
}

float Luces::getAtenuacionCuadratica()
{
	return static_cast<TLuz*>(nodo->getEntidad())->getAtenuacionCuadratica();
}

void Luces::rotation(TGraphicEngine * motorApp, float a, float x, float y, float z)
{
	motorApp->rotar(nodo, a, x, y, z);
}

void Luces::rotationYPR(TGraphicEngine * motorApp, float y, float p, float r)
{
	motorApp->rotarYPR(nodo, y, p, r);
}

void Luces::scale(TGraphicEngine * motorApp, float x, float y, float z)
{
	motorApp->rotarYPR(nodo, x, y, z);
}

void Luces::translation(TGraphicEngine * motorApp, float x, float y, float z)
{
	motorApp->rotarYPR(nodo, x, y, z);
	float v[3] = { x,y,z };
	static_cast<TLuz*>(nodo->getEntidad())->setDireccionLuz(v);
}

int Luces::getID()
{
	return ID;
}

glm::vec3 Luces::getPos()
{
	return pos;
}

TNodo* Luces::getNodo()
{
	return nodo;
}

