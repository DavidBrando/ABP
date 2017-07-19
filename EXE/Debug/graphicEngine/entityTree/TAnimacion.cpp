#include "TAnimacion.h"
#include <iostream>
#include "../resourceManager/TRecursoMalla.h"
#include "../resourceManager/TGestorRecursos.h"
#include "..\framework\openGLShader.h"
#include <glm\gtc\matrix_inverse.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\mat3x3.hpp>


TAnimacion::TAnimacion()
{
}

TAnimacion::TAnimacion(std::string path, TGestorRecursos * gestor, unsigned int num)
{
	cargarMalla(path, gestor, num);
}

TAnimacion::~TAnimacion()
{
	for (int i = 0; i < numeroFrame; i++) {
		delete[] animacion[i];
	}

	delete[] animacion;
}

void TAnimacion::cargarMalla(std::string path, TGestorRecursos * gestor, unsigned int num)
{
	animacion = new TRecursoMalla*[num];
	size_t punto = path.find_last_of(".");
	std::string ruta = punto == std::string::npos ? path : path.substr(punto);
	std::cout << "LA PATH SURMANO: " << path << std::endl;

	std::cout <<"LA RUTA SURMANO: "<<ruta << std::endl;
	std::cout <<"MAS RUTA: "<< ruta << std::endl;
	for (unsigned int i = 0; i < num; i++)
	{
		animacion[i] = static_cast<TRecursoMalla*>(gestor->getRecurso((ruta+std::to_string(i)+".obj"), 1));
	}
	ultimoFrame = 0;
	numeroFrame = num;
}

void TAnimacion::beginDraw()
{
	animacion[ultimoFrame]->draw();
	if (ultimoFrame == numeroFrame - 1) 
	{
		ultimoFrame = 0;
	}
	else 
	{
		ultimoFrame++;
	}
}

void TAnimacion::beginDraw(openGLShader& shader, const glm::mat4& view, const glm::mat4& proyection, double deltaTime)
{
	glm::mat4 MV = view * matrizActual;
	glm::mat4 MVP = proyection * MV;
	glm::mat3 N = glm::inverseTranspose(glm::mat3(MV));

	glUniformMatrix4fv(shader.getUniformLocation("mvp_matrix"), 1, GL_FALSE, glm::value_ptr(MVP));
	glUniformMatrix4fv(shader.getUniformLocation("mv_matrix"), 1, GL_FALSE, glm::value_ptr(MV));
	glUniformMatrix3fv(shader.getUniformLocation("n_matrix"), 1, GL_FALSE, glm::value_ptr(N));
	animacion[ultimoFrame]->draw(shader.getProgram());
	if (deltaTime >= 0.0041667) {
		if (ultimoFrame == numeroFrame - 1)
		{
			ultimoFrame = 0;
		}
		else
		{
			ultimoFrame++;
		}
	}
}

void TAnimacion::endDraw()
{
}
