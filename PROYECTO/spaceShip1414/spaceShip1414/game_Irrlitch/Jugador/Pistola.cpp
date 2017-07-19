/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   Pistola.cpp
* Author: David
*
* Created on 23 de enero de 2017, 17:25
*/

#include "Pistola.h"

Pistola::Pistola() : Arma() {

	cargadorNiveles[0] = 7;
	damageNiveles[0] = 20;
	totalMunicion[0] = 56;
	capacidadDeMunicion = 0;
	municionActual = 7;

	for (int i = 1; i < 4; i++) {
		cargadorNiveles[i] = cargadorNiveles[i - 1] + 1;
		damageNiveles[i] = damageNiveles[i - 1] + damageNiveles[i - 1] * 0.2;
		totalMunicion[i] = totalMunicion[i - 1] + 7;
	}

	nivelCargador = 0;
	nivelDamage = 0;
	nivelMunicion = 0;
	tiempoDisparo = 0.6f;
}

//Pistola::Pistola(const Pistola& orig) {
//}

Pistola::~Pistola() {
}

