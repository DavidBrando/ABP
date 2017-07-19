#include "TMalla.h"
#include <iostream>
#include "../resourceManager/TRecursoMalla.h"
#include "../resourceManager/TGestorRecursos.h"
#include "..\framework\openGLShader.h"
#include <glm\gtc\matrix_inverse.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\mat3x3.hpp>

TMalla::TMalla()
{
	
}

TMalla::TMalla(std::string path)
{
	this->cargarMalla(path);
}

TMalla::TMalla(std::string path, TGestorRecursos* gestor)
{
	this->cargarMalla(path, gestor);
}

TMalla::~TMalla()
{
	std::cout << "TMalla Destroyed" << std::endl;
}

void TMalla::cargarMalla(std::string path)
{
	if(this->malla == nullptr)
	{
		this->malla = new TRecursoMalla();
		this->malla->cargarFichero(path);
	}
	else
	{
		this->malla->cargarFichero(path);
	}
}

void TMalla::cargarMalla(std::string path, TGestorRecursos* gestor)
{
	this->malla = static_cast<TRecursoMalla*>(gestor->getRecurso(path,1));
}

void TMalla::beginDraw()
{
	this->malla->draw();
}

void TMalla::beginDraw(openGLShader& shader, const glm::mat4& view, const glm::mat4& proyection, double dt)
{
	glm::mat4 MV = view * matrizActual;
	glm::mat4 MVP = proyection * MV;
	glm::mat3 N = glm::inverseTranspose(glm::mat3(MV));

	glUniformMatrix4fv(shader.getUniformLocation("mvp_matrix"), 1, GL_FALSE, glm::value_ptr(MVP));
	glUniformMatrix4fv(shader.getUniformLocation("mv_matrix"), 1, GL_FALSE, glm::value_ptr(MV));
	glUniformMatrix3fv(shader.getUniformLocation("n_matrix"), 1, GL_FALSE, glm::value_ptr(N));
	this->malla->draw(shader.getProgram());
}

void TMalla::endDraw()
{
}
