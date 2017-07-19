/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Waypoints.cpp
 * Author: Hector
 *
 * Created on 24 de enero de 2017, 18:00
 */

#include "Waypoints.h"
#include <math.h>
#include "Nodo.h"
#include "../Fisicas/Entity2D.h"



Waypoints::Waypoints() {

}

Waypoints::Waypoints(const Waypoints& orig) {

}

Waypoints::~Waypoints() {

	delete[] pesos[0];
	delete[] pesos;

}

void Waypoints::MuestraPuntos() {
    std::cout << "-<-<-<-<-<-<-<-<-<-<-<-<" << std::endl;
    for (int i = 0; i < puntos.size(); i++) {

        std::cout << puntos[i]->getNombre() << " " << puntos.size() << std::endl;
    }

    std::cout << "-<-<-<-<-<-<-<-<-<-<-<-<" << std::endl;
}

void Waypoints::MostrarAdyacencia() {

	std::cout << "///////////////////////////////" << std::endl;

	for (int i = 0; i < puntos.size(); i++) {

		std::cout <<i<<" Llega a: " << "(";
		for (int j = 0; j < puntos.size(); j++) {
			
			if (pesos[i][j] > 0) {
				std::cout << j << ", ";
				
			}

			//else {
			//	std::cout << pesos[i][j] << ", ";
			//}

			if (puntos.size() - 1 == j) {
				std::cout << ")" << std::endl;
			}
		}
	}

	std::cout << "///////////////////////////////" << std::endl;

}




void Waypoints::creaPuntos(std::string nombre, glm::vec3 posicion) {

	Nodo *way = new Nodo(nombre, posicion,static_cast<int>(puntos.size()));

    puntos.push_back(way);
 
	
		
}

void Waypoints::creaPesos(Entity2D *entity) {
  
    float weightX = 0;
    float weightZ = 0;
    float weight = 0;

	//pesos = new float*[puntos.size()];
 //   for (int i = 0; i < puntos.size(); i++) {
 //       pesos[i] = new float[puntos.size()];
 //   }


    for (int i = 0; i < puntos.size(); i++) {

        for (int j = 0; j < puntos.size(); j++) {
            pesos[i][j] = 0;

            if (puntos[i] != puntos[j]) {
				
				//si nos devuelve f = 0 significa que ha chocado contra algo que no es una pared
				//o contra nada entonces se le asigna el valor de la distancia
				//sino, (choca contra una pared) se le pondria -1 (no llega a ese waypoint)
				//se deberia limiar el uso de raycast usando un filtro para el peso que si
				//supera X valor (tamDelMapa / 4 por ejemplo) no haga el raycast y se le asigne
				// -1
				float f = -1;
				weightX = pow((puntos[j]->getPosicion().x - puntos[i]->getPosicion().x), 2);
				weightZ = pow((puntos[j]->getPosicion().z - puntos[i]->getPosicion().z), 2);
				weight = weightX + weightZ;
				weight = sqrt(weight);
				/*std::cout << "///////////////////////" << std::endl;

				std::cout << "PESO ANTES DEL FILTRO: " << weight << std::endl;
				std::cout << "///////////////////////" << std::endl;*/



				if(weight <=tamDelMapa * 0.03 ) {
					 f = entity->rayCasting(b2Vec2(puntos[i]->getPosicion().x, puntos[i]->getPosicion().z), 
						 b2Vec2(puntos[j]->getPosicion().x, puntos[j]->getPosicion().z));

					 //std::cout<<"-------- F: "<<f<<std::endl;

					 if(f != 0.0f) {
						 weight = -1;
					 }

				}

				else {
					weight = -1;
				}

                //std::cout<<"///////////////////////"<<std::endl;
                //std::cout<< puntos[i]->getNombre()<<std::endl;
                //std::cout<<"I: "<<i<<"J: "<<j<<std::endl;
                //std::cout<< puntos[j]->getNombre() <<std::endl;
				
                //std::cout << "F = " << f << std::endl;
              
                //std::cout<<"PESO: "<<weight<<std::endl;

                pesos[i][j] = weight;

            }
        }
    }

}

void Waypoints::crearMatriz()
{

	pesos = new float*[puntos.size()];
	pesos[0] = new float[puntos.size()*puntos.size()];

	for (std::size_t i = 1; i < puntos.size(); i++) {
		pesos[i] = pesos[0] + puntos.size() * i;
	}


}

void Waypoints::mostrarPesos() {

	std::cout << "///////////////////////////////" << std::endl;

    for (int i = 0; i < puntos.size(); i++) {

		std::cout<<"i: " << i << ": " << "(";
        for (int j = 0; j < puntos.size(); j++) {
			std::cout << j << ": [" << pesos[i][j] << "], " << std::endl;;
            if (puntos.size() - 1 == j) {
                std::cout << ")" <<std::endl;
            }
        }
    }

	std::cout << "///////////////////////////////" << std::endl;

}


void Waypoints::setTamDelMapa(int tam) {
	tamDelMapa = tam;
}


float** Waypoints::getMatriz() {
	return pesos;
}

float Waypoints::getPeso(const int i, const int j) {

	return pesos[i][j];

}


std::vector<Nodo*> Waypoints::getNodos() {
	return puntos;
}

Nodo* Waypoints::getNodoX(int x) {

	return puntos.at(x);

}

int Waypoints::getTamMapa()
{
	return static_cast<int>(puntos.size());
}
