/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   Juego.cpp
* Author: Hector
*
* Created on 19 de diciembre de 2016, 22:22
*/



#include "Juego.h"
#include "Jugador\Personaje.h"
#include "Escenario/Escenario.h"
#include "Escenario/Camara.h"
#include "Escenario/readJson.h"
#include "Fisicas/MiContactListener.h"
#include "Fisicas/MyContactFilter.h"
#include "Menu/Menu.h"
#include "EstadoGeneral.h"

#include "ManejadorEstadoGeneral.h"

#define ANCHO 1920
#define LARGO 1080

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

Juego::Juego() {

}

Juego::Juego(std::string name) : EstadoGeneral(name) {
}

Juego::~Juego() {
}

void Juego::StarUP(IrrlichtDevice* iDevice) {
	iDevice->setEventReceiver(&teclado);
	driver = iDevice->getVideoDriver();
	smgr = iDevice->getSceneManager();
	guienv = iDevice->getGUIEnvironment();
	world = new b2World(gravity);
	contactListenerInstance = new MiContactListener();
	filtroContact = new MyContactFilter();
	gravity.Set(0.0f, 0.0f);

	world->SetContactListener(contactListenerInstance);
	world->SetContactFilter(filtroContact);

	iDevice->setWindowCaption(L"Movimiento del personaje");

	guienv->addStaticText(L"Movimiento del personaje",
		rect<s32>(10, 10, 260, 22), true); //metodo para poner algo por pantalla
										   //cambiar la camara activa smgr->setActiveCamera(camera);
	lastFPS = 0;
	 //el cubo que se crea es de 10x10x10 10px = 1m
	esce = new Escenario(smgr, driver, world,this);

	pers = esce->getPersonaje();
	// ene = new Enemigo(smgr, driver, world, vector3df(0,10,40));
	json = new readJson(esce);
	//esce->fabricaDeEnemigos(smgr, driver, world);

	cam = new Camara(smgr, pers->getPos());

	then = iDevice->getTimer()->getTime();
	estado = 0;
	para = false;
}

void Juego::Dentro(void) {
	//set up gui
}

void Juego::Fuera(void) {
	//restore playerdata
}

bool Juego::OnEvent(const SEvent &event) {
	//handle user input
	return (false);
}

void Juego::update(int state) {
	estado = state;
}

void Juego::mover(f32 dt)
{
	cam->actualizarCamara(pers->getPos(), pers->getRot(), dt);
	if(pers->getImpulso() == false) {

	if (!teclado.isKeyDown(irr::KEY_KEY_D) || !teclado.isKeyDown(irr::KEY_KEY_A) || !teclado.isKeyDown(irr::KEY_KEY_W) || !teclado.isKeyDown(irr::KEY_KEY_S)) {
		pers->setVelocidad();
	}

	if (teclado.isKeyDown(irr::KEY_KEY_W) && teclado.isKeyDown(irr::KEY_KEY_D)) {

		pers->moverPersonaje(4, dt);
		
		//cam->actualizarCamara(pers->getPos(), pers->getRot(), dt);

		//cam->actualizarCamara(0, dt);
		//cam->actualizarCamara(2, dt);
	}
	else if (teclado.isKeyDown(irr::KEY_KEY_S) && teclado.isKeyDown(irr::KEY_KEY_D)) {

		pers->moverPersonaje(5, dt);
		//cam->actualizarCamara(pers->getPos(), pers->getRot(), dt);

		// cam->actualizarCamara(0, dt);
		//cam->actualizarCamara(3, dt);

	}
	else if (teclado.isKeyDown(irr::KEY_KEY_S) && teclado.isKeyDown(irr::KEY_KEY_A)) {

		pers->moverPersonaje(6, dt);
		//cam->actualizarCamara(pers->getPos(), pers->getRot(), dt);

		// cam->actualizarCamara(1, dt);
		// cam->actualizarCamara(3, dt);


	}
	else if (teclado.isKeyDown(irr::KEY_KEY_A) && teclado.isKeyDown(irr::KEY_KEY_W)) {

		pers->moverPersonaje(7, dt);
		//cam->actualizarCamara(pers->getPos(), pers->getRot(), dt);

		// cam->actualizarCamara(1, dt);
		// cam->actualizarCamara(2, dt);


	}// X + and -
	else if (teclado.isKeyDown(irr::KEY_KEY_D)) {

		pers->moverPersonaje(0, dt);
	//	cam->actualizarCamara(pers->getPos(), pers->getRot(), dt);

		//   cam->actualizarCamara(0, dt);

	}
	else if (teclado.isKeyDown(irr::KEY_KEY_A)) {

		pers->moverPersonaje(1, dt);
	//	cam->actualizarCamara(pers->getPos(), pers->getRot(), dt);

		//cam->actualizarCamara(1, dt);

	}//Z + and -
	else if (teclado.isKeyDown(irr::KEY_KEY_W)) {

		pers->moverPersonaje(2, dt);
		//cam->actualizarCamara(pers->getPos(), pers->getRot(), dt);

		//cam->actualizarCamara(2, dt);
	}
	else if (teclado.isKeyDown(irr::KEY_KEY_S)) {

		pers->moverPersonaje(3, dt);
	//	cam->actualizarCamara(pers->getPos(), pers->getRot(), dt);

		//cam->actualizarCamara(3, dt);

	}
	
	}
	else {
		pers->disminuirTem();
		if(pers->getTemporizador() == 0.0f) {
			pers->setImpulso(false);

		}

	}

	pers->actualizarPosicion();
	cam->actualizarCamara(pers->getPos(), pers->getRot(), dt);
}


