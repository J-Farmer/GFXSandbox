#pragma once
#include "Dependencies\soil\SOIL.h"
#include "Dependencies\glew\glew.h"
#include <string>
class Texture
{
public:

	GLuint getTexHandle() { return texHandle; };
	std::string getTextureName() { return textureName; };

private:

	GLuint texHandle; 
	std::string textureName; 
};
