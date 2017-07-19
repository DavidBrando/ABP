#pragma once
#include "TRecurso.h"
#ifndef GLEW_STATIC
#define GLEW_STATIC
#include <GL/glew.h>
#endif
class TRecursoTextura :
	public TRecurso
{
public:
	TRecursoTextura(std::string);
	~TRecursoTextura();
	bool cargarFichero(std::string) override;
	void draw() override;
	void draw(unsigned int, GLuint, const std::string &);
	void desactivar(unsigned int);
	GLuint getTexturaID();
private:
	GLuint texturaID;
};

