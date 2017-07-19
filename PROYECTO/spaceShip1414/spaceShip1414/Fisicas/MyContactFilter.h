#pragma once
/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   MyContactFilter.h
* Author: David
*
* Created on 17 de diciembre de 2016, 18:13
*/

#ifndef MYCONTACTFILTER_H
#define MYCONTACTFILTER_H

class MyContactFilter : public b2ContactFilter {
public:
	MyContactFilter();
	MyContactFilter(const MyContactFilter& orig);
	virtual ~MyContactFilter();
	virtual bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB);
private:

};

#endif /* MYCONTACTFILTER_H */
