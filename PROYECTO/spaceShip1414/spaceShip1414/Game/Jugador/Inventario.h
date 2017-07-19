#pragma once

#include <iostream>
#include <vector>
#include<string>

class Objetos;
class Llave;

class Inventario
{

public:
	Inventario();
	~Inventario();
	void addObjeto(Objetos*);
	Objetos* usarObjeto(int);
	Llave* buscaLlave(std::string nomLlave);
	void mostrarInventario();
	void deleteObj(Objetos *obj);


private:

	std::vector<Objetos*> inventary;

};

