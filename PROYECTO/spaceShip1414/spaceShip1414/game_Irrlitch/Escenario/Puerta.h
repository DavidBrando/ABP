#pragma once
/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   Puerta.h
* Author: David
*
* Created on 15 de diciembre de 2016, 20:03
*/
#include <irrlicht.h>
#include <Box2D\Box2D.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifndef PUERTA_H
#define PUERTA_H


class Entity2D;
class MaquinaEstados;
class Estados;

class Puerta {
public:

	Puerta(int ident, vector3df posicion, vector3df rotacion, vector3df escala, IMeshSceneNode *objeto, std::string llave);
	Puerta(const Puerta& orig);
	virtual ~Puerta();

	vector3df getPosicion();
	vector3df getRotacion();
	vector3df getEscala();
	bool getAbierta();
	bool getTotalAbierta();
	void setPosicion(vector3df newPos);
	void setRotacion(vector3df newRot);
	void setEscala(vector3df newEscala);
	void setDetectado(bool x,int ident);
	void setFisica(b2World *world , ISceneManager* smgr, int ident);
	void setAbierta();
	void setCerrada();
	void abrirPuerta();
	void cerrarPuerta();
	void Update();
	void UpdateEstado();
	bool getDetectado();
	std::string getEstado();
	std::string getLlaveAsociada();

private:
	int id;
	vector3df pos;
	vector3df posIni;
	vector3df rot;
	vector3df escal;
	Entity2D *entity;
	IMeshSceneNode *maya;
	bool abierta=false;
	int estadoActual;
	float limiteApX;
	float limiteApZ;
	bool abrir;
	bool detectado;
	int idDetect;
	MaquinaEstados* Maquina;
	Estados* ABIERTA;
	Estados* CERRADA;
	Estados* BLOQUEADA;
	Estados* BLOQLLAVE;
	std::string llaveAsociada;
};

#endif /* PUERTA_H */

