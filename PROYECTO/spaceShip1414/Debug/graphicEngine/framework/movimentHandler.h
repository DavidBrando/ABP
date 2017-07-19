#pragma once
#ifndef GLEW_STATIC
#define GLEW_STATIC
#include <GL/glew.h>
#endif
#ifndef GLFW_STATIC
#define GLFW_STATIC
#include <GLFW\glfw3.h>
#endif
#include <glm\vec3.hpp>

class TTransform;
class player;
class TGraphicEngine;
class TCamara;
class Camara;
class movimentHandler
{
public:
	movimentHandler();
	~movimentHandler();
	void onKey(GLFWwindow* window, int key, int scancode, int action, int mods, double deltaTime, TGraphicEngine* motor);
	void onMouse(GLFWwindow*, double, double);
	void setMouseSensitive(float);
	void setPlayer(player*);
	void setCamara(Camara * cam);
	void checkKeys(GLFWwindow *);
private:
	//false = camara : true = player
	bool activo;
	bool moverJugador;
	float mouseSensitive;
	player *jugador;
	Camara *camara;
	glm::vec3 front;
};

