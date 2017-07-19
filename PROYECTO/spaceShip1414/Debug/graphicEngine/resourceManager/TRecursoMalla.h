#pragma once
#include "TRecurso.h"
#include <vector>
#ifndef GLEW_STATIC
#define GLEW_STATIC
#include <GL/glew.h>
#endif
#include <assimp\scene.h>
#include <glm\vec3.hpp>
#include <glm\vec2.hpp>
#include <vector>
#include <map>
#include <memory>

class TRecursoMalla :
	public TRecurso
{
	class Mesh
	{
	public:
		Mesh(const aiMesh*, TRecursoMalla*);
		~Mesh();
		void draw();
		void draw(GLuint);
		void init(const aiMesh*);
	private:
		TRecursoMalla* model;
		std::vector<glm::vec3> vertex;
		std::vector<glm::vec3> normal;
		std::vector<glm::vec2> uv;
		std::vector<GLuint> indices;
		GLuint buffer[4];
		GLuint vao;
		float shininess, shininess_strength;
		float color_ambient[4] = { 1, 1, 1, 1 };
		float color_diffuse[4] = { 1, 1, 1, 1 };
		float color_specular[4] = { 0.0 };
		float color_emissive[4] = { 0.0 };
		
		void load(const aiMesh*);
		inline void aiColorToFloat(aiColor4D&, float[4]);
		void create();
	};

public:
	TRecursoMalla();
	TRecursoMalla(std::string);
	~TRecursoMalla();
	bool cargarFichero(std::string) override;
	void draw() override;
	void draw(GLuint);
private:
	const aiScene* scene;
	std::map<std::string, GLuint> textures;
	std::vector<std::shared_ptr<Mesh>> meshes;
	
	void processNode(const aiNode*, const aiScene*);
};

