#include "player.h"
#include "../graphicEngine\TGraphicEngine.h"
#include "../graphicEngine\entityTree\TNodo.h"
#include "../graphicEngine\entityTree\TCamara.h"
#include "../graphicEngine\entityTree\TAnimacion.h"
#include "MaquinaEstados\FSM\MaquinaEstados.h"
#include "MaquinaEstados\FSM\Estados.h"
#include "Jugador\Inventario.h"
#include "Jugador\Bala.h"
#include "Jugador/Pistola.h"
#include "Jugador/Escopeta.h"

#include "Escenario\ObjConsumables\Botiquines.h"

#ifndef ENTITY2D_GUARD
#define ENTITY2D_GUARD
#include "../Fisicas\Entity2D.h"
#endif
#ifndef MUNDO_GUARD
#define MUNDO_GUARD
#include "../Fisicas\Mundo.h"
#endif
#include <iostream>
#include <math.h>

#define PI 3.14159265
#define PISTOL 0
#define SHOTGUN 1

player::player(TGraphicEngine * motorApp, Mundo *m) : velocity{ 70.0f }, yaw{ 0 }, pitch{ 0 }, victoria{ false }
{
	engine = motorApp;
	anguloCamara = 90.0f; //para hacer que rote con la camara
	vida = 100.0f;
	vidaMax = vida;
	initEstados();
	load_personaje();
	motorApp->escalar(nodo, 0.75f, 0.75f, 0.75f);
	motorApp->trasladar(nodo, 0.0f, 0.0f, 0.0f);
	motorApp->rotarYPR(nodo, 0, 0, 0);
	//animation = motorApp->addAnimacion(andar->getPathAnimacion(), 25);
	//motorApp->escalar(animation, 0.75f, 0.75f, 0.75f);
	//motorApp->trasladar(animation, 0.0f, 0.0f, 0.0f);
	//motorApp->rotarYPR(animation, 0, 0, 0);
	//animation->destruirEntidad();
	pos = glm::vec3(0, 0, 0);
	rot = glm::vec3(180, 0, 0);
	escale = glm::vec3(0.75f, 0.75f, 0.75f);

	pistol = new Pistola();
	shotgun = new Escopeta();

	armaActual = -1;
	cargador = pistol->getCargador();
	municionTotal = pistol->getCapacidadDeMun();


	vecDir, vecA, vecD, vecS = glm::vec3(0, 0, 0);
	entity = new Entity2D(m->getWorldBox2D(), glm::vec3(0,0,0), rot, this);
	//motorApp->setPlayerMove(this);
	inv = new Inventario();
	movimiento = "andar";
}

void player::rotation(TGraphicEngine * motorApp, float a, float x, float y, float z)
{
	motorApp->rotar(nodo, a, x, y, z);
}

void player::rotationYPR(TGraphicEngine * motorApp, float y, float p, float r)
{
	motorApp->rotarYPR(nodo, y, p, r);
}

void player::scale(TGraphicEngine * motorApp, float x, float y, float z)
{
	motorApp->escalar(nodo, x, y, z);
}

void player::translation(TGraphicEngine * motorApp, float x, float y, float z)
{
	motorApp->trasladar(nodo, x, y, z);
}

void player::initEstados()
{
	MaquinaEstadosAnimation = new MaquinaEstados();
	andar = new Estados("andar");
	andar->asignarPath("resourse/animations/Personaje/AndarFix/");
	reposoAndar = new Estados("reposoAndar");
	reposoAndar->asignarPath("resourse/animations/Personaje/AndarFix/reposo.obj");
	pistola = new Estados("pistola");
	pistola->asignarPath("resourse/animations/Personaje/AndarPistolaFix/r");
	reposoPistola = new Estados("reposoPistola");
	reposoPistola->asignarPath("resourse/animations/Personaje/AndarPistolaFix/reposop.obj");
	disparar = new Estados("disparar");
	disparar->asignarPath("resourse/animations/Personaje/Disparar/");
	escopeta = new Estados("escopeta");
	escopeta->asignarPath("resourse/animations/Personaje/AndarEscopetaFix/e");
	reposoEscopeta= new Estados("reposoEscopeta");
	reposoEscopeta->asignarPath("resourse/animations/Personaje/AndarEscopetaFix/ereposo.obj");
	MaquinaEstadosAnimation->addEstado(andar);
	MaquinaEstadosAnimation->addEstado(reposoAndar, true);
	MaquinaEstadosAnimation->addEstado(reposoPistola);
	MaquinaEstadosAnimation->addEstado(pistola);
	MaquinaEstadosAnimation->addEstado(disparar);
	MaquinaEstadosAnimation->addEstado(reposoEscopeta);
	MaquinaEstadosAnimation->addEstado(escopeta);
}

