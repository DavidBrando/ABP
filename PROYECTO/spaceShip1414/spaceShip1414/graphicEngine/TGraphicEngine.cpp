#include "TGraphicEngine.h"
#include <iostream>
#include <algorithm>
#include <glm\gtc\matrix_inverse.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\matrix_decompose.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "framework\openGLShader.h"
#include "resourceManager\TGestorRecursos.h"
#include "entityTree\TEntidad.h"
#include "entityTree\TNodo.h"
#include "entityTree\TTransform.h"
#include "entityTree\TCamara.h"
#include "entityTree\TLuz.h"
#include "entityTree\TMalla.h"
#include "entityTree\TAnimacion.h"
#include "../Game/Camara.h"

TGraphicEngine::TGraphicEngine(float w, float h) : registroCamaras(), registroLuces(), width{ w }, height{ h }
{
	aspect_ratio = w / h;
	shader = new openGLShader();
}

TGraphicEngine::~TGraphicEngine()
{
	delete escena;
	escena = nullptr;
	delete gestorRecursos;
	gestorRecursos = nullptr;
	delete shader;
	shader = nullptr;
	camaraActiva = nullptr;
	luzActiva = nullptr;
	registroCamaras.clear();
	registroLuces.clear();
	std::cout << "Facade Destroted" << std::endl;
}

bool TGraphicEngine::iniciarGraphicEngine()
{
	
	escena = new TNodo(nullptr);
	gestorRecursos = new TGestorRecursos();
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 0.8f);
	glViewport(0, 0, width, height);
	
	shader->compile("graphicEngine/Shader/spaceShip1414.vs", "graphicEngine/Shader/spaceShip1414.fs");
	return true;
}

TNodo * TGraphicEngine::crearNodo(TNodo* padre, TEntidad* entidad)
{
	return new TNodo(padre, entidad);
}

TTransform * TGraphicEngine::crearTransform()
{
	return new TTransform();
}

TCamara * TGraphicEngine::crearCamara(bool pe, float left, float right, float bottom, float top, float nearr, float farr, bool a)
{
	TCamara* c = new TCamara(pe, left, right, bottom, top, nearr, farr);
	if (a)
	{
		c->activar();
	}
	return c;
}

TCamara * TGraphicEngine::crearCamaraS(bool pe, float left, float right, float bottom, float top, float nearr, float farr, bool a)
{
	TCamara* c = new TCamara(pe, left, right, bottom, top, nearr, farr);
	if (a)
	{
		c->activar();
	}
	c->setTipo(2);
	return c;
}

TCamara * TGraphicEngine::crearCamara(bool pe, float fovy, float aspect, float nearr, float farr, bool a)
{
	TCamara * c = new TCamara(pe, fovy, aspect, nearr, farr);
	if (a)
	{
		c->activar();
	}
	return c;
}

TCamara * TGraphicEngine::crearCamaraS(bool pe, float fovy, float aspect, float nearr, float farr, bool a)
{
	TCamara* c = new TCamara(pe, fovy, aspect, nearr, farr);
	if (a)
	{
		c->activar();
	}
	else
		c->desactivar();

	c->setTipo(2);
	return c;
}

TCamara * TGraphicEngine::crearCamara(float fovy, float aspect, float nearr, float farr)
{
	return new TCamara(fovy, aspect, nearr, farr);
}

TLuz * TGraphicEngine::crearLuz(bool estaActiva, bool local, bool foco, float fAmbient[], float color[], float dicLuz[], float dicCono[], float sCosCutOff, float sExponet, float ateCos, float ateLin, float ateCua)
{
	TLuz* l = new TLuz(estaActiva, local, foco, fAmbient, color, dicLuz, dicCono, sCosCutOff, sExponet, ateCos, ateLin, ateCua);

	return l;
}

TMalla * TGraphicEngine::crearMalla(std::string fichero)
{
	return new TMalla(fichero, gestorRecursos);
}

TAnimacion * TGraphicEngine::crearAnimacion(std::string fichero, unsigned int num)
{
	return new TAnimacion(fichero, gestorRecursos, num);
}

TNodo * TGraphicEngine::nodoRaiz()
{
	return escena;
}

