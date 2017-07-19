#include "TGameEngine.h"
#include "Escenario\readJson.h"
#include "Escenario\Escenario.h"
#include "..\Fisicas\Mundo.h"
#include "..\Fisicas\b2GLDraw.h"
#include "player.h"
#include "../movimentHandler/movimentHandler.h"

TGameEngine::TGameEngine() : flags{ 0 }, scene{ nullptr }, world{ nullptr }, fooDrawInstance{ nullptr }, jugador{ nullptr }
{
}

TGameEngine::~TGameEngine()
{
	delete scene;
	delete world;
	delete fooDrawInstance;
	scene = nullptr;
	world = nullptr;
	fooDrawInstance = nullptr;
	jugador = nullptr;
	std::cout << "TGameEngine Destroyed" << std::endl;
}

bool TGameEngine::iniciarGameEngine(TGraphicEngine * motorApp)
{
	world = new Mundo();
	world->setMotorGame(motorApp, this);
	scene = new Escenario(motorApp, world);
	readJson json(scene);
	fooDrawInstance = new b2GLDraw();
	world->getWorldBox2D()->SetDebugDraw(fooDrawInstance);
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	flags += b2Draw::e_pairBit;
	flags += b2Draw::e_aabbBit;
	flags += b2Draw::e_centerOfMassBit;
	fooDrawInstance->SetFlags(flags);
	jugador = scene->getPersonaje();
	return true;
}

void TGameEngine::update(double deltaTime, movimentHandler* handler, TGraphicEngine * motorApp, int tecla)
{
	world->stepBox2D(1.0 / 60.0, 6, 2);
	world->getWorldBox2D()->DrawDebugData();
	world->clearForcesBox2D();
	handler->update(tecla, motorApp, this);
	jugador->actualizarLista(0.0f);
	scene->actualizarEstadoPuerta();
	scene->actualizarListaEnemigos(deltaTime);
	scene->actualizarObjetosConsumables();
	actualizarTiempoDeDisparo();
}

void TGameEngine::cambiarLuzActiva(int id)
{
	if (scene) {
		std::cout << "no es nulo" << std::endl;
	}
	scene->cambioDeLuces(id);
}

player * TGameEngine::getPlayer()
{
	return jugador;
}

Camara * TGameEngine::getCamara()
{
	return scene->getCamara();
}

void TGameEngine::drawDebug() {
	world->getWorldBox2D()->DrawDebugData();
	std::cout << "Se dibujan las fisicas" << std::endl;
}

Mundo* TGameEngine::getMundo() {
	return world;

}

void TGameEngine::actualizarTiempoDeDisparo() {
	if (jugador->getDisparo() == true && jugador->getArmaActual() != -1) {
		jugador->setTiempoDisparo(jugador->getTiempoDisparo() + 0.016);
		if (jugador->getTiempoDisparo() >= jugador->getTiempoArma()) {
			jugador->setDisparo(false);
			jugador->setTiempoDisparo(0);
		}
	}
}

void TGameEngine::victory()
{
	getPlayer()->victory();
}
