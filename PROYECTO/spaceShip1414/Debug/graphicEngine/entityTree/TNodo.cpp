#include "TNodo.h"
#include <iostream>
#include "TEntidad.h"
#include "..\framework\openGLShader.h"
#include "..\Fisicas\Mundo.h"

int TNodo::id = 0;

TNodo::TNodo()
{
	padre = nullptr;
	entidad = nullptr;
	idN = id++;
}

TNodo::TNodo(TEntidad *e)
{
	padre = nullptr;
	if (e != nullptr) {
		entidad = e;
	}
	else {
		entidad = nullptr;
	}
	idN = id++;
}

TNodo::TNodo(TNodo *p, TEntidad *e)
{
	if (p != nullptr) {
		if (!p->addHijo(this))
		{
			padre = nullptr;
		}
	}
	else {
		padre = nullptr;
	}
	if (e != nullptr) {
		entidad = e;
	}
	else {
		entidad = nullptr;
	}
	idN = id++;
}


TNodo::~TNodo()
{
	if(entidad != nullptr){
		delete entidad;
		entidad = nullptr;
	}
	if (hijos.size() > 0) {
		for (std::vector<TNodo*>::iterator it = hijos.begin(); it != hijos.end(); ++it)
		{
			if(*it != nullptr){
				delete *it;
			}
		}
		hijos.erase(hijos.begin(), hijos.end());
	}
	std::cout << "Nodo eliminado" << std::endl;
}

bool TNodo::addHijo(TNodo* n)
{
	if (n != nullptr)
	{
		this->hijos.push_back(n);
		n->setPadre(this);
		return true;
	}
	return false;
}

void TNodo::setPadre(TNodo* n)
{
	this->padre = n;
}

int TNodo::removeHijo(TNodo* n)
{
	for (std::vector<TNodo*>::iterator it = this->hijos.begin(); it != this->hijos.end(); ++it)
	{
		if (*it == n)
		{
			hijos.erase(it);
			delete *it;
			return 1;
		}
	}
	return 0;
}

bool TNodo::setEntidad(TEntidad* e)
{
	if (e != nullptr)
	{
		this->entidad = e;
		return true;
	}
	return false;
}

TEntidad* TNodo::getEntidad()
{
	return this->entidad;
}

TNodo* TNodo::getPadre()
{
	return this->padre;
}

int TNodo::getID()
{
	return idN;
}

void TNodo::draw()
{
	if (this->entidad) {
		this->entidad->beginDraw();
	}
	for (std::vector<TNodo*>::iterator it = this->hijos.begin(); it != this->hijos.end(); ++it) {
		(*it)->draw();
	}
	if (this->entidad) {
		this->entidad->endDraw();
	}
}

void TNodo::draw(openGLShader& s, const glm::mat4& w, const glm::mat4& pro, Mundo * world)
{
	if (this->entidad) {
		this->entidad->beginDraw(s,w,pro);
	}
	for (std::vector<TNodo*>::iterator it = this->hijos.begin(); it != this->hijos.end(); ++it) {
		
		(*it)->draw(s, w, pro, world);

	}
	if (this->entidad) {
		this->entidad->endDraw();
	}
	
}