void TGraphicEngine::addRegistroLuz(TNodo* l)
{
	if (l)
	{
		registroLuces.push_back(l);
	}
}

void TGraphicEngine::addRegistroCamara(TNodo * c)
{
	if (c)
	{
		registroCamaras.push_back(c);
	}
}

TNodo * TGraphicEngine::addAnimacion(std::string path, unsigned int frames, TNodo * nodoPadre)
{
	TTransform * rotation = crearTransform();
	TTransform * scale = crearTransform();
	TTransform * translation = crearTransform();
	TNodo* nodoRotation;
	TNodo* nodoAnimacion;
	if (nodoPadre == nullptr)
	{
		nodoRotation = crearNodo(nodoRaiz(), rotation);

		TNodo* nodoScale = crearNodo(nodoRotation, scale);
		TNodo* nodoTranslation = crearNodo(nodoScale, translation);
		if (path.empty())
		{
			nodoAnimacion = crearNodo(nodoTranslation, crearAnimacion("resourse/models/untitled.obj", 1));
		}
		else
		{
			nodoAnimacion = crearNodo(nodoTranslation, crearAnimacion(path, frames));
		}
	}
	else
	{
		nodoAnimacion = crearNodo(nodoPadre, crearAnimacion(path, frames));
	}


	return nodoAnimacion;
}

void TGraphicEngine::cargarNuevaAnimacion(TNodo* padre, std::string path, unsigned int frames)
{
	padre->setEntidad(crearAnimacion(path, frames));
}

void TGraphicEngine::cargarNuevaMalla(TNodo* padre, std::string path) {
	padre->setEntidad(crearMalla(path));
}

TNodo * TGraphicEngine::addMalla(std::string path, TNodo * nodoPadre)
{
	TTransform * rotation = crearTransform();
	TTransform * scale = crearTransform();
	TTransform * translation = crearTransform();
	TNodo* nodoRotation;
	TNodo* nodoMalla;
	if (nodoPadre == nullptr)
	{
		nodoRotation = crearNodo(nodoRaiz(), rotation);
		TNodo* nodoScale = crearNodo(nodoRotation, scale);
		TNodo* nodoTranslation = crearNodo(nodoScale, translation);
		if (path.empty())
		{
			nodoMalla = crearNodo(nodoTranslation, crearMalla("resourse/models/untitled.obj"));
		}
		else
		{
			nodoMalla = crearNodo(nodoTranslation, crearMalla(path));
		}
	}
	else
	{
		nodoMalla = crearNodo(nodoPadre, crearMalla(path));
	}

	return nodoMalla;
}

TNodo * TGraphicEngine::addCamara(char tipo, bool per, bool act, TNodo * nodoPadre, float x, float y, float z, float a, float b, float c)
{
	TTransform *transfRC = crearTransform();
	TTransform *transfEC = crearTransform();
	TTransform *transfTC = crearTransform();
	TNodo* nodoTransfRC = crearNodo(nodoPadre, transfRC);
	TNodo* nodoTransfEC = crearNodo(nodoTransfRC, transfEC);
	TNodo* nodoTransfTC = crearNodo(nodoTransfEC, transfTC);
	TNodo* nodoCamara;
	if (tipo == 2) {
		if (!per) {
			nodoCamara = crearNodo(nodoTransfTC, crearCamaraS(per, x, y, z, a, b, c, act));
		}
		else {
			nodoCamara = crearNodo(nodoTransfTC, crearCamaraS(per, x, y, z, a, act));
		}
	}
	else if (tipo == 1) {
		if (!per) {
			nodoCamara = crearNodo(nodoTransfTC, crearCamaraS(per, x, y, z, a, b, c, act));
		}
		else {
			nodoCamara = crearNodo(nodoTransfTC, crearCamaraS(per, x, y, z, a, act));
		}
	}
	else
	{
		nodoCamara = crearNodo(nodoTransfTC, crearCamara(x, y, z, a));
	}
	addRegistroCamara(nodoCamara);
	return nodoCamara;
}