void Juego::recargar()
{
	//comprobar que si no tienes balas no puedes recargar mas
	if (teclado.isKeyDown(irr::KEY_KEY_R) && pers->getMunicionActual() > 0) {
		pers->recargar();

		if(pers->getMunicionActual() < 0) {
			std::cout << "No puedes recagar, no te quedan balas" << std::endl;
		}	
	}
	

}

void Juego::pausa(IrrlichtDevice* iDevice)
{
	if (teclado.isKeyDown(irr::KEY_ESCAPE)) {
		update(1);
		menuPausa = new Menu(iDevice, 0);
	}
}

void Juego::cambioarma()
{

	if (teclado.isKeyDown(irr::KEY_KEY_1)) {
		if (pers->getArmaActual() != 0)
			pers->setArmaActual(0);
	}
	else if (teclado.isKeyDown(irr::KEY_KEY_2)) {
		if (pers->getArmaActual() != 1)
			pers->setArmaActual(1);
	}
	else if (teclado.isKeyDown(irr::KEY_KEY_3)) {
		if (pers->getArmaActual() != 2)
			pers->setArmaActual(2);
	}
}

void Juego::raton(f32 dt)
{
	//RATON
	vector3df mousePosition;
	// Create a ray through the mouse cursor.
	line3df ray = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(teclado.GetMouseState().Position, smgr->getActiveCamera());
	// And intersect the ray with a plane around the node facing towards the camera.
	plane3df plane(mousePosition, vector3df(0, 0, -1));
	bool ok = plane.getIntersectionWithLine(ray.start, ray.getVector(), mousePosition);
	mousePosition.X = teclado.GetMouseState().Position.X;
	mousePosition.Y = teclado.GetMouseState().Position.Y;
	pers->rotar(mousePosition);
	//if (teclado.isKeyDown(irr::KEY_KEY_E)) {
	//	std::cout << "//////////////////////////////////////////" << std::endl;
	//	std::cout << "" << std::endl;
	//	std::cout << "POS EPRS" << std::endl;
	//	std::cout << "PosX: " << pers->getPos().X << "PosZ: " << pers->getPos().Z << std::endl;
	//}
	if (teclado.GetMouseState().LeftButtonDown && pers->getDisparo() == false) {

		
		//mirar esta parte para el enemigo vaya disparando (posiblemente sea en el callback de colisiones
		if (pers->getCargador() >= 0) {
			pers->disparar(smgr, driver, world, dt, vector2df(mousePosition.X, mousePosition.Y));

		}
	}


	if (pers->getDisparo() == true) {
		pers->setTiempoDisparo(pers->getTiempoDisparo() + dt);
		if (pers->getTiempoDisparo() >= pers->getTiempoArma()) {
			pers->setDisparo(false);
			pers->setTiempoDisparo(0);
		}
	}
	if (ok) {

		pers->actualizarLista(dt);

	}



}

