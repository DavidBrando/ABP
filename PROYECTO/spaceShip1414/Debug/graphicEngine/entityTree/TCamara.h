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

class TCamara :
	public TEntidad
{
public:
	TCamara();
	TCamara(bool, float, float, float, float, float, float);
	~TCamara();
	void setPerspectiva(float, float, float, float, float, float);
	void setParalela(float, float, float, float, float, float);
	void setWindow(GLFWwindow*);
	void setView(glm::mat4);
	glm::mat4 getView();
	glm::mat4 getProjectionMatrix();
	void beginDraw() override;
	void beginDraw(openGLShader&, const glm::mat4&, const glm::mat4&) override;
	void endDraw() override;
	void activar();
	glm::vec3 mover();
	void desactivar();
	bool getActiva();
	void chechKeys();
	char getTipo();
	void setTipo(char);
private:
	char tipo;
	bool activa;
	bool esPerspectiva;
	glm::vec3 front, up;
	glm::mat4 view;
	void checkMouse();

	inline bool isKeyPress(int);
	GLfloat cameraSpeed, mouseSensitive;
	GLFWwindow* window;
	float yaw, pitch;
	glm::vec3 cameraPos, cameraFront, cameraUp;
};