TNodo * TGraphicEngine::addCamaraLibre(bool activa)
{
	TTransform *transfRC = crearTransform();
	TTransform *transfEC = crearTransform();
	TTransform *transfTC = crearTransform();
	TNodo* nodoTransfRC = crearNodo(nodoRaiz(), transfRC);
	TNodo* nodoTransfEC = crearNodo(nodoTransfRC, transfEC);
	TNodo* nodoTransfTC = crearNodo(nodoTransfEC, transfTC);
	TNodo* nodoCamara;
	nodoCamara = crearNodo(nodoTransfTC, crearCamara(45.0f, aspect_ratio, 0.1f, 300.0f));
	addRegistroCamara(nodoCamara);
	return nodoCamara;
}

TNodo * TGraphicEngine::addCamaraParalelaFija(bool activa)
{
	TTransform *transfRC = crearTransform();
	TTransform *transfEC = crearTransform();
	TTransform *transfTC = crearTransform();
	TNodo* nodoTransfRC = crearNodo(nodoRaiz(), transfRC);
	TNodo* nodoTransfEC = crearNodo(nodoTransfRC, transfEC);
	TNodo* nodoTransfTC = crearNodo(nodoTransfEC, transfTC);
	TNodo* nodoCamara;
	nodoCamara = crearNodo(nodoTransfTC, crearCamara(false, 0.0f, 1.0f*(width / 4), -1.0f*(height / 4), 0.0f, -370.0f, 370.0f, activa));
	addRegistroCamara(nodoCamara);
	return nodoCamara;
}

TNodo * TGraphicEngine::addCamaraParalelaSeguidora(bool activa, TNodo * nodoPadre)
{
	TTransform *transfRC = crearTransform();
	TTransform *transfEC = crearTransform();
	TTransform *transfTC = crearTransform();
	TNodo* nodoTransfRC = crearNodo(nodoPadre, transfRC);
	TNodo* nodoTransfEC = crearNodo(nodoTransfRC, transfEC);
	TNodo* nodoTransfTC = crearNodo(nodoTransfEC, transfTC);
	TNodo* nodoCamara;
	nodoCamara = crearNodo(nodoTransfTC, crearCamaraS(false, 0.0f, 1.0f*(width / 4), -1.0f*(height / 4), 0.0f, 50.0f, 370.0f, activa));
	addRegistroCamara(nodoCamara);
	rotarYPR(nodoCamara, 15.0f, 0.0f, 0.0f);
	rotarYPR(nodoCamara, 0.0f, -30.0f, 0.0f);
	trasladar(nodoCamara, -240.0f, 128.0f, 0.0f);
	return nodoCamara;
}

TNodo * TGraphicEngine::addCamaraPerspectivaFija(bool activa)
{
	TTransform *transfRC = crearTransform();
	TTransform *transfEC = crearTransform();
	TTransform *transfTC = crearTransform();
	TNodo* nodoTransfRC = crearNodo(nodoRaiz(), transfRC);
	TNodo* nodoTransfEC = crearNodo(nodoTransfRC, transfEC);
	TNodo* nodoTransfTC = crearNodo(nodoTransfEC, transfTC);
	TNodo* nodoCamara;
	nodoCamara = crearNodo(nodoTransfTC, crearCamara(true, 45.0f, aspect_ratio, 0.1f, 400.f, activa));
	addRegistroCamara(nodoCamara);
	return nodoCamara;
}

TNodo * TGraphicEngine::addCamaraPerspectivaSeguidora(bool activa, TNodo * nodoPadre)
{
	TTransform *transfRC = crearTransform();
	TTransform *transfEC = crearTransform();
	TTransform *transfTC = crearTransform();
	TNodo* nodoTransfRC = crearNodo(nodoPadre, transfRC);
	TNodo* nodoTransfEC = crearNodo(nodoTransfRC, transfEC);
	TNodo* nodoTransfTC = crearNodo(nodoTransfEC, transfTC);
	TNodo* nodoCamara;
	nodoCamara = crearNodo(nodoTransfTC, crearCamaraS(true, 45.f, aspect_ratio, 0.1f, 300.f, activa));
	addRegistroCamara(nodoCamara);

	return nodoCamara;
}

