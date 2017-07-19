/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Entity2D.cpp
 * Author: User
 *
 * Created on 9 de diciembre de 2016, 15:52
 */
#include <iostream>
#include "Entity2D.h"
#include "../Enemigos/Enemigo.h"
#include "RayCastCallback.h"

#define FILTRO_PERSONAJE 1
#define FILTRO_PARED 2
#define FILTRO_PUERTA 3
#define FILTRO_DISPAROPERS 4
#define FILTRO_DISPAROENE 5
#define FILTRO_ENEMIGO 6
#define FILTRO_SOMB_ENEMIGO 14


#define FILTRO_PUERTAABIERTA 15



//hacer diferentes constructores para los distintos objetos

Entity2D::Entity2D(b2World * world)
{

	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(-99999999, -99999999);
	bodyShape.SetAsBox(5.0f, 5.0f);
	md.mass = 50.0f;
	md.center = b2Vec2(3, 3);
	md.I = 0.0f;
	body = world->CreateBody(&bodyDef);
	body->CreateFixture(&bodyShape, 1.0f);
	body->GetFixtureList()->SetFriction(10.0f);
	body->SetUserData(this);
	body->SetMassData(&md);
	body->GetFixtureList()->SetSensor(true);
	filtro.groupIndex = FILTRO_PUERTAABIERTA;
	body->GetFixtureList()->SetFilterData(filtro);


	iden = -1;
	objeto3D = 0;

}
//constructor personaje

Entity2D::Entity2D(b2World *world, vector3df pos, void* dirPers, ISceneManager* smgr) {


    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.X, pos.Z);
    bodyShape.SetAsBox(5.0f, 5.0f);
    md.mass = 1.0f;
    md.center = b2Vec2(3, 3);
    md.I = 0.0f;
    body = world->CreateBody(&bodyDef);
    body -> CreateFixture(&bodyShape, 1.0f);
    body->GetFixtureList()->SetFriction(0.0f);
    body->SetUserData(this);
    body->SetMassData(&md);
	live = true;
    /*
   sombraDef.type = b2_dynamicBody;
   sombraDef.position.Set(pos.X, pos.Z);
   sombraShape.SetAsBox(5.0f, 5.0f);
   sombraP= world->CreateBody(&sombraDef);
   sombraP -> CreateFixture(&sombraShape, 1.0f);
   sombraP->GetFixtureList()->SetFriction(10.0f);
   sombraP->SetUserData(this);
   sombraP->SetMassData(&md);*/
    filtro.groupIndex = FILTRO_PERSONAJE;
    body->GetFixtureList()->SetFilterData(filtro);
    //   sombraP->GetFixtureList()->SetFilterData(filtro);
    idenSh = 0;


    /* fisica=smgr->addCubeSceneNode(10);
     fisica->setMaterialFlag(irr::video::EMF_WIREFRAME, true);
     fisica->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING,false);
     fisica->getMaterial(0).EmissiveColor.set(0,255,10,20);
     fisica->setPosition(vector3df(sombraP->GetPosition().x,10,sombraP->GetPosition().y));
     */
    iden = 0;
    objeto3D = dirPers;

}
//constructir pared

Entity2D::Entity2D(b2World* world, vector3df pos, vector3df rot, vector3df escala, void* dirPared) {
    //  std::cout<<"CREO PARED CON ENTITY! "<<std::endl;

    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(pos.X, pos.Z);

    //si tiene rotacion en Y van | sino van -
    // con la Y rotada y como esta escalado en X en unity hay que poner el escalado de X en la Y del body
    // std::cout<<"PARED: "<<this<<" ESCALA X: "<<escala.X<<" ESCALA Z: "<<escala.Z<<std::endl;
    if (rot.Y == 90) {

        bodyShape.SetAsBox(5 * escala.Z, 5 * escala.X);

    } else {
        bodyShape.SetAsBox(5 * escala.X, 5 * escala.Z);

    }


    body = world->CreateBody(&bodyDef);
    body -> CreateFixture(&bodyShape, 1.0f);
    body->SetUserData(this);

    filtro.groupIndex = FILTRO_PARED;
    body->GetFixtureList()->SetFilterData(filtro);

    objeto3D = dirPared;
    iden = 1;
}

