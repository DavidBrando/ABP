#pragma once
#include <vector>
#include <glm\mat4x4.hpp>
class TEntidad;
class openGLShader;
class Mundo;

class TNodo
{
public:
	TNodo();
	TNodo(TEntidad*);
	TNodo(TNodo*, TEntidad*);
	~TNodo();
	bool addHijo(TNodo*);
	void setPadre(TNodo*);
	int removeHijo(TNodo*);
	bool setEntidad(TEntidad*);
	TEntidad* getEntidad();
	TNodo* getPadre();
	int getID();
	void draw();
	void draw(openGLShader & s, const glm::mat4 & w, const glm::mat4 & pro, Mundo * world);
private:
	static int id;
	TEntidad* entidad;
	std::vector<TNodo*> hijos;
	TNodo* padre;
	int idN;
};