TNodo * TGraphicEngine::addLuz(TNodo * nodoPadre)
{
	TTransform *transfRL = crearTransform();
	TTransform *transfEL = crearTransform();
	TTransform *transfTL = crearTransform();
	TNodo* nodoTransfRL;
	if (nodoPadre == nullptr)
	{
		nodoTransfRL = crearNodo(nodoRaiz(), transfRL);
	}
	else
	{
		nodoTransfRL = crearNodo(nodoPadre, transfRL);
	}
	TNodo* nodoTransfEL = crearNodo(nodoTransfRL, transfEL);
	TNodo* nodoTransfTL = crearNodo(nodoTransfEL, transfTL);
	TNodo* nodoLuz = crearNodo(nodoTransfTL, crearLuz());
	addRegistroLuz(nodoLuz);
	return nodoLuz;
}

void TGraphicEngine::trasladar(TNodo * nodo, float x, float y, float z)
{
	TTransform * t = static_cast<TTransform*>(nodo->getPadre()->getEntidad());
	t->trasladar(x, y, z);
}

void TGraphicEngine::rotar(TNodo * nodo, float a, float x, float y, float z)
{
	TTransform * r = static_cast<TTransform*>(nodo->getPadre()->getPadre()->getPadre()->getEntidad());
	r->rotar(a, x, y, z);
}

void TGraphicEngine::rotarYPR(TNodo * nodo, float y, float p, float r)
{
	TTransform * ro = static_cast<TTransform*>(nodo->getPadre()->getPadre()->getPadre()->getEntidad());
	ro->rotarYPR(y, p, r);
}

void TGraphicEngine::escalar(TNodo * nodo, float x, float y, float z)
{
	TTransform * e = static_cast<TTransform*>(nodo->getPadre()->getPadre()->getEntidad());
	e->escalar(x, y, z);
}

void TGraphicEngine::resetTransform(TNodo * nodo, char tipo)
{
	switch (tipo)
	{
	case 't':
		(static_cast<TTransform*>(nodo->getPadre()->getEntidad()))->resetMatriz();
		break;
	case 'e':
		(static_cast<TTransform*>(nodo->getPadre()->getPadre()->getEntidad()))->resetMatriz();
		break;
	case 'r':
		(static_cast<TTransform*>(nodo->getPadre()->getPadre()->getPadre()->getEntidad()))->resetMatriz();
		break;
	default:
		std::cout << "No se puede reniciar la TTransformacion" << std::endl;
	}
}

glm::vec3 TGraphicEngine::getPosicion(TNodo * nodo)
{
	return descomponerMatriz(nodo, 't');
}

glm::vec3 TGraphicEngine::getRotacion(TNodo * nodo)
{
	return descomponerMatriz(nodo, 'r');
}

glm::vec3 TGraphicEngine::getEscalado(TNodo * nodo)
{
	return descomponerMatriz(nodo, 'e');
}

TNodo * TGraphicEngine::getPadreX(TNodo * hijo, char padre)
{
	if (padre == 0 || hijo->getPadre() == nullptr) {
		return hijo->getPadre();
	}
	else
	{
		return getPadreX(hijo->getPadre(), padre - 1);
	}
}

void TGraphicEngine::look(TNodo * nodo, glm::vec3 eye, glm::vec3 tar, glm::vec3 mat)
{
	TTransform * t = static_cast<TTransform*>(nodo->getPadre()->getPadre()->getPadre()->getEntidad());
	t->lookat(eye, tar, mat);
}

glm::mat4 TGraphicEngine::getInverseProjectionCamaraActive()
{
	return camaraActiva->getInverseProjection();
}

void TGraphicEngine::draw(double deltaTime)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	shader->use();
	camaraActivada();
	luzActivada();
	escena->draw(*shader, camaraActiva->getView(), camaraActiva->getProjectionMatrix(), deltaTime);
	shader->unUse();
}

void TGraphicEngine::resetShader()
{
	delete shader;
	shader = new openGLShader();
	shader->compile("graphicEngine/Shader/spaceShip1414.vs", "graphicEngine/Shader/spaceShip1414.fs");
}

