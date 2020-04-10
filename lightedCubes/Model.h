#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\glm\glm.hpp"
#include "Mesh.h"
#include "TextureManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Model
{
public:

	Model() {}; 
	Model(std::string path) { loadModel(path); };
	~Model() {};

	void renderCube(); 

	void loadModel(std::string filePath);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName); 

	void draw(Shader shader); 
	void draw(); 

private:
	GLfloat cube[320] = {

		//Verex Data			//Normals				//Tex Coords
		-1.0f, -1.0f, -1.0f,	0.0f,  0.0f, -1.0f,		0.0f, 0.0f,
		1.0f, -1.0f, -1.0f,		0.0f,  0.0f, -1.0f,		1.0f, 0.0f,
		1.0f,  1.0f, -1.0f,		0.0f,  0.0f, -1.0f,		1.0f, 1.0f,
		1.0f,  1.0f, -1.0f,		0.0f,  0.0f, -1.0f,		1.0f, 1.0f,
		-1.0f,  1.0f, -1.0f,	0.0f,  0.0f, -1.0f,		0.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,	0.0f,  0.0f, -1.0f,		0.0f, 0.0f,

		-1.0f, -1.0f,  1.0f,	0.0f,  0.0f,  1.0f,		0.0f, 0.0f,
		1.0f, -1.0f,  1.0f,		0.0f,  0.0f,  1.0f,		1.0f, 0.0f,
		1.0f,  1.0f,  1.0f,		0.0f,  0.0f,  1.0f,		1.0f, 1.0f,
		1.0f,  1.0f,  1.0f,		0.0f,  0.0f,  1.0f,		1.0f, 1.0f,
		-1.0f,  1.0f,  1.0f,	0.0f,  0.0f,  1.0f,		0.0f, 1.0f,
		-1.0f, -1.0f,  1.0f,	0.0f,  0.0f,  1.0f,		0.0f, 0.0f,

		-1.0f,  1.0f,  1.0f,	-1.0f,  0.0f,  0.0f,	1.0f, 0.0f,
		-1.0f,  1.0f, -1.0f,	-1.0f,  0.0f,  0.0f,	1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,	-1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,	-1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
		-1.0f, -1.0f,  1.0f,	-1.0f,  0.0f,  0.0f,	0.0f, 0.0f,
		-1.0f,  1.0f,  1.0f,	-1.0f,  0.0f,  0.0f,	1.0f, 0.0f,

		1.0f,  1.0f,  1.0f,		1.0f,  0.0f,  0.0f,		1.0f, 0.0f,
		1.0f,  1.0f, -1.0f,		1.0f,  0.0f,  0.0f,		1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,		1.0f,  0.0f,  0.0f,		0.0f, 1.0f,
		1.0f, -1.0f, -1.0f,		1.0f,  0.0f,  0.0f,		0.0f, 1.0f,
		1.0f, -1.0f,  1.0f,		1.0f,  0.0f,  0.0f,		0.0f, 0.0f,
		1.0f,  1.0f,  1.0f,		1.0f,  0.0f,  0.0f,		1.0f, 0.0f,

		-1.0f, -1.0f, -1.0f,	0.0f, -1.0f,  0.0f,		0.0f, 1.0f,
		1.0f, -1.0f, -1.0f,		0.0f, -1.0f,  0.0f,		1.0f, 1.0f,
		1.0f, -1.0f,  1.0f,		0.0f, -1.0f,  0.0f,		1.0f, 0.0f,
		1.0f, -1.0f,  1.0f,		0.0f, -1.0f,  0.0f,		1.0f, 0.0f,
		-1.0f, -1.0f,  1.0f,	0.0f, -1.0f,  0.0f,		0.0f, 0.0f,
		-1.0f, -1.0f, -1.0f,	0.0f, -1.0f,  0.0f,		0.0f, 1.0f,

		-1.0f,  1.0f, -1.0f,	0.0f,  1.0f,  0.0f,		0.0f, 1.0f,
		1.0f,  1.0f, -1.0f,		0.0f,  1.0f,  0.0f,		1.0f, 1.0f,
		1.0f,  1.0f,  1.0f,		0.0f,  1.0f,  0.0f,		1.0f, 0.0f,
		1.0f,  1.0f,  1.0f,		0.0f,  1.0f,  0.0f,		1.0f, 0.0f,
		-1.0f,  1.0f,  1.0f,	0.0f,  1.0f,  0.0f,		0.0f, 0.0f,
		-1.0f,  1.0f, -1.0f,	0.0f,  1.0f,  0.0f,		0.0f, 1.0f
	};

	GLuint cubeVAO;
	GLuint cubeVBO;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	std::vector<Mesh> meshes; 

	GLuint modelVertexBuffer;
	GLuint modelUVBuffer;
	GLuint modelNormalBuffer; 

	GLboolean modelLoaded = false; 

	std::string path;

	//void parseMS3D();
	//void parseOBJ();
	//void parseSTL();
	//void parse3DS(); 
};
