#pragma once

#include<iostream>
#include <vector>
#include <glm\vec3.hpp>




class GlDebugDraw 
{

public:

	/*struct LINE {
		LINE(glm::vec3 a, glm::vec3 b, glm::vec3 color) : a(a), b(b), color(color) {};

		glm::vec3 a;
		glm::vec3 b;
		glm::vec3 color;
	};

	GlDebugDraw() : m_debugMode(1) {};
	~GlDebugDraw();

	virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);

	virtual void drawSphere(const btVector3& p, btScalar radius, const btVector3& color) {};

	virtual void drawTriangle(const btVector3& a, const btVector3& b, const btVector3& c, const btVector3& color, btScalar alpha) {};

	virtual void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) {};

	void reportErrorWarning(const char * warningString) { std::cout << "Physics debugger warning: " << warningString << std::endl; }

	virtual void draw3dText(const btVector3& location, const char* textString) {};

	void setDebugMode(int debugMode) { m_debugMode = debugMode; };

	int getDebugMode() const { return m_debugMode; }

	std::vector<LINE> & GetLines() { return lines; }*/

private:

	//int m_debugMode;
	//std::vector<LINE> lines;

};

