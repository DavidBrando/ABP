#pragma once

#include<vector>
//#define manejador MaquinaEstados::getInstancia()

class Estados;
class Entity2D;

class MaquinaEstados
{

private:
	std::vector<Estados*> listaEstados;
	Estados* estadoActivo;
	
/*public:
	static MaquinaEstados& getInstancia(void)
	{
		static MaquinaEstados instancia;
		return instancia;
	}*/

public:
	MaquinaEstados();
	 ~MaquinaEstados(void);
	void addEstado(Estados* nombreEstados, bool activo=false);
	void cambiaEstado(const std::string nombre);
	Estados* getEstadoActivo();
	Estados* getEstado(const std::string nombre);
	
};

