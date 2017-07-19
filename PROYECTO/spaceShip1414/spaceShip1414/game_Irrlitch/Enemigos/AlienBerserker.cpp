/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   AlienBerserker.cpp
* Author: David
*
* Created on 18 de enero de 2017, 16:50
*/

#include "AlienBerserker.h"
#include "Nodo.h"
#include "navmeshes.h"
#include "AStar.h"
#include "../Escenario/Escenario.h"
#include "../Fisicas/Entity2D.h"
#include "Waypoints.h"
#include "LogicaDifusa.h"
#include "Flocking\Flocking.h"

#define RESISTMAX 120
#define VELMAX 30

AlienBerserker::AlienBerserker(ISceneManager* smgr, IVideoDriver* driver, b2World *world, vector3df posicion, Waypoints* puntos) : Enemigo(smgr, driver, world, posicion, puntos)
{

	maya = smgr->addCubeSceneNode(10); //preguntar a Miguel Angel
	if (maya)
	{
		maya->setPosition(posicion);//vector3df(0, 10, 40)
		maya->getMaterial(0).EmissiveColor.set(0, 0, 230, 20);
	}

	vel = VELMAX;
	vida = 100.0f;
	pos = maya->getPosition();
	
	estadoActual = BUSCARPUNTO;
	raza = BERSERKER;
	blindaje = 5.0f;
	damageChoque = 15.0f;
	entity = new Entity2D(world, pos, true, this, smgr, raza);

	irr::core::stringw wideString(vida);
	GVida = smgr->addTextSceneNode(smgr->getGUIEnvironment()->getBuiltInFont(), wideString.c_str(), video::SColor(255, 255, 0, 0), 0);
	RVida = smgr->addTextSceneNode(smgr->getGUIEnvironment()->getBuiltInFont(), L"Vida: ", video::SColor(255, 255, 0, 0), 0);
	//napis a lo mejor estaria bien que estuviese en el .h de enemigo
	//tambien se tiene que borrar con el destructor
	GVida->setPosition(posicion);
	RVida->setPosition(vector3df(posicion.X - 64, posicion.Y, posicion.Z));

	smgr->getGUIEnvironment()->clear();

	resistencia = RESISTMAX;
	moral = 80;

	waypoints = puntos;
	logica = new LogicaDifusa(vida, moral, resistencia);
	// waypoints->creaPesos(entity);

	//waypoints->mostrarPesos();
	path = new AStar(waypoints->getMatriz(), waypoints->getNodos().size());
	floc = new Flocking(false);

	disparado = false;
	damageBala = 20.0f;
}

//AlienBerserker::AlienBerserker(const AlienBerserker& orig) {
//}

AlienBerserker::~AlienBerserker() {
}

void AlienBerserker::Update(f32 dt)
{

	//crear metodos para todos los estados
	switch (estadoActual) {

	case BUSCARPUNTO:

		BuscarWaypoint();

		break;

	case PATRULLAR: //patrullar

		Patrullar();
		if (vel < VELMAX * 0.5f) {
			setVelocidad();
			estadoActual = DESCANSAR;

		}

		break;

	case ATACAR: //atacar

		Atacar(dt);
		iniLogicaDifusa();

		break;


	case ROTACION:
		maya->getMaterial(0).EmissiveColor.set(0, 255, 50, 150);


		break;

	case DESCANSAR:

		setVelocidad();
		recuperarResistencia();
		if (resistencia >= RESISTMAX * 0.75) {

			vel = VELMAX;
			estadoActual = PATRULLAR;


		}


		break;


	case ESCAPAR:

		maya->getMaterial(0).EmissiveColor.set(0, 255, 50, 150);
		iniLogicaDifusa();

		break;

	case CUERPOACUERPO:

		CQC();

		break;
	}

	this->actualizarLista();
	GVida->setPosition(pos);
	RVida->setPosition(vector3df(pos.X - 8, pos.Y, pos.Z));

}

//void AlienBerserker::Mover(int modo)
//{
//
//}

