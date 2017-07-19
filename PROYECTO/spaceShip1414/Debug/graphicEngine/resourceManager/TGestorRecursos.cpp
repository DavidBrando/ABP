#include "TGestorRecursos.h"
#include "TRecurso.h"
#include "TRecursoMalla.h"
#include "TRecursoTextura.h"


TGestorRecursos::TGestorRecursos() : recursos()
{
}


TGestorRecursos::~TGestorRecursos()
{
	for (std::vector<TRecurso*>::iterator it = recursos.begin(); it != recursos.end(); ++it)
	{
		delete (*it);
	}
	recursos.erase(recursos.begin(), recursos.end());
}

TRecurso * TGestorRecursos::getRecurso(std::string nombre, int tipo)
{
	TRecurso* rec = nullptr;
	if (recursos.size() > 0) {
		size_t index = nombre.find_last_of("\\/");
		std::string comparar = index == std::string::npos ? "" : nombre.substr(index+1);
		for (std::vector<TRecurso*>::iterator it = recursos.begin(); it != recursos.end(); ++it)
		{
			if ((*it)->getNombre().compare(comparar) == 0)
			{
				return *it;
			}
		}
	}
	switch (tipo)
	{
		case 1:
			rec = new TRecursoMalla(nombre);
			recursos.push_back(rec);
			break;
		case 2:
			//rec = new TRecursoTextura();
			//recursos.push_back(rec);
			break;
		default:
			rec = new TRecursoMalla(nombre);
			recursos.push_back(new TRecursoMalla(nombre));
			break;
	}
	return rec;
}

void TGestorRecursos::deleteRecurso(std::string nombre)
{
	if (recursos.size() > 0) {
		size_t index = nombre.find_last_of("\\/");
		std::string comparar = index == std::string::npos ? "" : nombre.substr(index + 1);
		std::vector<TRecurso*>::iterator it;
		for (it = recursos.begin(); it != recursos.end(); ++it)
		{
			if ((*it)->getNombre().compare(comparar) == 0)
			{
				delete (*it);
				break;
			}
		}
		recursos.erase(it);
	}
}
