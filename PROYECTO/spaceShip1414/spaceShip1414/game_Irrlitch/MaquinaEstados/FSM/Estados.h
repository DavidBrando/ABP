#pragma once

#include <string>

class Estados
{
private:
	std::string nombreEstado;
	bool estadoActivo;
	bool primerEstado;

public:
	Estados();
	Estados(std::string nuevoEstado);
	~Estados();
	std::string getEstado();
	bool getEstadoActivo();
	void setEstadoActivo(bool activo);
	virtual void inicializarEstado();
	virtual void limpiarEstado();


};

