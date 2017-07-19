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

class TRecursoTextura;
class TGestorRecursos;
class TRecursoMalla :
	public TRecurso
{
	class Mesh
	{
	public:
		Mesh(const aiMesh*, TRecursoMalla*, TGestorRecursos*);
		~Mesh();
		void draw() ; 
		void draw(GLuint);
		void disableAllTexture();
	private:
		TRecursoMalla* model;

		std::vector<glm::vec3> vertex;
		std::vector<glm::vec3> normal;
		std::vector<glm::vec2> uv;
		std::vector<GLuint> indices;
		GLuint buffer[4];
		GLuint vao;
		TRecursoTextura * texture_ambient;
		TRecursoTextura * texture_diffuse;
		TRecursoTextura * texture_specular;
		TRecursoTextura * texture_normal;

		float shininess, shininess_strength;
		float color_ambient[4] = { 1, 1, 1, 1 };
		float color_diffuse[4] = { 1, 1, 1, 1 };
		float color_specular[4] = { 0.0 };
		float color_emissive[4] = { 0.0 };
		
		void load(const aiMesh*, TGestorRecursos*);
		inline void aiColorToFloat(aiColor4D&, float[4]);
		TRecursoTextura * loadMaterial(const aiMesh*, aiTextureType, TGestorRecursos*);
		GLuint TextureFromFile(const std::string&);
		std::string texture_path(const std::string& path);
		void create();
	};

public:
	TRecursoMalla();
	TRecursoMalla(std::string, TGestorRecursos*);
	~TRecursoMalla();
	bool cargarFichero(std::string) override;
	bool cargarFichero(std::string, TGestorRecursos*);
	void draw() override;
	void draw(GLuint);
	std::string getRuta();
private:
	std::string ruta;
	const aiScene* scene;
	std::vector<std::shared_ptr<Mesh>> meshes;
	void processNode(const aiNode*, const aiScene*, TGestorRecursos*);
};