//constructir puerta

Entity2D::Entity2D(b2World* world, vector3df pos, vector3df rot, vector3df escala, bool sensor, void* dirPuerta, ISceneManager* smgr, int ident) {
	
	id = ident;
    bodyDef.type = b2_kinematicBody;
    bodyDef.position.Set(pos.X, pos.Z);
    b2PolygonShape bodyShape2;
    //si tiene rotacion en Y van | sino van -
    // con la Y rotada y como esta escalado en X en unity hay que poner el escalado de X en la Y del body
    //std::cout<<"PUERTA: "<<this<<" ESCALA X: "<<escala.X<<" ESCALA Z: "<<escala.Z<<std::endl;
    if (escala.Z != 1) {

        bodyShape.SetAsBox(15 * escala.X, 5 * escala.Z);
        bodyShape2.SetAsBox(5 * escala.X, 5 * escala.Z);	
    } else {
        bodyShape.SetAsBox(5 * escala.X, 15 * escala.Z);
        bodyShape2.SetAsBox(5 * escala.X, 5 * escala.Z);	
    }

    objeto3D = dirPuerta;
    puertaBody = world->CreateBody(&bodyDef);
	puertaBody-> CreateFixture(&bodyShape, 1.0f);
	puertaBody->GetFixtureList()->SetSensor(sensor);
	
    //std::cout<<"SENSOR: "<<body->GetFixtureList()->IsSensor()<<std::endl;
	puertaBody->SetUserData(this);

	body = world->CreateBody(&bodyDef);
    body->CreateFixture(&bodyShape2, 1.0f);
	body->SetUserData(this);
    filtro.groupIndex = FILTRO_PUERTA;
    //    body->GetFixtureList()->SetFilterData(filtro);
    iden = 2;
 /*   for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext()) {
        f->SetFilterData(filtro);

    }*/
	body->GetFixtureList()->SetFilterData(filtro);
	puertaBody->GetFixtureList()->SetFilterData(filtro);


}
//constructor bala

Entity2D::Entity2D(b2World* world, vector3df pos, vector3df rot, bool vivo, void* dirBala, int tipo) {


    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.X, pos.Z);
    // bodyShape.SetAsBox(2, 2);
    bodyCircle.m_p.Set(0, 0);
    bodyCircle.m_radius = 1;
    body = world->CreateBody(&bodyDef);
    body -> CreateFixture(&bodyCircle, 1.0f);
    body ->SetBullet(true);
    body->SetUserData(this);
    live = vivo;
	if (tipo == 1) {
		filtro.groupIndex = FILTRO_DISPAROPERS;
		body->GetFixtureList()->SetFilterData(filtro);
		iden = 3;
	}
	else {

		filtro.groupIndex = FILTRO_DISPAROENE;
		body->GetFixtureList()->SetFilterData(filtro);
		iden = 6;

	}

    objeto3D = dirBala;

}

//constructor enemigo

