
#include "Inventario.h"
#include "../Escenario/ObjConsumables/Objetos.h"
#include "../Escenario//ObjConsumables/Llave.h"
#include "../Escenario//ObjConsumables/Botiquines.h"




Inventario::Inventario()
{
}


Inventario::~Inventario()
{
	inventary.clear();
}

void Inventario::addObjeto(Objetos * obj)
{
	inventary.push_back(obj);
	mostrarInventario();
}

Objetos* Inventario::usarObjeto(int tipo)
{
	
	for(std::size_t i = 0; i < inventary.size(); i++) {

		if(inventary[i]->getID() == tipo) {
			 
			return inventary[i];
		}


	}
	return nullptr;
}

Llave * Inventario::buscaLlave(std::string nomLlave)
{
	for (std::size_t i = 0; i < inventary.size(); i++) {

		//1 llave
		if(inventary.at(i)->getID() == 1) {

		Llave *key = static_cast<Llave*>(inventary[i]);

			if (key->getNombreHabitacion().compare(nomLlave) == 0) {

				std::cout << "------ ENTONTRADOOOO" << std::endl;

				return key;
			}

		}
	}

	return nullptr;
}

void Inventario::mostrarInventario()
{

	for (std::size_t i = 0; i < inventary.size(); i++) {

		if (inventary.at(i)->getID() == 0) {
			std::cout << std::endl;
			std::cout << "///////////" << std::endl;
			std::cout << "BOTIQUIN" << std::endl;
			std::cout << "///////////" << std::endl;
			Botiquines *bot = static_cast<Botiquines*>(inventary[i]);
			std::cout << "VIDA: " << bot->getVida() << std::endl;
			std::cout << "ESTADO: " << bot->getVivo() << std::endl;

		}

		else {
			std::cout << "///////////" << std::endl;
			std::cout << "LLAVE" << std::endl;
			std::cout << "///////////" << std::endl;
			Llave *l = static_cast<Llave*>(inventary[i]);
			std::cout << "HAB: " << l->getNombreHabitacion() << std::endl;
			std::cout << "ESTADO: " << l->getVivo() << std::endl;

			std::cout << std::endl;

		}

	}

	std::cout << "///////////" << std::endl;
	std::cout << "NADA :D " << std::endl;
	std::cout << "///////////" << std::endl;
}

void Inventario::deleteObj(Objetos * obj)
{

	for (std::vector<Objetos*>::iterator it = inventary.begin(); it != inventary.end();) {
		if ((*it)!= NULL && (*it) == obj) {

			std::cout << "///////////" << std::endl;
			std::cout << "IT: "<<(*it)->getID() << std::endl;
			std::cout << "///////////" << std::endl;

			std::cout << "///////////" << std::endl;
			std::cout << "OBJ: " << obj->getID() << std::endl;
			std::cout << "///////////" << std::endl;

			delete(*it);
			it = inventary.erase(it);
			mostrarInventario();
		}
		else {
			it++;
		}


	}

}