void player::deleteEstados()
{
	delete andar;
	delete reposoAndar;
	delete reposoPistola;
	delete pistola;
	delete disparar;
	delete MaquinaEstadosAnimation;
}

player::~player()
{
	delete(entity);
	delete inv;
	deleteEstados();
}

float player::getVelocity()
{
	return velocity;
}

float player::getYaw()
{
	return yaw;
}

float player::getPitch()
{
	return pitch;
}

void player::setVelocity(float v)
{
	velocity = v;
}

void player::setYaw(float y)
{
	yaw = y;
}

void player::setPitch(float p)
{
	pitch = p;
}

glm::vec3 player::getPos()
{
	return pos;
}

glm::vec3 player::getRot()
{
	return rot;
}

glm::vec3 player::getScale()
{
	return escale;
}

int player::getDireccion()
{
	return dir;
}

void player::setPos(float x, float y, float z)
{
	pos.x = x; pos.y = y; pos.z = z;
}

void player::setRot(float x, float y, float z)
{
	rot.x = x; rot.y = y; rot.z = z;
}

void player::setScale(float x, float y, float z)
{
	escale.x = x; escale.y = y; escale.z = z;
}

void player::cambiarAnimacion(char c) {

	switch (c)
	{

	case 'r': //reposo
		std::cout << "REPOSO" << std::endl;
		if (movimiento == "andar")
		{
			MaquinaEstadosAnimation->cambiaEstado("reposoAndar");
			NPistola->noDraw(false);
			Nandar->noDraw(false);
			NreposoPistola->noDraw(false);
			NreposoEscopeta->noDraw(false);
			NEscopeta->noDraw(false);
			nodo = NreposoAndar;
			
			
		}
		if (movimiento == "pistola")
		{
			MaquinaEstadosAnimation->cambiaEstado("reposoPistola");
			NPistola->noDraw(false);
			Nandar->noDraw(false);
			NreposoAndar->noDraw(false);
			NreposoEscopeta->noDraw(false);
			NEscopeta->noDraw(false);
			nodo = NreposoPistola;
		}

		if (movimiento == "escopeta")
		{
			MaquinaEstadosAnimation->cambiaEstado("reposoEscopeta");
			NPistola->noDraw(false);
			Nandar->noDraw(false);
			NreposoAndar->noDraw(false);
			NreposoPistola->noDraw(false);
			NEscopeta->noDraw(false);
			nodo = NreposoEscopeta;
		}
		
		//engine->rotarYPR(nodo, 27.0f, 0.0f, 0.0f);
		break;

	case 'a': //andar
		std::cout << "ANDAR" << std::endl;
		MaquinaEstadosAnimation->cambiaEstado("andar");
		NPistola->noDraw(false);
		NreposoAndar->noDraw(false);
		NreposoPistola->noDraw(false);
		NreposoEscopeta->noDraw(false);
		NEscopeta->noDraw(false);
		nodo = Nandar;

		break;

	case 'c': //pistola
		MaquinaEstadosAnimation->cambiaEstado("pistola");
		Nandar->noDraw(false);
		NreposoAndar->noDraw(false);
		NreposoPistola->noDraw(false);
		NreposoEscopeta->noDraw(false);
		NEscopeta->noDraw(false);
		nodo = NPistola;

		break;

	case 'd': //disparar

		break;
	case 'e': //escopeta
		MaquinaEstadosAnimation->cambiaEstado("escopeta");
		Nandar->noDraw(false);
		NreposoAndar->noDraw(false);
		NreposoPistola->noDraw(false);
		NPistola->noDraw(false);
		NreposoEscopeta->noDraw(false);
		nodo = NEscopeta;

		break;

	default:
		//animacion de andar
		break;
	}
}

