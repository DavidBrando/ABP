#pragma once
#include "TEntidad.h"
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>

class TLuz :
	public TEntidad
{
public:
	TLuz(bool estaActiva = false, bool local = false, bool foco = false, float fAmbient[] = NULL, float color[] = NULL, float dicLuz[] = NULL, float dicCono[] = NULL, float sCosCutOff = 0.f, float sExponet = 0.f, float ateCos = 0.f, float ateLin = 0.f, float ateCua = 0.f);
	~TLuz();
	void beginDraw() override;
	void beginDraw(openGLShader&, const glm::mat4&, const glm::mat4&, double) override;
	void endDraw() override;
	void renderLuz(const glm::mat4&, openGLShader&, const glm::mat4&, const glm::mat4&);
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
	void setDireccionConoView(float v[]);
	glm::vec3 getAmbient();
	glm::vec3 getColor();
	glm::vec3 getDireccionLuz();
	glm::vec3 getDireccionCono();
	glm::vec3 getDireccionConoView();
	float getCosCutOffFoco();
	float getExponentFoco();
	float getAtenuacionConstante();
	float getAtenuacionLiniar();
	float getAtenuacionCuadratica();
private:
	glm::vec3 getDirectionXView(const glm::mat4 &);
	static unsigned int nLuces;
	unsigned int id;
	bool activa;
	bool esLocal;
	bool esFoco;
	glm::vec3 ambient;
	glm::vec3 color;
	glm::vec3 direccionLuz;
	glm::vec3 direccionCono;
	glm::vec3 direccionConoView;
	glm::vec3 vectorMedio;
	float spotCosCutOff;
	float spotExponent;
	float atenuacionConstante;
	float atenuacionLinial;
	float atenuacionCuadratica;
};

