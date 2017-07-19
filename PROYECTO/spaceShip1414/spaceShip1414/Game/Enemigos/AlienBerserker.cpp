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
#include "BehaviorTree\BehaivorTree.h"
#include "../Fisicas/Mundo.h"
#include "../graphicEngine/TGraphicEngine.h"

#define RESISTMAX 120
#define VELMAX 30

AlienBerserker::AlienBerserker(TGraphicEngine* motor, Mundo* mundo, glm::vec3 posicion, Escenario* esce, Waypoints* puntos) : Enemigo(motor, mundo, posicion, puntos)
{



	//seria mejor que se le pasara las cosas necesarias del escenario que todo el escenario entero
	//para hacer el tema de los navmesehses y los waypoints

	nodo = motor->addMalla("resourse/models/Personajes/alienberserker/alienberserker.obj");

	motor->escalar(nodo, 1.0f, 1.0f, 1.0f);
	motor->trasladar(nodo, posicion.x, -5.0f, posicion.z); //esta en -5 mientras sea el nanosuit
	motor->rotarYPR(nodo, 180, 0, 0);
	rot = glm::vec3(180, 0, 0);

	vel = VELMAX;
	pos = posicion;
	//rot = maya->getRotation();
	vida = 100.0f;
	
	st.posicion = posicion;
	st.orientacion = 0;
	st.rotacion = 0;
	st.velocidad = glm::vec3(0, 0, 0);

	sto.angular = 0;
	sto.linear = glm::vec3(0, 0, 0);

	estadoActual = BUSCARPUNTO;
	raza = BERSERKER;
	blindaje = 5.0f;
	damageChoque = 15.0f;
	moral = 50.0f;
	resistencia = RESISTMAX;

	entity = new Entity2D(mundo->getWorldBox2D(), pos, true, this, raza);

	// nav = new navmeshes(10, esce);


	waypoints = puntos;
	logica = new LogicaDifusa(vida, moral, resistencia);
	// waypoints->creaPesos(entity);
	//waypoints->mostrarPesos();
	tree = new BehaivorTree();
	disparado = false;

	damageBala = 20.0f;



	//    std::cout << "GRAFO CON 0" << std::endl;
	//    std::cout << "" << std::endl;
	//    nav->muestraGrafo();
	//  std::cout << "COLISIONES" << std::endl;
	// std::cout << "" << std::endl;
	// nav->setColisiones(esce->getParedes());
	//nav->muestraGrafo();
	path = new AStar(waypoints->getMatriz(), waypoints->getNodos().size());
	floc = new Flocking(false);
	// dibujaGrid(smgr);
	//crearArbol();
	time = 0.0f;


}

//AlienBerserker::AlienBerserker(const AlienBerserker& orig) {
//}

AlienBerserker::~AlienBerserker() {

	delete(tree);


}

void AlienBerserker::Update(float dt)
{

	//crear metodos para todos los estados

	if (vista == true && estadoActual != FLOCKING && floc->getLider() != true) {
		floc->colisionAvoidance(entity);

	}

	if (esquivarPared) {
		obstacleAvoidance();
	}

	st.update(sto, dt);


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

		if (floc->getLider()) {
			floc->cambiarEstadoSequito(entity, FLOCKING);
		}

		break;

	case ATACAR: //atacar

		Atacar(dt);

		break;


	case DESCANSAR:

		setVelocidad();
		recuperarResistencia();
		if (resistencia >= RESISTMAX * 0.75) {

			vel = VELMAX;
			estadoActual = PATRULLAR;


		}


		break;

	case ROTACION:



		break;

	case ESCAPAR:

		iniLogicaDifusa();

		break;

	case CUERPOACUERPO:

		CQC();



		break;

	case FLOCKING:

		empezarFlocking(dt);



		break;

	}

	setPos(st.posicion);
	this->actualizarLista();


}


void AlienBerserker::Patrullar()
{

	if (puntoFin == nullptr) {

		posNodo = path->buscarWaypointMasCorto(posNodo);

		if (posNodo != -1) {
			puntoFin = waypoints->getNodoX(posNodo);


		}

		if (nodoAnterior == puntoFin) {


			posNodo = path->buscarWaypointNoRepetido(puntoFin->getLugarDelNodo(), puntoIni->getLugarDelNodo());
			puntoFin = waypoints->getNodoX(posNodo);


		}

		std::cout << std::endl;
		std::cout << "NOMBRE DEL DESTINO: " << this->puntoFin->getNombre() << std::endl;
		std::cout << "NUM: " << puntoFin->getLugarDelNodo() << std::endl;
		std::cout << "POS: " << glm::to_string(puntoFin->getPosicion()) << std::endl;

	}

	else if (puntoFin != nullptr) {


		if (path->distanciaEntreElNodoYEne(st.posicion, puntoFin->getPosicion()) < 20.0f) {

			arrive(puntoFin->getPosicion());

			if (path->distanciaEntreElNodoYEne(st.posicion, puntoFin->getPosicion()) < 5.0f
				|| path->distanciaEntreElNodoYEne(st.posicion, puntoFin->getPosicion()) < 10.0f)
			{

				dir = -1;

				nodoAnterior = puntoIni;
				puntoIni = puntoFin;
				puntoFin = nullptr;
			}
		}

		else {
			seek(puntoFin->getPosicion());
		}



	}

	/*std::cout << std::endl;
	std::cout << "PATRULLO PREMO!" << std::endl;
	std::cout << std::endl;*/

}