void player::actualizarFisicas(int n, double delta, float anguloCam)
{
	b2Vec2 vel(0,0);
	glm::vec3 rotaton = engine->getRotacion(nodo);
	dir = n;

	//std::cout << "VALORS DE N: " << n << std::endl;
	//if (n != -1 && MaquinaEstadosAnimation->getEstadoActivo()->getEstado() != andar->getEstado())
	//{
	//	cambiarAnimacion('a');
	//}

	//std::cout << "VECTORES ACTU" << std::endl;
	//std::cout << "DIR: "<< glm::to_string(vecDir) << std::endl;
	//std::cout << "A: "<<glm::to_string(vecA) << std::endl;
	//std::cout << "S: "<< glm::to_string(vecS) << std::endl;
	//std::cout <<"D:"<< glm::to_string(vecD) << std::endl;

	//if (anguloCamara == 90.0f || anguloCam == 270.0f)
	//	anguloCam -= 180.0f;

	if(n == -1)
	{
		entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
		if (MaquinaEstadosAnimation->getEstadoActivo()->getEstado() != reposoAndar->getEstado()) {
			cambiarAnimacion('r');
			//engine->resetTransform(nodo, 'r');

			//engine->rotarYPR(nodo, anguloCamara - 90, 0.0f, 0.0f);
			nodo->noDraw(true);
		}
		if (recalculo == true)
		{
			//std::cout << "HORA DEL RECALCULO" << std::endl;
			asignarVectorDirector(vecDir, anguloCamara);
			setRecalculo(false);
			//engine->resetTransform(this->getNodo(), 'r');
			//engine->rotarYPR(nodo, rotaton.y, 0.0f, 0.0f);
		}
	
	}
	if (n == 0)
	{
		vel.Set(vecD.x, vecD.z);
		vel = velocity * vel;
		engine->resetTransform(nodo, 'r');
		engine->rotarYPR(nodo, anguloCamara - 90, 0.0f, 0.0f);
		rotAnt = anguloCamara - 90;
		vecAux = vecD;
		//entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(velocity, 0.0f));
		if (movimiento == "andar")
		{
			cambiarAnimacion('a');

			nodo->noDraw(true);
		}
		else if (movimiento == "pistola")
		{
			cambiarAnimacion('c');
			nodo->noDraw(true);
		}
		else if (movimiento == "escopeta")
		{
			cambiarAnimacion('e');
			nodo->noDraw(true);
		}
	}
	if (n == 1)
	{
		vel.Set(vecA.x, vecA.z);
		vel = velocity * vel;
		engine->resetTransform(nodo, 'r');
		engine->rotarYPR(nodo, anguloCamara + 90, 0.0f, 0.0f);
		rotAnt = anguloCamara + 90;

		vecAux = vecA;
		if (movimiento == "andar")
		{
			cambiarAnimacion('a');

			nodo->noDraw(true);
		}
		else if (movimiento == "pistola")
		{
			cambiarAnimacion('c');
			nodo->noDraw(true);
		}
		else if (movimiento == "escopeta")
		{
			cambiarAnimacion('e');
			nodo->noDraw(true);
		}
		//entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(-velocity, 0.0f));
	}
	if (n == 2)
	{
		vel.Set(vecS.x, vecS.z);
		vel = velocity * vel;
		engine->resetTransform(nodo, 'r');
		engine->rotarYPR(nodo, anguloCamara + 180, 0.0f, 0.0f);
		rotAnt = anguloCamara + 180;

		vecAux = vecS;
		if (movimiento == "andar")
		{
			cambiarAnimacion('a');

			nodo->noDraw(true);
		}
		else if (movimiento == "pistola")
		{
			cambiarAnimacion('c');
			nodo->noDraw(true);
		}
		else if (movimiento == "escopeta")
		{
			cambiarAnimacion('e');
			nodo->noDraw(true);
		}
		//entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(0.0f, -velocity));
	}
	if (n == 3)
	{
		vel.Set(vecDir.x, vecDir.z);
		vel = velocity * vel;
		engine->resetTransform(nodo, 'r');
		engine->rotarYPR(nodo, anguloCamara, 0.0f, 0.0f);
		rotAnt = anguloCamara;
		vecAux = vecDir;
		if (movimiento == "andar")
		{
			cambiarAnimacion('a');

			nodo->noDraw(true);
		}
		else if (movimiento == "pistola")
		{
			cambiarAnimacion('c');
			nodo->noDraw(true);
		}
		else if (movimiento == "escopeta")
		{
			cambiarAnimacion('e');
			nodo->noDraw(true);
		}
		//entity->getCuerpo2D()->SetLinearVelocity(b2Vec2(0.0f, velocity));
	}

	if (n == 4)
	{
		cambiarAnimacion('a');
		movimiento = "andar";
	}


	if (n == 5)
	{
		cambiarAnimacion('c');
		movimiento = "pistola";
	}

	if (n == 6)
	{
		cambiarAnimacion('e');
		movimiento = "escopeta";
	}

	entity->getCuerpo2D()->SetLinearVelocity(vel);
	actualizarPosicion();
	//engine->resetTransform(this->getNodo(), 't');
	//setPos(-entity->getCuerpo2D()->GetPosition().x, this->getPos().y, -entity->getCuerpo2D()->GetPosition().y);
	//engine->trasladar(this->getNodo(), entity->getCuerpo2D()->GetPosition().x, this->getPos().y, -entity->getCuerpo2D()->GetPosition().y);
}

