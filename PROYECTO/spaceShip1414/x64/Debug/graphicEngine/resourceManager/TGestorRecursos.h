#pragma once
#include <vector>
#include <string>

class TRecurso;

class TGestorRecursos
{
public:
	TGestorRecursos();
	~TGestorRecursos();
	TRecurso* getRecurso(std::string, int);
	void deleteRecurso(std::string);
private:
	std::vector<TRecurso*> recursos;
};