void Juego::accionesDeTeclado() {

	if (teclado.isKeyDown(irr::KEY_KEY_E) && pers->getTeclaE() == false) {
		std::cout << "CAMBIO ESTADO TRUE" << std::endl;
		pers->setTeclaE(true);
	}

	if (!teclado.isKeyDown(irr::KEY_KEY_E) && pers->getTeclaE() == true) {
		std::cout << "CAMBIO ESTADO FALSE" << std::endl;
		pers->setTeclaE(false);
	}

	if (teclado.isKeyDown(irr::KEY_KEY_Q) && pers->getTeclaQ() == false) {
		std::cout << "CAMBIO ESTADO TRUE" << std::endl;
		pers->setTeclaQ(true);
		pers->usarBotiquin();
	}

	if (!teclado.isKeyDown(irr::KEY_KEY_Q) && pers->getTeclaQ() == true) {
		std::cout << "CAMBIO ESTADO FALSE" << std::endl;
		pers->setTeclaQ(false);
	}

}


void Juego::render(IrrlichtDevice* iDevice) {
	
	if (control == false) {


		this->StarUP(iDevice);
		control = true;
	}
	//    std::cout<<estado<<std::endl;
	if (iDevice->isWindowActive()) {


		const u32 now = iDevice->getTimer()->getTime();

		const f32 dt = (f32)(now - then) / 1000.f;
		//float distancia;
		world->Step(dt, 6, 2); //1.0f/60.0f
		world->ClearForces();
		


		switch (estado)
		{
		case 0: {
			//mover camara y personaje
			this->mover(dt);
			//recarga
			this->recargar();
			//pausa
			this->pausa(iDevice);
			//cambio de arma
			this->cambioarma();
			
			accionesDeTeclado();

			/*
			if(teclado.isKeyDown(irr::KEY_KEY_Q) && now >= 5.0f){
			esce->spawnearEnemigo(smgr, driver, world);

			}*/

		

			//debug para la subida de las armas
			/*
			if (teclado.isKeyDown(irr::KEY_KEY_I)) {
			pers->subirCapacidadDeMun();
			} else if (teclado.isKeyDown(irr::KEY_KEY_O)) {
			pers->subirCargador();
			} else if (teclado.isKeyDown(irr::KEY_KEY_P)) {
			pers->subirNivelDamage();
			}
			*/

			this->raton(dt);
			break;
		}

		case 1: {
			s32 pulsado = menuPausa->run();
			//                std::cout << "seleccion: " << pulsado << std::endl;
			if (pulsado != -1) {

				if (pulsado == 1) {
					update(0);
				}
				else if (pulsado == 2)
					iDevice->closeDevice();
			}
		}
		case 2:
		{
			std::cout << estado << std::endl;
			if (para==false)
			{
				para = true;
				std::cout << "maaaaaaaaatao" << std::endl;
				esce->destroyPared();
				esce->eleminarEnemigos();
				esce->destroyWaypoints();
				control = false;
				smgr->clear();
				manager.CambiaEstado("menu");
			}
			
		 //pers->getEntity()->setLive(false);
		}

		}

		if(control == true) {

		then = now;

		driver->beginScene(true, true, SColor(255, 100, 101, 140)); //se usa para hacer el render

		
		esce->actualizarListaEnemigos(dt);
		esce->actualizarEstadoPuerta();
		esce->actualizarEstadoPersonaje();
		esce->actualizarObjetosConsumables();
		smgr->drawAll(); //dibuja todo el grafo

		guienv->drawAll(); //dibujar el GUI

		driver->endScene(); //intercambia buffer

		int fps = driver->getFPS();
		if (lastFPS != fps) {
			core::stringw str = L"FPS: ";
			str += fps;

			iDevice->setWindowCaption(str.c_str());

			lastFPS = fps;
		}
		
		}

	}
	else {
		iDevice->yield();
	}
}

void Juego::destroyNew()
{

}

void Juego::cambioEstado(std::string est)
{
	if (est=="menu")
	{
	
		estado = 2;
		/*manager.CambiaEstado("menu");
		device->getGUIEnvironment()->clear();
		device->getSceneManager()->clear();*/
	}
}

