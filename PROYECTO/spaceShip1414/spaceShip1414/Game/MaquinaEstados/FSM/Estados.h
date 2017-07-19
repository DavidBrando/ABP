#pragma once

#include <string>

class Estados
{
private:
	std::string nombreEstado;
	bool estadoActivo;
	bool primerEstado;
	std::string pathAnimacion;

public:
	Estados();
	Estados(std::string nuevoEstado);
	~Estados();
	std::string getEstado();
	bool getEstadoActivo();
	void setEstadoActivo(bool activo);
	virtual void inicializarEstado();
	virtual void limpiarEstado();
	std::string getPathAnimacion();
	void asignarPath(std::string path);


};