Entity2D::Entity2D(b2World *world, vector3df pos, bool vivo, void* dirEnemigo, ISceneManager* smgr, unsigned int raza) {


    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set((pos.X), (pos.Z));

	if (raza == 10) {
		bodyShape.SetAsBox(5.0f, 5.0f);
	}

	else if (raza == 11) {
		bodyShape.SetAsBox(10.0f, 10.0f);
	}

	bodyCircle.m_p.Set(0, 0);
	bodyCircle.m_radius = 45; 

    body = world->CreateBody(&bodyDef);
	body->CreateFixture(&bodyCircle, 1.0f);
	body->GetFixtureList()->SetSensor(true);
    body -> CreateFixture(&bodyShape, 1.0f);
    live = vivo;
   
    body->SetUserData(this);
    

    sombraDef.type = b2_kinematicBody;
    sombraDef.position.Set(pos.X, pos.Z);
    sombraShape.SetAsBox(6.0f, 6.0f);
    sombraE = world->CreateBody(&sombraDef);
    sombraE -> CreateFixture(&sombraShape, 1.0f);
	
    //sombraE->GetFixtureList()->SetFriction(10.0f);
    sombraE->SetUserData(this);
    sombraE->SetMassData(&md);
    idenSh = 1;
    filtro.groupIndex = FILTRO_ENEMIGO;

	for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext()) {
		f->SetFilterData(filtro);

	}
	
	filtro.groupIndex = FILTRO_PUERTAABIERTA;
	sombraE->GetFixtureList()->SetFilterData(filtro);

    fisica2 = smgr->addSphereSceneNode(45);
	//smgr->addSphereSceneNode(25)->setPosition(vector3df(sombraE->GetPosition().x, 10, sombraE->GetPosition().y));
    fisica2->setMaterialFlag(irr::video::EMF_WIREFRAME, true);
    fisica2->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);
    fisica2->getMaterial(0).EmissiveColor.set(0, 100, 10, 100);
    fisica2->setPosition(vector3df(sombraE->GetPosition().x, 10, sombraE->GetPosition().y));

	//direccion = smgr->addCubeSceneNode(5);
	////smgr->addSphereSceneNode(25)->setPosition(vector3df(sombraE->GetPosition().x, 10, sombraE->GetPosition().y));
	//direccion->setMaterialFlag(irr::video::EMF_WIREFRAME, true);
	//direccion->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);
	//direccion->getMaterial(0).EmissiveColor.set(0, 140, 50, 100);
	//direccion->setPosition(vector3df(sombraE->GetPosition().x, 10, sombraE->GetPosition().y+5));

    iden = 4;
    objeto3D = dirEnemigo;
}


//constructor de objeto
Entity2D::Entity2D(b2World * world, vector3df pos, vector3df rot, vector3df escala, void * dirObjeto, int tipo)
{
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(pos.X, pos.Z);
	

	body = world->CreateBody(&bodyDef);
	

	if(tipo == 5) {

		b2PolygonShape bodyShape2;

		bodyShape.SetAsBox(30 * escala.X, 5 * escala.Z);
		bodyShape2.SetAsBox(7 * escala.X, 7 * escala.Z);
		
	
		body->CreateFixture(&bodyShape2, 1.0f);
	}

	else {

		bodyShape.SetAsBox(5 * escala.X, 5 * escala.Z);

	}

	body->SetUserData(this);
	body->CreateFixture(&bodyShape, 1.0f);	
	body->GetFixtureList()->SetSensor(true);

	
	//filtro.groupIndex = FILTRO_PARED;
	//body->GetFixtureList()->SetFilterData(filtro);

	objeto3D = dirObjeto;
	iden = 5;
	id = tipo;
	live = true;

	/*
	0: botiquin
	1: llave
	2: municion de pistola
	3:   " " de subfusil
	4:   " " de escopeta	
	*/
}

Entity2D::Entity2D(const Entity2D& orig) {
}

Entity2D::~Entity2D() {
    std::cout << "ID DE LA ENTITY " << iden << std::endl;
    std::cout << "MUERO ENTITY2D" << std::endl;
    body->GetWorld()->DestroyBody(body); //así se tienen que borrar los objetos, no vale con la copia del puntero
    if (sombraE != NULL && fisica2 != NULL) {
        sombraE->GetWorld()->DestroyBody(sombraE);
        fisica2->getParent()->removeChild(fisica2);
    }

	if(puertaBody != NULL) {
		puertaBody->GetWorld()->DestroyBody(puertaBody);
	}
    //mundo->DestroyBody(body);
    //    body->SetUserData(NULL);
    //    body = NULL;

}

float Entity2D::rayCast(b2Vec2 inicio, b2Vec2 fin) {


    float resultado = 0;
    float rayo1, rayo2 = 0;

	
    rayo1 = rayCasting(inicio, fin);


	  std::cout << "Soy rayo1: " << rayo1 << std::endl;
//    std::cout << "Soy rayo2: " << rayo2 << std::endl;
//    //////////////////////////////////////////
	  std::cout << resultado << std::endl;
//    //////////////////////////////////////////

    return resultado;
}

