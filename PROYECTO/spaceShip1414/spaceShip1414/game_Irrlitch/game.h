#pragma once
/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   game.h
* Author: Hector
*
* Created on 29 de diciembre de 2016, 18:25
*/

#include <irrlicht.h>
#include "CAppReceiver.h"
#include <string>

#ifndef GAME_H
#define GAME_H

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class game {
public:
	game();
	game(const game& orig);
	virtual ~game();


private:

};

#endif /* GAME_H */

