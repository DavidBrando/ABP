#pragma once
#include "TEntidad.h"
#ifndef GLEW_STATIC
#define GLEW_STATIC
#include <GL/glew.h>
#endif
#ifndef GLFW_STATIC
#define GLFW_STATIC
#include <GLFW\glfw3.h>
#endif
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>

class TCamara :
	public TEntidad
{
public:
	TCamara(float, float, float, float);
	TCamara(bool, float, float, float, float, float, float);
	TCamara::TCamara(bool, float, float, float, float);
	~TCamara();
	void setPerspectiva(float, float, float, float, float, float);
	void setParalela(float, float, float, float, float, float);
	void setView(glm::mat4);
	glm::mat4 getView();
	glm::mat4 getProjectionMatrix();
	void beginDraw() override;
	void beginDraw(openGLShader&, const glm::mat4&, const glm::mat4&, double) override;
	void endDraw() override;
	void activar();
	void desactivar();
	bool getActiva();
	char getTipo();
	void setTipo(char);
	glm::mat4 getInverseProjection();
private:
	char tipo;
	bool activa;
	bool esPerspectiva;
	glm::vec3 front, up;
	glm::mat4 view;
};

