#include "TRecursoMalla.h"
#include <GL\GL.h>
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>
#include <glm\gtc\type_ptr.hpp>
#include <iostream>
#include "TRecursoTextura.h"
#include "TGestorRecursos.h"
#include <SFML\Graphics\Image.hpp>

TRecursoMalla::Mesh::Mesh(const aiMesh *maya, TRecursoMalla *modelo, TGestorRecursos * gr) : buffer{ 0 }, vao{ 0 }, texture_diffuse{ nullptr }, texture_specular{ nullptr }, texture_ambient{ nullptr }, texture_normal{ nullptr }
{
	this->model = modelo;
	load(maya, gr);
	create();
}

TRecursoMalla::Mesh::~Mesh()
{
	glDeleteBuffers(4, buffer);
	glDeleteVertexArrays(1, &vao);
}

void TRecursoMalla::Mesh::draw()
{
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
}

void TRecursoMalla::Mesh::draw(GLuint program)
{
	if (texture_diffuse != nullptr)
	{
		texture_diffuse->draw(1, program, "material.diffuse");
	}
	/*if (texture_normal != nullptr) {
		activeTextureNum(2, texture_normal->getTexturaID(), program, "material.normal");
		texture_normal->draw(2, program, "material.normal");
	}*/
	if (texture_specular!=nullptr)
	{
		texture_specular->draw(2, program, "material.specular");
	}
	if (texture_ambient != nullptr)
	{
		texture_ambient->draw(3, program, "material.ambient");
	}

	glUniform1f(glGetUniformLocation(program, "material.shininess"), shininess);
	glUniform1f(glGetUniformLocation(program, "material.shininess_strength"), shininess_strength);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);

	disableAllTexture();
}

void TRecursoMalla::Mesh::disableAllTexture()
{
	if (texture_diffuse != nullptr)
	{
		texture_diffuse->desactivar(1);
	}
	/*if (texture_normal != nullptr) {
		texture_normal->desactivar(2);
	}*/
	if (texture_specular != nullptr)
	{
		texture_specular->desactivar(2);
	}
	if (texture_ambient != nullptr)
	{
		texture_ambient->desactivar(3);
	}
}

void TRecursoMalla::Mesh::load(const aiMesh * malla, TGestorRecursos* gr)
{
	vertex.reserve(malla->mNumVertices);
	uv.reserve(malla->mNumVertices);
	normal.reserve(malla->mNumVertices);
	indices.reserve(3 * malla->mNumFaces);

	for (unsigned int i = 0; i < malla->mNumVertices; i++)
	{
		// Obtener la posicion de cada vertice
		const aiVector3D* pos = &(malla->mVertices[i]);
		vertex.push_back(glm::vec3(pos->x, pos->y, pos->z));

		// Obtener las coordenadas de textura
		if (malla->HasTextureCoords(0))
		{
			const aiVector3D* UVW = &(malla->mTextureCoords[0][i]);
			uv.push_back(glm::vec2(UVW->x, UVW->y));
		}
		else
		{
			uv.push_back(glm::vec2(0, 0));
		}

		// Obtener los vectores normales
		if (malla->HasNormals()) 
		{
			const aiVector3D* n = &(malla->mNormals[i]);
			normal.push_back(glm::vec3(n->x, n->y, n->z));
		}
	}

	// Obtener los indices
	for (unsigned int i = 0; i < malla->mNumFaces; i++) 
	{
		indices.push_back(malla->mFaces[i].mIndices[0]);
		indices.push_back(malla->mFaces[i].mIndices[1]);
		indices.push_back(malla->mFaces[i].mIndices[2]);
	}

	texture_ambient=loadMaterial(malla, aiTextureType_AMBIENT, gr);
	texture_diffuse=loadMaterial(malla, aiTextureType_DIFFUSE, gr);
	texture_specular=loadMaterial(malla, aiTextureType_SPECULAR, gr);
	//loadMaterial(malla, aiTextureType_HEIGHT, gr, texture_normal);

	if (malla->mMaterialIndex >= 0) {
		// obtener el material correspondiente a este Mesh
		const aiMaterial* material = model->scene->mMaterials[malla->mMaterialIndex];

		if (material->Get(AI_MATKEY_SHININESS, shininess) != AI_SUCCESS)                     { shininess = 128.0;        }
		if (material->Get(AI_MATKEY_SHININESS_STRENGTH, shininess_strength) != AI_SUCCESS)   { shininess_strength = 1.0; }

		aiColor4D diffuse, ambient, specular, emisive;
	
		if (aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuse) == AI_SUCCESS)   { aiColorToFloat(diffuse, color_diffuse);   }
		if (aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specular) == AI_SUCCESS) { aiColorToFloat(specular, color_specular); }
		if (aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &ambient) == AI_SUCCESS)   { aiColorToFloat(ambient, color_ambient);   }
		if (aiGetMaterialColor(material, AI_MATKEY_COLOR_EMISSIVE, &emisive) == AI_SUCCESS)  { aiColorToFloat(emisive, color_emissive);  }
	}
}

