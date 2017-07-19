#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>

class TNodo;
class TGestorRecursos;
class TEntidad;
class TCamara;
class TTransform;
class TLuz;
class TMalla;
class TAnimacion;
class openGLShader;
class TGraphicEngine
{
public:
	TGraphicEngine(float, float);
	~TGraphicEngine();
	bool iniciarGraphicEngine();
	TNodo* crearNodo(TNodo*, TEntidad*);
	TTransform* crearTransform();
	TCamara* crearCamara(bool, float, float, float, float, float, float, bool a = false);
	TCamara* crearCamaraS(bool, float, float, float, float, float, float, bool a = false);
	TCamara* crearCamara(bool, float, float, float, float, bool a = false);
	TCamara* crearCamaraS(bool, float, float, float, float, bool a = false);
	TCamara* crearCamara(float fovy, float aspect, float nearr, float farr);
	TLuz* crearLuz(bool estaActiva = false, bool local = false, bool foco = false, float fAmbient[] = NULL, float color[] = NULL, float dicLuz[] = NULL, float dicCono[] = NULL, float sCosCutOff = 0.f, float sExponet = 0.f, float ateCos = 0.f, float ateLin = 0.f, float ateCua = 0.f);
	TMalla* crearMalla(std::string);
	TAnimacion* crearAnimacion(std::string, unsigned int);
	TNodo* nodoRaiz();
	void addRegistroLuz(TNodo*);
	void addRegistroCamara(TNodo*);
	void cargarNuevaAnimacion(TNodo * padre, std::string path, unsigned int frames);
	void cargarNuevaMalla(TNodo * padre, std::string path);
	TNodo * addAnimacion(std::string path = "", unsigned int frames = 25, TNodo * nodoPadre = nullptr);
	TNodo * addMalla(std::string path = "", TNodo * nodoPadre = nullptr);
	TNodo * addCamara(char tipo = 0, bool per = false, bool act = false, TNodo * nodoPadre = nullptr, float x = 45.0f, float y = 0.1f, float z = 1000.0f, float a = 0.0f, float b = 10.0f, float c = 10.0f);
	TNodo * addCamaraLibre(bool activa = false);
	TNodo * addCamaraParalelaFija(bool activa = false);
	TNodo * addCamaraParalelaSeguidora(bool activa = false, TNodo * nodoPadre = nullptr);
	TNodo * addCamaraPerspectivaFija(bool activa = false);
	TNodo * addCamaraPerspectivaSeguidora(bool activa = false, TNodo * nodoPadre = nullptr);
	TNodo * addLuz(TNodo * nodoPadre = nullptr);

	void trasladar(TNodo *, float, float, float);
	void rotar(TNodo *, float, float, float, float);
	void rotarYPR(TNodo *, float, float, float);
	void escalar(TNodo *, float, float, float);
	void resetTransform(TNodo *, char);
	glm::vec3 getPosicion(TNodo *);
	glm::vec3 getRotacion(TNodo *);
	glm::vec3 getEscalado(TNodo *);
	TNodo * getPadreX(TNodo *, char p = 0);
	glm::mat4 getView();
	glm::mat4 getProjection();
	void look(TNodo * nodo, glm::vec3 eye, glm::vec3 tar, glm::vec3 mat);
	glm::mat4 getInverseProjectionCamaraActive();
	void onresize(int, int);
	void cambiarCamaraActiva(char m, void * dirCam);
	void buscarNodoPadre(TNodo * n);
	void draw(double);
private:
	glm::vec3 descomponerMatriz(TNodo *, char);
	void camaraActivada();
	void luzActivada();

	openGLShader * shader;
	TNodo* escena;
	TGestorRecursos* gestorRecursos;
	TCamara* camaraActiva;
	TLuz* luzActiva;
	std::vector<TNodo*> registroCamaras;
	std::vector<TNodo*> registroLuces;
	float aspect_ratio, width, height;
};

