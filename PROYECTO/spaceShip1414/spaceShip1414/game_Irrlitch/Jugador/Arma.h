#pragma once
/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   Arma.h
* Author: David
*
* Created on 23 de enero de 2017, 17:04
*/

#ifndef ARMA_H
#define ARMA_H


class Arma {
public:
	Arma();
	//    Arma(const Arma& orig);
	virtual ~Arma();

	void subirNivelCargador();
	void subirNivelDamage();
	void subirNivelMunicion();
	//metodos usados por el personaje para guardar en el arma el cargador actual
	//y el total de dicha municion
	void setCapacidadDeMun(int cap);
	void setMunicionAcutal(int newMun);
	// end
	float getTiempoDisparo();
	int getNivelCargador();
	int getNivelDamage();
	int getNivelMunicion();
	int getCapacidadDeMun();
	float getDamage();
	int getCargador();
	int getTotalMunicion();
	int getMunicionActual();


protected:

	int cargadorNiveles[4]; //cargador individual
	float damageNiveles[4]; //danyo actual
	int totalMunicion[4]; // total de municion que lleva
	float tiempoDisparo;
	int nivelCargador;
	int nivelDamage;
	int nivelMunicion;
	int capacidadDeMunicion; //municion que tengo guardada
	int municionActual; //cargador que tengo actualmente



};

#endif /* ARMA_H */