void AlienBerserker::Atacar(float dt)
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
	iniLogicaDifusa();

}

void AlienBerserker::CQC()
{

	//maya->getMaterial(0).EmissiveColor.set(0, 10, 250, 150);
	glm::vec3 posPlayer;
	posPlayer.x = posJugador.x;
	posPlayer.y = 0.0f;
	posPlayer.z = posJugador.y;
	//dir = path->getDireccion(pos, posPlayer);
	//this->Mover(dir);

	//vectorUnitario = path->getVectorDeDireccion(pos, posPlayer);
	seek(posPlayer);


	if (path->estoyEnElNodo(pos, posPlayer)) {
		dir = -1;
		this->setVelocidad();



		/*posNodo = path->buscarWaypointMasCorto(posNodo);
		puntoFin = waypoints->getNodoX(posNodo);*/

	}


	iniLogicaDifusa();

}

void AlienBerserker::empezarFlocking(float dt)
{
	//maya->getMaterial(0).EmissiveColor.set(0, 125, 50, 175);
	glm::vec3 u;
	float maxAngularAcceleration = MULTIVEL * PROPCURVA;

	//vector3df v(0, 0, 0);
	if (time < 1.5f) {

		u = floc->cohesion(entity);
		sto.linear = u * maxAngularAcceleration;
		Mover();

	}

	else {

		u = floc->separacion(entity);
		sto.linear = u * maxAngularAcceleration;
		Mover();

		u = floc->alineacion(entity);
		sto.linear = u * maxAngularAcceleration;
		Mover();

	}



	time += dt;

	//if (time > 5.0) {

	//u = floc->alineacion(entity);
	//vectorUnitario += u;
	//u = floc->cohesion(entity);
	//vectorUnitario = u;
	//u = floc->separacion(entity);
	//vectorUnitario += u;
	//time = 0.0f;
	//}
	//time += dt;
	//Mover(u);


}



void AlienBerserker::BuscarWaypoint()
{

	if (puntoIni == nullptr) {
		posNodo = path->buscarWaypointCercano(st.posicion, waypoints->getNodos());

		if (posNodo != -1) {
			puntoIni = waypoints->getNodoX(posNodo);
		}

		std::cout << std::endl;
		std::cout << "NOMBRE: " << this->puntoIni->getNombre() << std::endl;
		std::cout << "POS NODO: " << posNodo << std::endl;
	}



	if (puntoIni != nullptr) {

		//vectorUnitario = path->getVectorDeDireccion(pos, puntoIni->getPosicion());

		//	std::cout << "DISTANSIA QUE ME FUMO PARA LLEGAR AL NODO: " << path->distanciaEntreElNodoYEne(pos, puntoIni->getPosicion()) << std::endl;

		if (path->distanciaEntreElNodoYEne(st.posicion, puntoIni->getPosicion()) < 20.0f) {

			arrive(puntoIni->getPosicion());
			//std::cout << "DISTANSIA QUE ME FUMO PARA LLEGAR AL NODO: " << path->distanciaEntreElNodoYEne(pos, puntoIni->getPosicion()) << std::endl;


			if (path->distanciaEntreElNodoYEne(st.posicion, puntoIni->getPosicion()) < 5.0f
				|| path->distanciaEntreElNodoYEne(st.posicion, puntoIni->getPosicion()) < 10.0f
				|| path->estoyEnElNodo(st.posicion, puntoIni->getPosicion()))
			{

				estadoActual = PATRULLAR;

				dir = -1;
				//this->setVelocidad();

			}
		}

		else {
			seek(puntoIni->getPosicion());
		}

	}
}

void AlienBerserker::quitarVida(float damage) {

	std::cout << "BERSERKER!" << std::endl;

	vida = vida - (damage - blindaje);
	moral = moral - (damage * 0.35 - blindaje);
	if (moral < 0.0f)
		moral = 0.0f;

	resistencia = resistencia - damage * 0.35;

	vel = vel - resistencia * 0.15f;

	if (resistencia < 0.0f)
		resistencia = 0.0f;


	std::cout << vida << std::endl;
}


void AlienBerserker::recuperarResistencia()
{

	vida += 0.001f;
	resistencia += 0.001f;

}

void AlienBerserker::setLider(bool c)
{
	floc->setLider(c);
}

