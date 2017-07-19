#pragma once

#include <string>
#include <glm\vec3.hpp>


class Nodo
{
public:
	Nodo(std::string name, glm::vec3 position, int place);
	~Nodo();
	bool operator==(const Nodo& n) const;
	bool operator!=(const Nodo& n) const;
	std::string getNombre();
	glm::vec3 getPosicion();
	int getLugarDelNodo();


private: 

		std::string nombre;
		glm::vec3 pos;
		int lugar;

};

