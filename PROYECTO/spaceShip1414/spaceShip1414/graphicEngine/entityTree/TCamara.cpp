#include "TCamara.h"
#include <iostream>
#include <glm\gtx\euler_angles.hpp>
#include <glm\gtx\matrix_cross_product.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\matrix_inverse.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm\gtx\string_cast.hpp>
#include "..\framework\openGLShader.h"

TCamara::TCamara(float fovy, float aspect, float near, float far) : tipo{ 0 }, activa{ false }, esPerspectiva{ true },
front{ fovy, aspect, 0 }, up{ near, far, 0 }
{
}

TCamara::TCamara(bool p, float left, float right, float bottom, float top, float near, float far) : tipo{ 1 }
{
	if (p) {
		this->setPerspectiva(left, right, bottom, top, near, far);
	}
	else {
		this->setParalela(left, right, bottom, top, near, far);
	}
}

TCamara::TCamara(bool pe, float fovy, float aspect, float near, float far) : tipo{ 1 }, esPerspectiva{ pe }, front{ fovy, aspect, 0 }, up{ near, far, 0 }
{


}

TCamara::~TCamara()
{
	std::cout << "TCamara Detroyed" << std::endl;
}

void TCamara::setPerspectiva(float left, float right, float bottom, float top, float near, float far)
{
	this->esPerspectiva = true;
	this->front = glm::vec3(left, right, near);
	this->up = glm::vec3(bottom, top, far);
}

void TCamara::setParalela(float left, float right, float bottom, float top, float near, float far)
{
	this->esPerspectiva = false;
	this->front = glm::vec3(left, right, near);
	this->up = glm::vec3(bottom, top, far);
}

void TCamara::setView(glm::mat4 v)
{
	this->view = glm::inverse(v);
}

glm::mat4 TCamara::getView()
{
	//std::cout << "Matriz View "<< tipo + 0 << ": " << glm::to_string(view) << std::endl;
	return view;
}

glm::mat4 TCamara::getProjectionMatrix()
{
	if (esPerspectiva) {
		return glm::perspective(front.x, front.y, up.x, up.y);
		//return glm::frustum(front.x, front.y, up.x, up.y, front.z, up.z);
	}
	else {
		return glm::ortho(front.x, front.y, up.x, up.y, front.z, up.z);
	}
}


void TCamara::beginDraw()
{
}

void TCamara::beginDraw(openGLShader& shader, const glm::mat4& view, const glm::mat4& proyection, double dt)
{
}

void TCamara::endDraw()
{
}

void TCamara::activar()
{
	activa = true;
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

glm::mat4 TCamara::getInverseProjection()
{
	return glm::inverse(getProjectionMatrix());
}