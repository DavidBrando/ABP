#pragma once
#include "TEntidad.h"
#include <glm\vec3.hpp>

class TLuz :
	public TEntidad
{
public:
	TLuz();
	TLuz(float,float, float);
	~TLuz();
	void setIntensidad(float, float, float);
	glm::vec3 getIntensidad();
	void beginDraw() override;
	void beginDraw(openGLShader&, const glm::mat4&, const glm::mat4&) override;
	void endDraw() override;
	void activar();
	void desactivar();
	bool getActiva();
	void renderLuz(const glm::mat4&, openGLShader&, const glm::mat4&, const glm::mat4&);
private:
	glm::vec3 intensidad;
	bool activa;
};

