#include "TLuz.h"
#include <iostream>
#include "..\framework\openGLShader.h"
#include <glm\gtc\matrix_inverse.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\mat3x3.hpp>
#include <glm\vec4.hpp>
#include <glm\gtx\matrix_decompose.hpp>
#include <glm\gtc\matrix_transform.hpp>

unsigned int TLuz::nLuces = 0;

TLuz::TLuz(bool estaActiva, bool local, bool foco, float fAmbient[], float fColor[], float dicLuz[], float dicCono[], float sCosCutOff, float sExponet, float ateCos, float ateLin, float ateCua) :
	activa{ estaActiva }, esLocal{ local }, esFoco{ foco }, spotCosCutOff{ sCosCutOff }, spotExponent{ sExponet }, atenuacionConstante{ ateCos }, atenuacionLinial{ ateLin }, atenuacionCuadratica{ ateCua }
{
	if (fAmbient != NULL) {
		ambient = glm::vec3(fAmbient[0], fAmbient[1], fAmbient[2]);
	}
	else {
		ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	}
	if (fColor != NULL) {
		color = glm::vec3(fColor[0], fColor[1], fColor[2]);
	}
	else {
		color = glm::vec3(1.0f, 1.0f, 1.0f);
	}
	if (dicLuz != NULL) {
		direccionLuz = glm::vec3(dicLuz[0], dicLuz[1], dicLuz[2]);
	}
	else {
		direccionLuz = glm::vec3(0.0f, 0.0f, -40.0f);
	}
	if (dicCono != NULL) {
		direccionCono = glm::vec3(dicCono[0], dicCono[1], dicCono[2]);
	}
	else {
		direccionCono = glm::vec3(0.0f, -1.0f, 0.0f);
	}
	direccionConoView = glm::vec3(0.0f, -1.0f, 0.0f);
	vectorMedio = glm::normalize(direccionLuz + glm::vec3(0, 0, 1));
	id = nLuces;
	++nLuces;
}

TLuz::~TLuz()
{
	std::cout << "TLuz Destroyed" << std::endl;
}

void TLuz::beginDraw()
{
}

void TLuz::beginDraw(openGLShader& shader, const glm::mat4& view, const glm::mat4& proyection, double dt)
{
	//esto se hace en el renderLuz por el sistema de registro de luces.
}

void TLuz::endDraw()
{
}

void TLuz::renderLuz(const glm::mat4& model, openGLShader& shader, const glm::mat4& view, const glm::mat4& proyection)
{
	std::cout << "Inicia Render Luz"<< std::endl;
	glm::mat4 MV = view * model;
	glm::mat4 MVP = proyection * MV;
	glm::mat3 N = glm::inverseTranspose(glm::mat3(MV));

	glUniformMatrix4fv(shader.getUniformLocation("mvp_matrix"), 1, GL_FALSE, glm::value_ptr(MVP));
	glUniformMatrix4fv(shader.getUniformLocation("mv_matrix"), 1, GL_FALSE, glm::value_ptr(MV));
	glUniformMatrix3fv(shader.getUniformLocation("n_matrix"), 1, GL_FALSE, glm::value_ptr(N));


	std::cout << "matricez Render Luz completas" << std::endl;
	float Shininess = 0.1f;
	float Strength = 0.2f;
	
	//std::cout << "------------ Luz ID: " << id << " --------------" << std::endl;
	std::cout << "Inicia Render Luz shader" << std::endl;
	glUniform1f(shader.getUniformLocation("Shininess"), Shininess);
	glUniform1f(shader.getUniformLocation("Strength"), Strength);
	std::string luz = "luz[" + std::to_string(id) + "].activa";
	//std::cout << luz << " -> " << activa << std::endl;
	glUniform1i(shader.getUniformLocation(luz), activa);
	luz = "luz[" + std::to_string(id) + "].esLocal";
	//std::cout << luz << " -> " << esLocal << std::endl;
	glUniform1i(shader.getUniformLocation(luz), esLocal);
	luz = "luz[" + std::to_string(id) + "].esFocal";
//	std::cout << luz << " -> " << esFoco << std::endl;
	glUniform1i(shader.getUniformLocation(luz), esFoco);
	luz = "luz[" + std::to_string(id) + "].cAmbiente";
//	std::cout << luz << " -> " << ambient.r << " - " << ambient.g << " - " << ambient.b << std::endl;
	glUniform3fv(shader.getUniformLocation(luz), 1, glm::value_ptr(ambient));
	luz = "luz[" + std::to_string(id) + "].colorDS";
	//std::cout << luz << " -> " << color.r << " - " << color.g << " - " << color.b << std::endl;
	glUniform3fv(shader.getUniformLocation(luz), 1, glm::value_ptr(color));
	luz = "luz[" + std::to_string(id) + "].posicion";
	glm::vec3 v = getDirectionXView(MV);
	float p[] = { v.x, v.y, v.z };
	setDireccionLuz(p);
	//std::cout << luz << " -> " << direccionLuz.x << " - " << direccionLuz.y << " - " << direccionLuz.z << std::endl;
	glUniform3fv(shader.getUniformLocation(luz), 1, glm::value_ptr(direccionLuz));
	luz = "luz[" + std::to_string(id) + "].vectorMedio";
//	std::cout << luz << " -> " << vectorMedio.x << " - " << vectorMedio.y << " - " << vectorMedio.z << std::endl;
	glUniform3fv(shader.getUniformLocation(luz), 1, glm::value_ptr(vectorMedio));
	luz = "luz[" + std::to_string(id) + "].direcCono";
	/*glm::mat4 modelCono = glm::translate(glm::mat4(), glm::vec3(direccionCono.x, direccionCono.y, direccionCono.z));
	glm::mat4 MVCono = view * modelCono;
	v = getDirectionXView(MVCono);
	p[0] = 0;
	p[1] = v.y;
	p[2] = 0;
	setDireccionConoView(p);*/
	//std::cout << luz << " -> " << direccionCono.x << " - " << direccionCono.y << " - " << direccionCono.z << std::endl;
	//std::cout << luz << " -> " << direccionConoView.x << " - " << direccionConoView.y << " - " << direccionConoView.z << std::endl;
	glUniform3fv(shader.getUniformLocation(luz), 1, glm::value_ptr(direccionCono));
	luz = "luz[" + std::to_string(id) + "].spotCosCutOff";
	//std::cout << luz << " -> " << spotCosCutOff << std::endl;
	glUniform1f(shader.getUniformLocation(luz), spotCosCutOff);
	luz = "luz[" + std::to_string(id) + "].spotExponent";
//	std::cout << luz << " -> " << spotExponent << std::endl;
	glUniform1f(shader.getUniformLocation(luz), spotExponent);
	luz = "luz[" + std::to_string(id) + "].atenuacionConstante";
//	std::cout << luz << " -> " << atenuacionConstante << std::endl;
	glUniform1f(shader.getUniformLocation(luz), atenuacionConstante);
	luz = "luz[" + std::to_string(id) + "].atenuacionLinial";
//	std::cout << luz << " -> " << atenuacionLinial << std::endl;
	glUniform1f(shader.getUniformLocation(luz), atenuacionLinial);
	luz = "luz[" + std::to_string(id) + "].atenuacionCuadratica";
	//std::cout << luz << " -> " << atenuacionCuadratica << std::endl;
	glUniform1f(shader.getUniformLocation(luz), atenuacionCuadratica);
	//std::cout << "-----------------------------------------" << std::endl;
	std::cout << "Finaliza Render Luz shader" << std::endl;
}

