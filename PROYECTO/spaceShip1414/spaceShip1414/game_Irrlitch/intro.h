#pragma once
/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   intro.h
* Author: Hector
*
* Created on 10 de enero de 2017, 19:42
*/

#ifndef INTRO_H
#define INTRO_H

#include <irrlicht.h>
#include "EstadoGeneral.h"
#include <string>

class intro : public EstadoGeneral {
public:
	intro();
	intro(std::string name);
	virtual ~intro();

	void Dentro(void);
	void Fuera(void);
	bool OnEvent(const SEvent &event);
	void render(IrrlichtDevice* iDevice);
	void StarUP(IrrlichtDevice* iDevice);


private:

};

#endif /* INTRO_H */