void player::setCamPos(glm::vec3 p)
{
	posCam = p;
}

TNodo * player::getNodo()
{
	return nodo;
}

void player::asignarVectorDirector(glm::vec3 u, float angle)
{
	vecDir = u;
	anguloCamara = angle;
	//std::cout << "ANGLEEEEE: " << angle << std::endl;
	//std::cout << angle + 90 << std::endl;
	//std::cout << angle + 180 << std::endl;
	//std::cout << angle - 90 << std::endl;
	float angulo = (90) * PI / 180;
	vecA = glm::vec3(vecDir.x * cos(angulo) - vecDir.z * sin(angulo),
					0, vecDir.x * sin(angulo) + vecDir.z * cos(angulo));
	angulo = (180) * PI / 180;
	vecS = glm::vec3(vecDir.x * cos(angulo) - vecDir.z * sin(angulo),
					0, vecDir.x * sin(angulo) + vecDir.z * cos(angulo));
	angulo = (- 90) * PI / 180;
	vecD = glm::vec3(vecDir.x * cos(angulo) - vecDir.z * sin(angulo),
					0, vecDir.x * sin(angulo) + vecDir.z * cos(angulo));
	//std::cout << "VECTORES" << std::endl;
	//std::cout << "DIR: "<< glm::to_string(vecDir) << std::endl;
	//std::cout << "A: "<<glm::to_string(vecA) << std::endl;
	//std::cout << "S: "<< glm::to_string(vecS) << std::endl;
	//std::cout <<"D:"<< glm::to_string(vecD) << std::endl;

}

void player::actualizarPosicion()
{	
	
	std::cout << "POS ANTES DEL PUTO JUGADOR: " << glm::to_string(engine->getPosicion(nodo)) << std::endl;
	engine->resetTransform(this->getNodo(), 't');

	setPos(entity->getCuerpo2D()->GetPosition().x, this->getPos().y, -entity->getCuerpo2D()->GetPosition().y);
//	std::cout << "POS 2D DEL PUTO JUGADOR DEPSUES: " << entity->getCuerpo2D()->GetPosition().x << ", " << -entity->getCuerpo2D()->GetPosition().y << std::endl;
	engine->trasladar(this->getNodo(), entity->getCuerpo2D()->GetPosition().x, this->getPos().y, -entity->getCuerpo2D()->GetPosition().y);
	std::cout << "POS DESPUES DEL PUTO JUGADOR: " << glm::to_string(engine->getPosicion(nodo)) << std::endl;

}