void TLuz::activar()
{
	activa = true;
}

void TLuz::desactivar()
{
	activa = false;
}

bool TLuz::estaActiva()
{
	return activa;
}

bool TLuz::esAmbiental()
{
	if (esLocal)
		return false;
	else
		return true;
}

bool TLuz::esPuntual()
{
	if (esLocal && !esFoco)
		return true;
	else
		return false;
}

bool TLuz::esFocal()
{
	return esFoco;
}

void TLuz::setLocal(bool l)
{
	esLocal = l;
}

void TLuz::setFoco(bool f)
{
	esFoco = f;
}

void TLuz::setAmbient(float v[])
{
	ambient.r = v[0];
	ambient.g = v[1];
	ambient.b = v[2];
}

void TLuz::setColor(float v[])
{
	color.r = v[0];
	color.g = v[1];
	color.b = v[2];
}

void TLuz::setDireccionLuz(float v[])
{
	direccionLuz.x = v[0];
	direccionLuz.y = v[1];
	direccionLuz.z = v[2];
	vectorMedio = glm::normalize(direccionLuz + glm::vec3(0, 0, 1));
}

void TLuz::setDireccionCono(float v[])
{
	direccionCono.x = v[0];
	direccionCono.y = v[1];
	direccionCono.z = v[2];
}

void TLuz::setCosCutOffFoco(float f)
{
	spotCosCutOff = f;
}

void TLuz::setExponentFoco(float f)
{
	spotExponent = f;
}

void TLuz::setAtenuacionConstante(float f)
{
	atenuacionConstante = f;
}

void TLuz::setAtenuacionLiniar(float f)
{
	atenuacionLinial = f;
}

void TLuz::setAtenuacionCuadratica(float f)
{
	atenuacionCuadratica = f;
}

void TLuz::setDireccionConoView(float v[])
{
	direccionConoView.x = v[0];
	direccionConoView.y = v[1];
	direccionConoView.z = v[3];
}

glm::vec3 TLuz::getAmbient()
{
	return ambient;
}

glm::vec3 TLuz::getColor()
{
	return color;
}

glm::vec3 TLuz::getDireccionLuz()
{
	return direccionLuz;
}

glm::vec3 TLuz::getDireccionCono()
{
	return direccionCono;
}

glm::vec3 TLuz::getDireccionConoView()
{
	return direccionConoView;
}

float TLuz::getCosCutOffFoco()
{
	return spotCosCutOff;
}

float TLuz::getExponentFoco()
{
	return spotExponent;
}

float TLuz::getAtenuacionConstante()
{
	return atenuacionConstante;
}

float TLuz::getAtenuacionLiniar()
{
	return atenuacionLinial;
}

float TLuz::getAtenuacionCuadratica()
{
	return atenuacionCuadratica;
}

glm::vec3 TLuz::getDirectionXView(const glm::mat4 & matriz)
{
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(matriz, scale, rotation, translation, skew, perspective);

	return translation;
}
