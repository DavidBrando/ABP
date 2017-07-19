#pragma once
#include <string>

class estadosJuego
{
private:
	std::string nombreEstado;
	bool estadoActivo;
public:
	estadosJuego();
	estadosJuego(std::string nuevoEstado);
	~estadosJuego();
	std::string getEstado();
	bool getEstadoActivo();
	void setEstadoActivo(bool activo);
	virtual void inicializarEstado();
	virtual bool limpiarEstado();
	virtual void handler(void * event, void * window, void * manager);
	virtual void update(double deltatime, void * window, void * manager);
	virtual void render(void * window);
	virtual void resize(float width, float height);
};

