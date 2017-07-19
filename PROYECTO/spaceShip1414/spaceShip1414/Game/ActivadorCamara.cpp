#include "ActivadorCamara.h"
#include <glm\vec3.hpp>
#include "../graphicEngine/TGraphicEngine.h"
#include "../Fisicas\Entity2D.h"
#include "../Fisicas\Mundo.h"
#include <iostream>

ActivadorCamara::ActivadorCamara(TGraphicEngine * motorApp, Mundo *mundo,int ident, glm::vec3 pos, glm::vec3 rot, glm::vec3 escala, void* dirCamara)
{
	std::cout << "---------->" << ident << std::endl;
	Entity2D *entity = new Entity2D(mundo->getWorldBox2D(),
		pos,
		rot,
		escala,
		this, true);
		id = ident;
		dirCam = dirCamara;
}


ActivadorCamara::~ActivadorCamara()
{
}


int ActivadorCamara::getID()
{
	return id;
}

void * ActivadorCamara::getDirCamara()
{
	return dirCam;
}