glm::vec3 TGraphicEngine::descomponerMatriz(TNodo * nodo, char tipo)
{
	glm::mat4 transform = (static_cast<TTransform*>(nodo->getPadre()->getEntidad()))->getMatriz() * (static_cast<TTransform*>(nodo->getPadre()->getPadre()->getEntidad()))->getMatriz() * (static_cast<TTransform*>(nodo->getPadre()->getPadre()->getPadre()->getEntidad()))->getMatriz();
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(transform, scale, rotation, translation, skew, perspective);
	rotation = glm::conjugate(rotation);
	glm::vec3 rotEulerAngle = glm::eulerAngles(rotation);
	switch (tipo)
	{
	case 't':
		return translation;
		break;
	case 'e':
		return scale;
		break;
	case 'r':
		return rotEulerAngle;
		break;
	default:
		std::cout << "Error al descomponer" << std::endl;
		return glm::vec3();
	}
}

void TGraphicEngine::onresize(int width, int height)
{
	aspect_ratio = std::max(0.0f, width / (float)height);
	glViewport(0, 0, width, height);
}

void TGraphicEngine::camaraActivada()
{
	for (size_t i = 0; i < registroCamaras.size(); i++)
	{
		if (static_cast<TCamara*>(registroCamaras.at(i)->getEntidad())->getActiva())
		{
			glm::mat4 t = static_cast<TTransform*>(registroCamaras.at(i)->getPadre()->getEntidad())->getMatriz();
			glm::mat4 e = static_cast<TTransform*>(registroCamaras.at(i)->getPadre()->getPadre()->getEntidad())->getMatriz();
			glm::mat4 r = static_cast<TTransform*>(registroCamaras.at(i)->getPadre()->getPadre()->getPadre()->getEntidad())->getMatriz();
			if (static_cast<TCamara*>(registroCamaras.at(i)->getEntidad())->getTipo() == 2)
			{
				glm::mat4 tt = static_cast<TTransform*>(registroCamaras.at(i)->getPadre()->getPadre()->getPadre()->getPadre()->getEntidad())->getMatriz();
				static_cast<TCamara*>(registroCamaras.at(i)->getEntidad())->setView(tt*t*(e*r));
			}
			else
			{
				static_cast<TCamara*>(registroCamaras.at(i)->getEntidad())->setView(t*(e*r));
			}
			camaraActiva = static_cast<TCamara*>(registroCamaras.at(i)->getEntidad());
			break;
		}
	}
}

void TGraphicEngine::luzActivada()
{
	for (size_t i = 0; i < registroLuces.size(); i++) {
		if (static_cast<TLuz*>(registroLuces.at(i)->getEntidad())->estaActiva())
		{
			glm::mat4 t = static_cast<TTransform*>(registroLuces.at(i)->getPadre()->getEntidad())->getMatriz();
			glm::mat4 e = static_cast<TTransform*>(registroLuces.at(i)->getPadre()->getPadre()->getEntidad())->getMatriz();
			glm::mat4 r = static_cast<TTransform*>(registroLuces.at(i)->getPadre()->getPadre()->getPadre()->getEntidad())->getMatriz();
			static_cast<TLuz*>(registroLuces.at(i)->getEntidad())->renderLuz(t*(e*r), *shader, camaraActiva->getView(), camaraActiva->getProjectionMatrix());
			luzActiva = static_cast<TLuz*>(registroLuces.at(i)->getEntidad());
		}
	}
}

glm::mat4 TGraphicEngine::getView()
{
	return camaraActiva->getView();
}

glm::mat4 TGraphicEngine::getProjection()
{
	if (camaraActiva != nullptr) {
		return camaraActiva->getProjectionMatrix();
	}
	else {
		return glm::mat4(1.0f);
	}
}

void TGraphicEngine::cambiarCamaraActiva(char m, void * dirCam)
{
	if (camaraActiva) {
		camaraActiva->desactivar();
	}
	if (registroCamaras.size() > m) {
		Camara * cam = static_cast<Camara*>(dirCam);
		cam->getTCamara()->activar();
		camaraActiva = cam->getTCamara();
	}
}

void TGraphicEngine::buscarNodoPadre(TNodo* n)
{
	TNodo* aux = n->getPadre()->getPadre()->getPadre();
	TNodo* godfather = aux->getPadre();
	godfather->removeHijo(aux);
}
