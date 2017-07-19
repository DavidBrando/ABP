#pragma once
#include <glm\vec3.hpp>
class TTransform;
class TGraphicEngine;
class TNodo;
class TCamara;
class player;

class Camara
{
public:
	
	Camara(TGraphicEngine * motorApp, char tipo, bool activa = false, player* jugador = nullptr);
	Camara(TGraphicEngine * motorApp, int ident, bool activa, bool move, glm::vec3 pos, glm::vec3 rot, glm::vec3 escala);
	Camara(TGraphicEngine * motorApp, int ident, bool movimiento, glm::vec3 pos, glm::vec3 rot, glm::vec3 escala, player * jugador);

	~Camara();
	int getId();
	float getVelocity();
	float getYaw();
	float getPitch();
	void rotation(TGraphicEngine *, float, float, float, float);
	void rotationYPR(TGraphicEngine *, float, float, float);
	void scale(TGraphicEngine *, float, float, float);
	void translation(TGraphicEngine *, float, float, float);
	float anguloEntreDosVectores(glm::vec3 u, glm::vec3 v);
	void updateCam(TGraphicEngine * motorApp, glm::vec3 posPers, int tecla);
	float getAnguloInicial();

	float getRotY();

	void setVelocity(float);
	void setYaw(float);
	void setPitch(float);
	TCamara* getTCamara();
	TNodo* getNodo();
	bool getMovil();

private:
	float velocity;
	float yaw;
	float pitch;
	TNodo * nodo;
	bool activa;
	glm::vec3 p;
	glm::vec3 r;
	bool fija;
	bool movil;
	int id;
	float anguloInicial, rotAnterior, rotX;
};