inline void TRecursoMalla::Mesh::aiColorToFloat(aiColor4D & src, float dst[4])
{
	dst[0] = src.r;
	dst[1] = src.g;
	dst[2] = src.b;
	dst[3] = src.a;
}

TRecursoTextura * TRecursoMalla::Mesh::loadMaterial(const aiMesh * mesh, aiTextureType ttype, TGestorRecursos * gr)
{

	if (mesh->mMaterialIndex >= 0) {
		const aiMaterial* material = model->scene->mMaterials[mesh->mMaterialIndex];

		for (unsigned int i = 0; i < material->GetTextureCount(ttype); i++) {
			
			aiString path;
			
			if (AI_SUCCESS == material->GetTexture(ttype, i, &path)) {
				const std::string tex_path = path.C_Str();
				return static_cast<TRecursoTextura*>(gr->getRecurso(texture_path(path.C_Str()), 2));
				//std::cout << "tex-mex: " << textureADSN->getTexturaID()<<" "<<textureADSN->getNombre() << std::endl;
				
			}
		}
	}
}

std::string TRecursoMalla::Mesh::texture_path(const std::string & path)
{
	size_t start = path.find_last_of("\\/");
	std::string tex_path = start == std::string::npos ? path : path.substr(start + 1);
	std::cout << "Ruta textura: " << tex_path << std::endl;
	return model->getRuta().empty() ? tex_path : model->getRuta() + "/" + tex_path;
}

void TRecursoMalla::Mesh::create()
{
	// generar y activar el VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// generar dos ids para los buffer
	glGenBuffers(4, buffer);

	// buffer de vertices
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(glm::vec3), &vertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	// buffer de textura
	if (!uv.empty()) {
		glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
		glBufferData(GL_ARRAY_BUFFER, uv.size() * sizeof(glm::vec2), &uv[0], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(1);
	}

	// buffer de normales
	if (!normal.empty()) {
		glBindBuffer(GL_ARRAY_BUFFER, buffer[2]);
		glBufferData(GL_ARRAY_BUFFER, normal.size() * sizeof(glm::vec3), &normal[0], GL_STATIC_DRAW);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(2);
	}

	// buffer de indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	// desactivar el VAO
	glBindVertexArray(0);
	vertex.clear();
	uv.clear();
	normal.clear();
}

TRecursoMalla::TRecursoMalla()
{
}

TRecursoMalla::TRecursoMalla(std::string n, TGestorRecursos * gr)
{
	this->cargarFichero(n, gr);
}

TRecursoMalla::~TRecursoMalla() 
{
}

bool TRecursoMalla::cargarFichero(std::string n)
{
	return false;
}

bool TRecursoMalla::cargarFichero(std::string n, TGestorRecursos* gr)
{
	size_t index = n.find_last_of("\\/");
	nombre = index == std::string::npos ? "" : n.substr(index+1);
	std::cout <<"Recurso nombre: "<< nombre << std::endl;
	index = n.find_last_of("\\/");
	ruta = index == std::string::npos ? "" : n.substr(0, index);

	Assimp::Importer importer;
	scene = importer.ReadFile(n, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (scene && scene->mRootNode)
	{
		processNode(scene->mRootNode, scene, gr);
		return true;
	}
	else
	{ 
		std::cout << importer.GetErrorString() << std::endl;
		return false;
	}
}

void TRecursoMalla::draw()
{
	for (auto& m : meshes) { m->draw(); }
}

void TRecursoMalla::draw(GLuint program)
{
	for (auto& m : meshes) { m->draw(program); }
}

std::string TRecursoMalla::getRuta()
{
	return ruta;
}

void TRecursoMalla::processNode(const aiNode * nodo, const aiScene * malla, TGestorRecursos* gr)
{
	// obtener los mesh de esta escena
	for (unsigned int i = 0; i < nodo->mNumMeshes; i++) 
	{
		std::shared_ptr<Mesh> malla(new Mesh(scene->mMeshes[nodo->mMeshes[i]], this, gr));
		meshes.push_back(malla);
	}

	// procesar los hijos del nodo
	for (unsigned int i = 0; i < nodo->mNumChildren; i++)
	{
		this->processNode(nodo->mChildren[i], scene, gr);
	}
}
