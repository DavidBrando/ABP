#pragma once
#ifndef GLEW_STATIC
#define GLEW_STATIC
#include <GL/glew.h>
#endif
#include <string>


class openGLShader
{
public:
	openGLShader();
	~openGLShader();
	GLuint getUniformLocation(std::string);
	bool loadFile(std::string, std::string&);
	GLuint compile();
	GLuint compile(std::string, std::string);
	void logShader(GLuint, const GLchar*);
	void logLink();
	GLuint compileShader(std::string&, GLenum);
	GLuint createProgram(GLuint, GLuint);
	void use();
	void unUse();
	GLuint getProgram();
private:
	GLuint program;
};

