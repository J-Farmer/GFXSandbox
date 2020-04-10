#pragma once
#include "Dependencies\soil\SOIL.h"
#include "Dependencies\glew\glew.h"
#include "Texture.h"

class TextureManager
{
public:
	
	static GLuint loadTexture(const char *path) { return SOIL_load_OGL_texture(path, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS); }; //Loads a texture into openGL texture, using SOIL as a backend.
	static GLuint loadTexture(const char *path, GLuint texHandle) { return SOIL_load_OGL_texture(path, SOIL_LOAD_AUTO, texHandle, SOIL_FLAG_MIPMAPS); } //Loads a new texture into an existing openGL texture, using SOIL as a backend. 
	static void bindTexture(GLint texHandle, GLint OGLTexPos) { glActiveTexture(GL_TEXTURE0 + OGLTexPos); glBindTexture(GL_TEXTURE_2D, texHandle); }; //This will bind the texHandle to the correct openGL defined texture position.

	//static void bindTexture(string name, GLint OGLTexPos) { glActiveTexture(GL_TEXTURE0 + OGLTexPos); glBindTexture(GL_TEXTURE_2D, texHandle); }; //This will bind the texHandle to the correct openGL defined texture position. First it must search for the texture with the correct name. 
	//static void bindTexture(Texture name, GLint OGLTexPos) { glActiveTexture(GL_TEXTURE0 + OGLTexPos); glBindTexture(GL_TEXTURE_2D, texHandle); }; //This will bind the texHandle to the correct openGL defined texture position using a texture object. 

private:

};
