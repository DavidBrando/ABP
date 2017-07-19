#pragma once
#include <vector>

class estadosJuego;
class MaquinaEstadosJuego
{

private:
	std::vector<estadosJuego *> listaEstados;
	estadosJuego * estadoActivo;
	void activarEstado(estadosJuego * nombreEstados);
	bool reniciar;
public:
	MaquinaEstadosJuego();
	 ~MaquinaEstadosJuego(void);
	void addEstado(estadosJuego * nombreEstados, bool activo=false);
	void cambiaEstado(const std::string nombre);
	estadosJuego * getEstadoActivo();
	estadosJuego * getEstado(const std::string nombre);
	void borrarEstado(const std::string nombre);
	bool reniciarEstado();
};