void AlienBerserker::Patrullar()
{
	//maya->getMaterial(0).EmissiveColor.set(0, 15, 0, 200);
	if (puntoFin == nullptr) {

		posNodo = path->buscarWaypointMasCorto(posNodo);

		if (posNodo != -1) {
			puntoFin = waypoints->getNodoX(posNodo);


		}

		if (nodoAnterior == puntoFin) {


			posNodo = path->buscarWaypointNoRepetido(puntoFin->getLugarDelNodo(), puntoIni->getLugarDelNodo());
			puntoFin = waypoints->getNodoX(posNodo);


		}

		/*std::cout << std::endl;
		std::cout << "NOMBRE DEL DESTINO: " << this->puntoFin->getNombre() << std::endl;*/

	}

	else if (puntoFin != nullptr) {



		//dir = path->getDireccion(pos, puntoFin->getPosicion());
		//this->Mover(dir);
		vectorUnitario = path->getVectorDeDireccion(pos, puntoFin->getPosicion());

		
		if (path->estoyEnElNodo(pos, puntoFin->getPosicion())) {
			dir = -1;
			this->setVelocidad();

			nodoAnterior = puntoIni;
			puntoIni = puntoFin;
			puntoFin = nullptr;

			/*posNodo = path->buscarWaypointMasCorto(posNodo);
			puntoFin = waypoints->getNodoX(posNodo);*/

		}


	}

	/*std::cout << std::endl;
	std::cout << "PATRULLO PREMO!" << std::endl;
	std::cout << std::endl;*/

}

void AlienBerserker::Atacar(f32 dt)
{
	//maya->getMaterial(0).EmissiveColor.set(0, 255, 50, 0);
	/*		std::cout << std::endl;
	std::cout << "CRIA ALIEN" << std::endl;
	std::cout << "POS X: " << posJugador.X << "POS Y(Z): " << posJugador.Y << std::endl;
	std::cout << std::endl;*/

	if (disparado == false) {

		this->disparar(dt); //donde crea la bala

	}


	if (disparado == true) {
		this->aumentarTiempoDisparo(dt);
		if (this->getTiempoDisparo() >= 0.7f) {
			this->setDisparo(false);
			this->resetTiempoDisparo();
		}
	}

	this->setVelocidad();
}

void AlienBerserker::CQC()
{

	//maya->getMaterial(0).EmissiveColor.set(0, 10, 250, 150);
	vector3df posPlayer;
	posPlayer.X = posJugador.X;
	posPlayer.Y = 0.0f;
	posPlayer.Z = posJugador.Y;
	//dir = path->getDireccion(pos, posPlayer);
	//this->Mover(dir);

	vectorUnitario = path->getVectorDeDireccion(pos, posPlayer);

	seek(posPlayer);


	if (path->estoyEnElNodo(pos, posPlayer)) {
		dir = -1;
		this->setVelocidad();



		/*posNodo = path->buscarWaypointMasCorto(posNodo);
		puntoFin = waypoints->getNodoX(posNodo);*/

	}


	iniLogicaDifusa();

}


void AlienBerserker::BuscarWaypoint()
{
	//maya->getMaterial(0).EmissiveColor.set(0, 0, 200, 10);

	if (puntoIni == nullptr) {
		posNodo = path->buscarWaypointCercano(pos, waypoints->getNodos());

		if (posNodo != -1) {
			puntoIni = waypoints->getNodoX(posNodo);
		}

		//	std::cout << std::endl;
		//std::cout << "NOMBRE: " << this->puntoIni->getNombre() << std::endl;
		//std::cout << "POS NODO: " << posNodo << std::endl;
	}



	if (puntoIni != nullptr) {
		//dir = path->getDireccion(pos, puntoIni->getPosicion());
		/*	std::cout << std::endl;
		std::cout << "DIR: " << dir << std::endl;
		std::cout << std::endl;*/

		//	this->Mover(dir);
		vectorUnitario = path->getVectorDeDireccion(pos, puntoIni->getPosicion());


		if (path->estoyEnElNodo(pos, puntoIni->getPosicion())) {
			estadoActual = PATRULLAR;

			dir = -1;
			this->setVelocidad();

		}
	}
}

void AlienBerserker::quitarVida(float damage) {

	std::cout << "BERSERKER!" << std::endl;

	vida = vida - (damage - blindaje);
	irr::core::stringw wideString(vida);
	GVida->setText(wideString.c_str());

	std::cout << vida << std::endl;
}

void AlienBerserker::recuperarResistencia()
{

	maya->getMaterial(0).EmissiveColor.set(0, 250, 200, 10);

	vida += 0.001f;
	resistencia += 0.001f;
	irr::core::stringw wideString(vida);
	GVida->setText(wideString.c_str());
}

