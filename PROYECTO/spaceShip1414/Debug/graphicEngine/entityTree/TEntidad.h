#pragma once
#include <glm\mat4x4.hpp>
class openGLShader;
class TEntidad
{
public:
	virtual void beginDraw() = 0;
	virtual void beginDraw(openGLShader&, const glm::mat4&, const glm::mat4&) = 0;
	virtual void endDraw() = 0;
protected:
	static glm::mat4 matrizActual;
};

