/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   Arma.cpp
* Author: David
*
* Created on 23 de enero de 2017, 17:04
*/
#include <iostream>

#include "Arma.h"

Arma::Arma() {
}

//Arma::Arma(const Arma& orig) {
//}

Arma::~Arma() {
}

int Arma::getNivelCargador() {
	return nivelCargador;
}

int Arma::getNivelDamage() {
	return nivelDamage;
}

int Arma::getNivelMunicion() {
	return nivelMunicion;
}

float Arma::getTiempoDisparo() {
	return tiempoDisparo;
}

//total de balas que tiene el arma
int Arma::getCapacidadDeMun() {
	return capacidadDeMunicion;
}

//total de un cargador individual dependiendo del nivels
int Arma::getCargador() {
	return cargadorNiveles[nivelCargador];
}

int Arma::getTotalMunicion()
{
	return totalMunicion[nivelMunicion];
}

float Arma::getDamage() {
	return damageNiveles[nivelDamage];
}

//devuelve la municion del cargador cuando se cambia
int Arma::getMunicionActual() {
	return municionActual;
}




void Arma::subirNivelCargador() {

	if (nivelCargador <= 3) {
		nivelCargador++;
		std::cout << "Ha aumentado tu cargador de " << cargadorNiveles[nivelCargador] << " balas a ";
		nivelCargador++;
		std::cout << cargadorNiveles[nivelCargador] << "balas" << std::endl;
	}
	else {
		std::cout << "Has alcanzado el nivel maximo que es el 4" << std::endl;
	}
}

void Arma::subirNivelDamage() {

	if (nivelDamage <= 3) {
		std::cout << "Ha aumentado tu damage de " << damageNiveles[nivelDamage] << " a ";
		nivelDamage++;
		std::cout << damageNiveles[nivelDamage] << " de damage" << std::endl;
	}
	else {
		std::cout << "Has alcanzado el nivel maximo que es el 4" << std::endl;
	}
}

void Arma::subirNivelMunicion() {

	if (nivelMunicion <= 3) {
		std::cout << "Ha aumentado tu municion total de " << totalMunicion[nivelMunicion] << " a ";
		nivelMunicion++;
		std::cout << totalMunicion[nivelMunicion] << " total" << std::endl;
	}

	else {
		std::cout << "Has alcanzado el nivel maximo que es el 4" << std::endl;
	}

}

void Arma::setCapacidadDeMun(int cap) {
	capacidadDeMunicion = cap;
}

void Arma::setMunicionAcutal(int newMun) {
	municionActual = newMun;
}

