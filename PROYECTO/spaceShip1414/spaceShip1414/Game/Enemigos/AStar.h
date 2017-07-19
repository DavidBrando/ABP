#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <glm\glm.hpp>


class Nodo;



class AStar
{

public:
	AStar(float** matrix, int tam);
	~AStar();
	int buscarWaypointCercano(const glm::vec3 &posEne, const std::vector<Nodo*> &vecNodos);
	int buscarWaypointMasCorto(const int &posNodoIni);
	int buscarWaypointNoRepetido(const int &posWaypointRep, const int &posNodoActual);
	int getDireccion(const glm::vec3 &posEne, const glm::vec3 &posNodo); //ver hacia donde tiene que ir
	glm::vec3 getVectorDeDireccion(const glm::vec3 &posEne, const glm::vec3 &posNodo);
	bool estoyEnElNodo(const glm::vec3 &posEne, const glm::vec3 &posNodo);
	float distanciaEntreElNodoYEne(const glm::vec3 posEne, const glm::vec3 posWaypoint);
	void calcularAnguloDeRotacion();
	float getAnguloDeRotacion();
	
	

private:

	float** matriz;
	int tamMatrix;
	float actualX, actualZ, anteriorX, anteriorZ, angulo;


};

