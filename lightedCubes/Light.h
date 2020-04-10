#pragma once
#include "Dependencies/glew/glew.h"
#include "Dependencies\glm\glm.hpp"

class Light
{
	enum lightType
	{
		spot,
		directional,
		point
	};

	struct lightProperties
	{
		glm::vec3 direction;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};

	Light() {};
	~Light() {}; 
	bool setPostiion(GLfloat x, GLfloat y, GLfloat z);
	glm::vec3 getPosition() { return position; };
	glm::vec3 getColor() { return color; };
	glm::vec3 setPosition(glm::vec3 pos) { position = pos; };
	glm::vec3 setColor(glm::vec3 col) { color = col; };

private:
	glm::vec3 position; 
	glm::vec3 color; 
};