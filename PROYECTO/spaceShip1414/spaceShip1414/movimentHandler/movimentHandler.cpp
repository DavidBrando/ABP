#include "movimentHandler.h"
#include <iostream>
#include "../graphicEngine/entityTree/TTransform.h"
#include "../Game/player.h"
#include "../Game/Camara.h"
#include "../graphicEngine/TGraphicEngine.h"
#include "../Game/TGameEngine.h"
#include "../graphicEngine/entityTree/TCamara.h"

movimentHandler::movimentHandler() : activo{ false }, mouseSensitive{ 0.015f }
{
}

movimentHandler::~movimentHandler()
{
}

void movimentHandler::update(int tecla, TGraphicEngine * graphicMotor, TGameEngine * gameMotor)
{
	if (gameMotor->getPlayer()->getImpulso() == false)
	{
		gameMotor->getPlayer()->actualizarFisicas(tecla, 0, 0);
	}
	else
	{
		gameMotor->getPlayer()->disminuirTem();
		if (gameMotor->getPlayer()->getTemporizador() == 0.0f)
		{
			gameMotor->getPlayer()->setImpulso(false);
		}
		gameMotor->getPlayer()->actualizarPosicion();
	}
	graphicMotor->resetTransform(gameMotor->getCamara()->getNodo(), 'r');
	gameMotor->getCamara()->updateCam(graphicMotor, gameMotor->getPlayer()->getPos(), tecla);
}

