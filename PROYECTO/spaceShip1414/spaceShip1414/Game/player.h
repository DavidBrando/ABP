#pragma once
#include <glm\vec3.hpp>
#include <list>

class TGraphicEngine;
class TCamara;
class TNodo;
class Entity2D;
class Mundo;
class Bala;
class MaquinaEstados;
class Estados;
class Inventario;
class Pistola;
class Escopeta;

class player
{
public:
	player(TGraphicEngine*, Mundo*);
	~player();
	float getVelocity();
	float getYaw();
	float getPitch();
	void rotation(TGraphicEngine *, float, float, float, float);
	void rotationYPR(TGraphicEngine *, float, float, float);
	void scale(TGraphicEngine *, float, float, float);
	void translation(TGraphicEngine *, float, float, float);
	void setVelocity(float);
	void setYaw(float);
	void setPitch(float);
	glm::vec3 getPos();
	glm::vec3 getRot();
	glm::vec3 getScale();
	int getDireccion();
	void setPos(float x, float y, float z);
	void setRot(float x, float y, float z);
	void setScale(float x, float y, float z);
	void cambiarAnimacion(char c);
	void actualizarFisicas(int n, double delta, float);
	void setCamPos(glm::vec3);
	TNodo * getNodo();

	void asignarVectorDirector(glm::vec3 u, float angle);
	void actualizarPosicion();

	void iniciarTiempoImpulso();

	void disminuirTem();

	void initEstados();
	void deleteEstados();

	float getTemporizador();
	void setImpulso(bool x);
	void destruirAnimacion(TNodo * n);
	bool getImpulso();
	void setAnguloCamara(float angle);
	void setRecalculo(bool x);
	void setVectorDirector(glm::vec3 u);

	void setTeclaE(bool x);
	void setTeclaQ(bool x);
	bool getTeclaE();
	bool getTeclaQ();

	void quitarVida(float damage);
	void curar(float recup);
	void usarBotiquin();
	float getVida();
	float getPorcentajeVida();
	Inventario* getInventario();

	float getTiempoDisparo();
	void setTiempoDisparo(float x);
	void setDisparo(bool x);
	bool getDisparo();
	void actualizarLista(float dt);
	void Disparar(Mundo* w, float dt);
	int getCargador();
	int getMunicionActual();
	float getDamage();
	float getTiempoArma();
	int getArmaActual();
	void recargar();
	void cogerMunicion(int municionCogida, int arma);
	void setArmaActual(int newArma);

	void load_personaje();

	void victory();
	bool getVictory();

private:

	
	float velocity;
	float yaw;
	float pitch;
	float temporizador;
	float anguloCamara;
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 escale;
	glm::vec3 posCam;
	glm::vec3 posAnterior;
	glm::vec3 vecDir, vecA, vecS, vecD, vecAux;
	Entity2D *entity;
	TNodo *nodo, *animation;
	TGraphicEngine * engine;
	int dir;
	bool impulso = false, recalculo = false;
	MaquinaEstados* MaquinaEstadosAnimation;
	bool teclaE = false, teclaQ = false;
	float vida, vidaMax, rotAnt;
	Inventario *inv;

	std::list<Bala*> listaBalas;
	bool disparo;
	float tiempoDisparo;
	Pistola *pistol;
	Escopeta *shotgun;
	int cargador; //cargador actual del arma en uso
	int municionTotal; //balas totales que tiene el jugador del arma actual
	int armaActual;

	Estados* andar, *pistola, *escopeta, *reposoAndar, *reposoPistola, *disparar, *reposoEscopeta;
	TNodo *godfather, *NreposoAndar, *NreposoPistola, *Nandar, *NPistola, *NreposoEscopeta,*NEscopeta;
	std::string movimiento;
	
	bool victoria;
};


