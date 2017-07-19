/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   intro.cpp
* Author: Hector
*
* Created on 10 de enero de 2017, 19:42
*/

//intro.cpp
#include "Intro.h"

intro::intro(void)
{
}

intro::intro(std::string name) : EstadoGeneral(name)
{

}

intro::~intro(void)
{
}

void intro::Dentro(void)
{
	//set up gui
}

void intro::Fuera(void)
{
	//restore playerdata
}

bool intro::OnEvent(const SEvent &event)
{
	//handle user input
	return(false);
}

void intro::render(IrrlichtDevice* iDevice)
{
	iDevice->getSceneManager()->addCameraSceneNode(0, vector3df(0, 70, -40), vector3df(0, 0, 0));
	iDevice->getSceneManager()->addCubeSceneNode(10);
	iDevice->getSceneManager()->drawAll();
}

void intro::StarUP(IrrlichtDevice* iDevice)
{

}