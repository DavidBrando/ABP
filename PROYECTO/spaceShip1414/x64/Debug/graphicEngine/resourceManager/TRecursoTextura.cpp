#include "TRecursoTextura.h"
#include <iostream>
#include <cstring>
#include <string>
#include <SFML\Graphics\Image.hpp>

TRecursoTextura::TRecursoTextura(std::string ntextura) : texturaID{ 0 }
{
	cargarFichero(ntextura);
}


TRecursoTextura::~TRecursoTextura()
{
	glDeleteTextures(1, &texturaID);
}

bool TRecursoTextura::cargarFichero(std::string ntextura)
{
	setNombre(ntextura);
	glGenTextures(1, &texturaID);
	std::cout << "textura ID: " << texturaID << std::endl;
	sf::Image imagen;
	if (!imagen.loadFromFile(/*"resourse/texture/"+*/ntextura))
	{
		//std::cerr << "No se a podidio cargar la textura -> " << ntextura << std::endl;
		return false;
	}
	
		glBindTexture(GL_TEXTURE_2D, texturaID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imagen.getSize().x, imagen.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, imagen.getPixelsPtr());

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, texturaID);
	
	return true;
}

void TRecursoTextura::draw()
{
}

void TRecursoTextura::draw(unsigned int num, GLuint programID, const std::string & nombre)
{
	glActiveTexture(GL_TEXTURE0 + num);
	glBindTexture(GL_TEXTURE_2D, texturaID);
	glUniform1i(glGetUniformLocation(programID, nombre.c_str()), num);
}

void TRecursoTextura::desactivar(unsigned int t)
{
	glActiveTexture(GL_TEXTURE0 + t);
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint TRecursoTextura::getTexturaID()
{
	
		return texturaID;
	
	
}
