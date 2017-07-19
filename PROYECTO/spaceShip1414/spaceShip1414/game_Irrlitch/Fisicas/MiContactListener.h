#pragma once
/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   MiContactListener.h
* Author: David
*
* Created on 7 de diciembre de 2016, 11:27
*/

#ifndef MICONTACTLISTENER_H
#define MICONTACTLISTENER_H

class Entity2D;
class Bala;

class MiContactListener : public b2ContactListener {
private:
	bool terActivado;
public:
	MiContactListener();
	MiContactListener(const MiContactListener& orig);
	~MiContactListener();
	// Se produce un contacto entre dos cuerpos
	virtual void BeginContact(b2Contact* contact);
	// El contacto entre los cuerpos ha finalizado
	virtual void EndContact(b2Contact* contact);
	// Se ejecuta antes de resolver el contacto.
	// Podemos evitar que se procese
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	// Podemos obtener el impulso aplicado sobre los cuerpos en contacto
	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

	void actualizarPuerta(Entity2D *entity, Entity2D *pers, int modo);

	void aplicarDamage(Entity2D *entity, Entity2D *bala);
	void activarTerminar(Entity2D *pers, Entity2D *terminal, bool actTer);
	void gestionarObjeto(Entity2D *pers, Entity2D *objeto, int tipo);
	void aumentarMunicionPistola(Entity2D *pers, Entity2D *munPistola);
	void aumentarMunicionSubfusil(Entity2D *pers, Entity2D *munSubfisul);
	void aumentarMunicionEscopeta(Entity2D *pers, Entity2D *munEscopeta);
	void addObjetoAlInventario(Entity2D *pers, Entity2D *objeto, int tipo);



};



#endif /* MICONTACTLISTENER_H */

