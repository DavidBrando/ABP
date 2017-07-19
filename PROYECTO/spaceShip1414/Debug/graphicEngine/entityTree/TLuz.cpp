#include "TLuz.h"
#include <iostream>
#include "..\framework\openGLShader.h"
#include <glm\gtc\matrix_inverse.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\mat3x3.hpp>
#include <glm\vec4.hpp>

TLuz::TLuz()
{
}

TLuz::TLuz(float x, float y, float z) : intensidad {x, y, z}, activa(false)
{
}

TLuz::~TLuz()
{
	std::cout << "TLuz Destroyed" << std::endl;
}

void TLuz::setIntensidad(float x, float y, float z)
{
	this->intensidad.x = x;
	this->intensidad.y = y;
	this->intensidad.z = z;
}

glm::vec3 TLuz::getIntensidad()
{
	return this->intensidad;
}

void TLuz::beginDraw()
{
}

void TLuz::beginDraw(openGLShader& shader, const glm::mat4& view, const glm::mat4& proyection)
{
	/*glm::mat4 MV = view * model;
	glm::mat4 MVP = proyection * MV;
	glm::mat3 N = glm::inverseTranspose(glm::mat3(MV));

	glUniformMatrix4fv(shader.getUniformLocation("mvp_matrix"), 1, GL_FALSE, glm::value_ptr(MVP));
	glUniformMatrix4fv(shader.getUniformLocation("mv_matrix"), 1, GL_FALSE, glm::value_ptr(MV));
	glUniformMatrix3fv(shader.getUniformLocation("n_matrix"), 1, GL_FALSE, glm::value_ptr(N));

	// direccion de la luz
	glm::vec3 lightDirEyeSpace = glm::vec3(MV * glm::vec4(this->intensidad, 0));

	glUniform3fv(shader.getUniformLocation("light.direction"), 1, glm::value_ptr(lightDirEyeSpace));
	glUniform3fv(shader.getUniformLocation("light.ambient"), 1, glm::value_ptr(glm::vec3(0.1f)));
	glUniform3fv(shader.getUniformLocation("light.diffuse"), 1, glm::value_ptr(glm::vec3(1.0f)));
	glUniform3fv(shader.getUniformLocation("light.specular"), 1, glm::value_ptr(glm::vec3(1.0f)));*/
}

void TLuz::endDraw()
{
}

void TLuz::activar()
{
	activa = true;
}

void TLuz::desactivar()
{
	activa = false;
}

bool TLuz::getActiva()
{
	return activa;
}

void TLuz::renderLuz(const glm::mat4& model, openGLShader& shader, const glm::mat4& view, const glm::mat4& proyection)
{
	glm::mat4 MV = view * model;
	glm::mat4 MVP = proyection * MV;
	glm::mat3 N = glm::inverseTranspose(glm::mat3(MV));

	glUniformMatrix4fv(shader.getUniformLocation("mvp_matrix"), 1, GL_FALSE, glm::value_ptr(MVP));
	glUniformMatrix4fv(shader.getUniformLocation("mv_matrix"), 1, GL_FALSE, glm::value_ptr(MV));
	glUniformMatrix3fv(shader.getUniformLocation("n_matrix"), 1, GL_FALSE, glm::value_ptr(N));

	// direccion de la luz
	glm::vec3 lightDirEyeSpace = glm::vec3(MV * glm::vec4(this->intensidad, 0));

	glUniform3fv(shader.getUniformLocation("light.direction"), 1, glm::value_ptr(lightDirEyeSpace));
	glUniform3fv(shader.getUniformLocation("light.ambient"), 1, glm::value_ptr(glm::vec3(0.1f)));
	glUniform3fv(shader.getUniformLocation("light.diffuse"), 1, glm::value_ptr(glm::vec3(1.0f)));
	glUniform3fv(shader.getUniformLocation("light.specular"), 1, glm::value_ptr(glm::vec3(1.0f)));
}

