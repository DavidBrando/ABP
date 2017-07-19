#pragma once
#include <string>
class TRecurso
{
public:
	TRecurso();
	TRecurso(std::string);
	~TRecurso();
	std::string getNombre();
	void setNombre(std::string);
	virtual bool cargarFichero(std::string) = 0;
	virtual void draw() = 0;
protected:
	std::string nombre;
};

