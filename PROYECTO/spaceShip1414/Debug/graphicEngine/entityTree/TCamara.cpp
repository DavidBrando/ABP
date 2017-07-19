#include "TCamara.h"
#include <iostream>
#include <glm\gtx\euler_angles.hpp>
#include <glm\gtx\matrix_cross_product.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\matrix_inverse.hpp>
#include "..\framework\openGLShader.h"

TCamara::TCamara() : yaw{ 0 }, pitch{ 0 },
cameraPos{ 0.0f, 4.5f, 15.0f },
cameraFront{ 0.0f, 0.0f, -1.0f },
cameraUp{ 0.0f, 1.0f, 0.0f },
cameraSpeed{ 0.05f }, mouseSensitive{ 0.15f }, tipo{ 0 }, activa{ false }
{
}

TCamara::TCamara(bool p, float x1, float y1, float z1, float x2, float y2, float z2) : tipo{ 1 }
{
	if (p) {
		this->setPerspectiva(x1, y1, z1, x2, y2, z2);
	}
	else {
		this->setParalela(x1, y1, z1, x2, y2, z2);
	}
}

TCamara::~TCamara()
{
	std::cout << "TCamara Detroyed" << std::endl;
}

void TCamara::setPerspectiva(float xu, float yu, float zu, float xf, float yf, float zf)
{
	this->esPerspectiva = true;
	this->front = glm::vec3(xf, yf, zf);
	this->up = glm::vec3(xu, yu, zu);
	cameraSpeed = 5.0f;
}

void TCamara::setParalela(float xu, float yu, float zu, float xf, float yf, float zf)
{
	this->esPerspectiva = false;
	this->front = glm::vec3(xf, yf, zf);
	this->up = glm::vec3(xu, yu, zu);
}

void TCamara::setWindow(GLFWwindow * ventana)
{
	window = ventana;
}

void TCamara::setView(glm::mat4 v)
{
	this->view = glm::inverse(v);
}

glm::mat4 TCamara::getView()
{
	chechKeys();
	if (tipo!=0) {
		return view;
	}
	else {
		chechKeys();
		checkMouse();

		// obtener los parametros de visualizacion
		glm::mat4 Rot = glm::yawPitchRoll(glm::radians(yaw), glm::radians(pitch), 0.0f);
		cameraFront = glm::vec3(Rot * glm::vec4(0, 0, -1, 0));
		cameraUp = glm::vec3(Rot * glm::vec4(0, 1, 0, 0));

		// craer la matriz de vista
		return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	}
}



glm::mat4 TCamara::getProjectionMatrix()
{
	if (tipo!=0) {
		int width, height;
		glfwGetWindowSize(window, &width, &height);

		return glm::perspective(up.x, static_cast<float>(width) / static_cast<float>(height), up.y, up.z);
	}
	else {
		int width, height;
		glfwGetWindowSize(window, &width, &height);

		return glm::perspective(45.0f, static_cast<float>(width) / static_cast<float>(height), 0.1f, 1000.0f);
	}
}

void TCamara::beginDraw()
{
}

void TCamara::beginDraw(openGLShader& shader, const glm::mat4& view, const glm::mat4& proyection)
{
}

void TCamara::endDraw()
{
}

void TCamara::activar()
{
	activa = true;
}

glm::vec3 TCamara::mover()
{
	chechKeys();
	return cameraPos;
}

void TCamara::desactivar()
{
	activa = false;
}

bool TCamara::getActiva()
{
	return activa;
}

char TCamara::getTipo()
{
	return tipo;
}

void TCamara::setTipo(char t)
{
	this->tipo = t;
}

void TCamara::checkMouse()
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	int width, height;
	glfwGetWindowSize(window, &width, &height);
	glfwSetCursorPos(window, width / 2.0, height / 2.0);

	GLfloat xoffset = ((width / 2.0f) - static_cast<float>(xpos)) * mouseSensitive;
	GLfloat yoffset = ((height / 2.0f) - static_cast<float>(ypos)) * mouseSensitive;

	yaw += xoffset;
	pitch += yoffset;
}

void TCamara::chechKeys()
{

	if (isKeyPress(GLFW_KEY_W)) { cameraPos += cameraSpeed * front;}
	if (isKeyPress(GLFW_KEY_S)) { cameraPos -= cameraSpeed * front; }
	if (isKeyPress(GLFW_KEY_A)) { cameraPos -= glm::normalize(glm::cross(front, up)) * cameraSpeed; }
	if (isKeyPress(GLFW_KEY_D)) { cameraPos += glm::normalize(glm::cross(front, up)) * cameraSpeed; }
}

inline bool TCamara::isKeyPress(int key)
{
	return (glfwGetKey(window, key) == GLFW_PRESS);
}
