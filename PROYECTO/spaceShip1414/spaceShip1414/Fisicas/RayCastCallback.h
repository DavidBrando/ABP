#pragma once
/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   RayCastCallback.h
* Author: User
*
* Created on 9 de diciembre de 2016, 15:27
*/

#ifndef RAYCASTCALLBACK_H
#define RAYCASTCALLBACK_H

#include <Box2D\Box2D.h>


class RayCastCallback : public b2RayCastCallback {
public:
	RayCastCallback();
	RayCastCallback(const RayCastCallback& orig);
	virtual ~RayCastCallback();
	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);
	float32 getDistancia();
	int getEntidadChocada();
	bool getEsPuertaCerrada();
	b2Vec2 getNormal();
	b2Vec2 getPuntoDeChoque();

private:

	float32 distancia;
	int entidadChocada;
	bool x;
	b2Vec2 punto;
	b2Vec2 nor;
};

#endif /* RAYCASTCALLBACK_H */

