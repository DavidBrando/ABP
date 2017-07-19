/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   Fusil.cpp
* Author: David
*
* Created on 23 de enero de 2017, 17:43
*/

#include "Fusil.h"

Fusil::Fusil() : Arma() {

	cargadorNiveles[0] = 30;
	damageNiveles[0] = 10;
	totalMunicion[0] = 360;
	capacidadDeMunicion = 0;
	municionActual = 30;

	for (int i = 1; i < 4; i++) {
		cargadorNiveles[i] = cargadorNiveles[i - 1] + 10;
		damageNiveles[i] = damageNiveles[i - 1] + damageNiveles[i - 1] * 0.3f;
		totalMunicion[i] = totalMunicion[i - 1] + 30;
	}

	nivelCargador = 0;
	nivelDamage = 0;
	nivelMunicion = 0;
	tiempoDisparo = 0.2f;
}

//Fusil::Fusil(const Fusil& orig) {
//}

Fusil::~Fusil() {
}

