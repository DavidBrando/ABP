/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   Escopeta.cpp
* Author: David
*
* Created on 23 de enero de 2017, 17:48
*/

#include "Escopeta.h"

Escopeta::Escopeta() : Arma() {

	cargadorNiveles[0] = 5;
	damageNiveles[0] = 25;
	totalMunicion[0] = 35;
	capacidadDeMunicion = 15;
	municionActual = 5;

	for (int i = 1; i < 4; i++) {
		cargadorNiveles[i] = cargadorNiveles[i - 1] + 1;
		damageNiveles[i] = damageNiveles[i - 1] + damageNiveles[i - 1] * 0.7f;
		totalMunicion[i] = totalMunicion[i - 1] + 5;
	}

	nivelCargador = 0;
	nivelDamage = 0;
	nivelMunicion = 0;
	tiempoDisparo = 1.0f;
}

//Escopeta::Escopeta(const Escopeta& orig) {
//}

Escopeta::~Escopeta() {
}

