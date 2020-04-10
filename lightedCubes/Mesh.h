#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\assimp\Importer.hpp"
#include "Dependencies\assimp\scene.h"
#include "Dependencies\assimp\postprocess.h"
#include "Shader.h"
#include <vector>
#include <string>

struct vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoordinates;
	glm::vec3 tangent;
	glm::vec3 bitangent;
};

struct texture
{
	unsigned int id;
	std::string type; 
	aiString path; 
};

class Mesh
{
public:
	
	std::vector<vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<texture> textures;

	Mesh(std::vector<vertex> vertices, std::vector<unsigned int> indices, std::vector<texture> textures);
	void draw(Shader shader); 
	void draw(); 

private:
	unsigned int VAO, VBO, EBO;

	void setupMesh(); 
};