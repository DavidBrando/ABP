#pragma once
#include <glm\vec3.hpp>

class TGraphicEngine;
class TNodo;

class Luces

{
public:
	Luces(TGraphicEngine * motorApp, glm::vec3 tras, glm::vec3 r, glm::vec3 sca, int iden);
	~Luces();
	float getVelocity();
	void setVelocity(float);
	void activar();
	void desactivar();
	bool estaActiva();
	bool esAmbiental();
	bool esPuntual();
	bool esFocal();
	void setLocal(bool l);
	void setFoco(bool f);
	void setAmbient(float v[]);
	void setColor(float v[]);
	void setDireccionLuz(float v[]);
	void setDireccionCono(float v[]);
	void setCosCutOffFoco(float f);
	void setExponentFoco(float f);
	void setAtenuacionConstante(float f);
	void setAtenuacionLiniar(float f);
	void setAtenuacionCuadratica(float f);
	glm::vec3 getAmbient();
	glm::vec3 getColor();
	glm::vec3 getDireccionLuz();
	glm::vec3 getDireccionCono();
	float getCosCutOffFoco();
	float getExponentFoco();
	float getAtenuacionConstante();
	float getAtenuacionLiniar();
	float getAtenuacionCuadratica();
	void rotation(TGraphicEngine *, float, float, float, float);
	void rotationYPR(TGraphicEngine *, float, float, float);
	void scale(TGraphicEngine *, float, float, float);
	void translation(TGraphicEngine *, float, float, float);
	int getID();
	glm::vec3 getPos();
	TNodo* getNodo();

private:
	float velocity;
	TNodo* nodo;
	int ID;
	glm::vec3 pos;
};