void player::iniciarTiempoImpulso() {

	temporizador = 4.0f;

}

void player::disminuirTem()
{
	temporizador -= 0.5f;
}

float player::getTemporizador()
{
	return temporizador;
}

void player::setImpulso(bool x)
{
	impulso = x;
}

void player::destruirAnimacion(TNodo* n)
{
	n->destruirEntidad();
}

bool player::getImpulso() {
	return impulso;
}

void player::setAnguloCamara(float angle)
{
	anguloCamara = angle;
}

void player::setRecalculo(bool x)
{
	recalculo = x;
}

void player::setVectorDirector(glm::vec3 u)
{
	vecDir = u;
}

void player::setTeclaE(bool x)
{
	teclaE = x;
}

void player::setTeclaQ(bool x)
{
	teclaQ = x;
}

bool player::getTeclaE()
{
	return teclaE;
}

bool player::getTeclaQ()
{
	return teclaQ;
}

void player::quitarVida(float damage)
{
	std::cout << std::endl;
	std::cout << "VIDA ANTES: " << vida << std::endl;
	vida -= damage;
	std::cout << std::endl;
	std::cout << "VIDA DESPUES: " << vida << std::endl;
}

void player::curar(float recup)
{
	vida += recup;
}

void player::usarBotiquin()
{
	Botiquines *bot = static_cast<Botiquines*>(inv->usarObjeto(0));
	if (bot != nullptr) {
		float dif = vidaMax - vida;
		if (dif >= bot->getVida()) {
			curar(bot->getVida());
			inv->deleteObj(bot);
		}
		else if (vida != vidaMax) {
			curar(dif);
			inv->deleteObj(bot);
		}
		else {
			std::cout << std::endl;
			std::cout << "TIENES LA VIDA MAX " << std::endl;
			std::cout << std::endl;
		}
	}
	else {
		std::cout << std::endl;
		std::cout << "NO TIENES BOTIQUINES " << std::endl;
		std::cout << std::endl;
	}
}

float player::getVida()
{
	return vida;
}

float player::getPorcentajeVida()
{
	return vida / vidaMax;
}

Inventario * player::getInventario()
{
	return inv;
}

float player::getTiempoDisparo()
{
	return tiempoDisparo;
}

void player::setTiempoDisparo(float x)
{
	tiempoDisparo = x;
}

void player::setDisparo(bool x)
{
	disparo = x;
}

bool player::getDisparo()
{
	return disparo;
}

void player::actualizarLista(float dt)
{
	if (!listaBalas.empty()) {
		for (std::list<Bala*>::iterator it = listaBalas.begin(); it != listaBalas.end();) {
			if ((*it) != NULL) {
				if (!(*it)->estaViva()) {

					delete(*it);
					it = listaBalas.erase(it);
				}
				else
					it++;
			}
			else
				it++;
		}

		for (std::list<Bala*>::iterator it = listaBalas.begin(); it != listaBalas.end(); it++) {
			if ((*it) != NULL && (*it)->estaViva() == true) {
				(*it)->mover();
				//(*it)->update();
			}
		}
	}
}

void player::Disparar(Mundo * w, float dt)
{
	if(armaActual != -1)
	{
		std::cout << "CARGADOR: " << cargador << std::endl;
		tiempoDisparo += dt;
		disparo = true;
		//glm::vec3 caca = engine->getRotacion(nodo);
	
		Bala *bullet = new Bala(engine, w, pos, vecAux, getDamage(), 1, 600.0f, rotAnt);
		//Bala::Bala(TGraphicEngine * motorApp, Mundo *world, glm::vec3 posPers, glm::vec3 mousePosition,
		//	float dumug, int tipo, float velocidad) {
		listaBalas.push_back(bullet);
		cargador--;
	}

}

int player::getCargador()
{
	return cargador;
}

int player::getMunicionActual()
{
	return municionTotal;
}

float player::getDamage()
{
	switch (armaActual) {

	case 0:
		return pistol->getDamage();
		break;

	case 1:
		return shotgun->getDamage();
		break;

	}
}

