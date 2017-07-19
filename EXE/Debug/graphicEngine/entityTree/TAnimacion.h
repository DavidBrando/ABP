#pragma once
#include "TEntidad.h"
#include <vector>
#include <string>
class TRecursoMalla;
class TGestorRecursos;

class TAnimacion :
	public TEntidad
{
public:
	TAnimacion();
	TAnimacion(std::string path, TGestorRecursos* gestor, unsigned int num);
	~TAnimacion();
	void cargarMalla(std::string, TGestorRecursos*, unsigned int);
	void beginDraw() override;
	void beginDraw(openGLShader&, const glm::mat4&, const glm::mat4&, double) override;
	void endDraw() override;
private:
	TRecursoMalla** animacion;
	unsigned int ultimoFrame;
	unsigned int numeroFrame;
};