float Entity2D::rayCasting(b2Vec2 inicio, b2Vec2 fin) {

    RayCastCallback *callback = new RayCastCallback();
    llamarCallBack(callback, inicio, fin);
	float dis;
	normal = callback->getNormal();
	puntoDeChoque = callback->getPuntoDeChoque();

	if(callback->getEntidadChocada() == 2 && callback->getEsPuertaCerrada() == true) {
		std::cout << "----- RESULT: " << callback->getDistancia() + 1.0f << std::endl;
		return callback->getDistancia();
	}

		


	else if(callback->getEntidadChocada() != 1) {

		return 0.0f;
	}



	

	else {
		return callback->getDistancia();
	}

}

void Entity2D::llamarCallBack(RayCastCallback* callback, b2Vec2 inicio, b2Vec2 fin) {
    body->GetWorld()->RayCast(callback, inicio, fin);

}

void Entity2D::destruirFixture() {

    for (b2Fixture* f = body->GetFixtureList(); f; f) {

        if (f->IsSensor() == false) {

            b2Filter newFilter;
            newFilter.groupIndex = FILTRO_PUERTAABIERTA;
            f->SetFilterData(newFilter);
            // b2Fixture* destroyMe = f;

            // body->DestroyFixture(destroyMe);
        }
        f = f->GetNext();
    }
}

void Entity2D::crearFixture() {

    for (b2Fixture* f = body->GetFixtureList(); f; f) {

        if (f->IsSensor() == false) {

            b2Filter newFilter;
            newFilter.groupIndex = FILTRO_PUERTA;
            f->SetFilterData(newFilter);
            // b2Fixture* destroyMe = f;

            // body->DestroyFixture(destroyMe);
        }
        f = f->GetNext();
    }
}

b2Body* Entity2D::getCuerpo2D() {

    return body;
}

void Entity2D::getRotarDireccion() {
	float ang = -atan2f(body->GetPosition().x, body->GetPosition().y) * 180 / 3.14;
	//direccion->setRotation(vector3df(0,ang,0));
	
}

b2Body* Entity2D::getSombraE2D() {
    //  std::cout<<"Sombra x: "<<sombra->GetPosition().x<<" Sombra z: "<<sombra->GetPosition().y<<std::endl;
    //  std::cout<<"Body x: "<<body->GetPosition().x<<" Body z: "<<body->GetPosition().y<<std::endl;
    if (fisica2 != NULL && sombraE != NULL) {
        fisica2->setPosition(vector3df(sombraE->GetPosition().x, 10, sombraE->GetPosition().y));
	//	direccion->setPosition(vector3df(sombraE->GetPosition().x, 10, sombraE->GetPosition().y+5));
		
    }
    return sombraE;
}

b2Body * Entity2D::getPuertaBody()
{
	return puertaBody;
}

int Entity2D::getId()
{
	return id;
}

vector3df Entity2D::getNormal()
{
	return vector3df(normal.x, 0, normal.y);
}

vector3df Entity2D::getPuntoDeChoque()
{
	return vector3df(puntoDeChoque.x, 0, puntoDeChoque.y);
}

int Entity2D::getIDEN() {
    return iden;
}

int Entity2D::getIDENSH() {
    return idenSh;
}

b2Body* Entity2D::getSombraP2D() {
    //  std::cout<<"Sombra x: "<<sombra->GetPosition().x<<" Sombra z: "<<sombra->GetPosition().y<<std::endl;
    //  std::cout<<"Body x: "<<body->GetPosition().x<<" Body z: "<<body->GetPosition().y<<std::endl;

    if (fisica != NULL) {
        fisica->setPosition(vector3df(sombraP->GetPosition().x, 10, sombraP->GetPosition().y));
    }
    return sombraP;
}

bool Entity2D::getLive() {
    return live;
}

void Entity2D::setLive(bool x) {
    live = x;
}

void* Entity2D::getObjeto3D() {
    return objeto3D;
}