float player::getTiempoArma()
{
	switch (armaActual) {

	case 0:
		return pistol->getTiempoDisparo();
		break;

	case 1:
		return shotgun->getTiempoDisparo();
		break;

	}
}

int player::getArmaActual()
{
	return armaActual;
}

void player::recargar()
{
	//restar de la recarga al total de balas que se tiene actualmente
	int recarga;

	switch (armaActual) {

	case 0:
		recarga = pistol->getCargador() - cargador;

		break;

	case 1:
		recarga = shotgun->getCargador() - cargador;

		break;

	}


	cargador += recarga;
	municionTotal -= recarga;
}

void player::cogerMunicion(int municionCogida, int arma)
{
	//usar armaActual para el switch
	//municionTotal += municionCogida;
	int auxMunicion;

	switch (arma) {

	case 0:

		auxMunicion = pistol->getCapacidadDeMun();
		auxMunicion += municionCogida;

		if (auxMunicion > pistol->getTotalMunicion()) {
			auxMunicion = pistol->getTotalMunicion();
		}

		pistol->setCapacidadDeMun(auxMunicion);

		if (arma == armaActual) {
			municionTotal = auxMunicion;
		}


		break;

	case 1:

		auxMunicion = shotgun->getCapacidadDeMun();
		auxMunicion += municionCogida;

		if (auxMunicion > shotgun->getTotalMunicion()) {
			auxMunicion = shotgun->getTotalMunicion();
		}

		shotgun->setCapacidadDeMun(auxMunicion);

		if (arma == armaActual) {
			municionTotal = auxMunicion;
		}

		break;

	}
}

void player::setArmaActual(int newArma)
{
	//habria que poner tambien el de total de municion del arma actual (llamar al seter)
	//y devolver tambien el cargador total del arma
	switch (armaActual) {

	case 0:

		pistol->setMunicionAcutal(cargador);
		pistol->setCapacidadDeMun(municionTotal);

		break;

	case 1:

		shotgun->setMunicionAcutal(cargador);
		shotgun->setCapacidadDeMun(municionTotal);
		break;

	}

	std::cout << "" << std::endl;
	std::cout << "ARMA: " << armaActual << std::endl;
	std::cout << "MUNICION TOTAL: " << municionTotal << std::endl;
	std::cout << "" << std::endl;


	armaActual = newArma;

	switch (armaActual) {

	case 0:
		std::cout << "CAMBIO A PISTOLA " << armaActual << std::endl;
		cargador = pistol->getMunicionActual();
		municionTotal = pistol->getCapacidadDeMun();

		break;


	case 1:

		std::cout << "CAMBIO A ESCOPETA " << armaActual << std::endl;
		cargador = shotgun->getMunicionActual();
		municionTotal = shotgun->getCapacidadDeMun();


		break;



	}
	std::cout << "" << std::endl;
	std::cout << "ARMA CAMBIADA: " << armaActual << std::endl;
	std::cout << "MUNICION TOTAL: " << municionTotal << std::endl;
	std::cout << "" << std::endl;
}

void player::load_personaje()
{

	NreposoAndar = engine->addMalla(reposoAndar->getPathAnimacion());
	nodo = NreposoAndar;
	nodo->noDraw(true);
	godfather = nodo->getPadre();
	Nandar = engine->addAnimacion(andar->getPathAnimacion(), 8, godfather);
	Nandar->noDraw(false);
	NPistola = engine->addAnimacion(pistola->getPathAnimacion(), 8, godfather);
	NPistola->noDraw(false);
	NreposoPistola = engine->addMalla(reposoPistola->getPathAnimacion(), godfather);
	NreposoPistola->noDraw(false);
	NreposoEscopeta = engine->addMalla(reposoEscopeta->getPathAnimacion(), godfather);
	NreposoEscopeta->noDraw(false);
	NEscopeta = engine->addAnimacion(escopeta->getPathAnimacion(), 8, godfather);
	NEscopeta->noDraw(false);
}

void player::victory()
{
	victoria = true;
}

bool player::getVictory()
{
	return victoria;
}
