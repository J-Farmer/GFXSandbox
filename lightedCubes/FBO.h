#pragma once
#include "Dependencies\glew\glew.h"
#include "TextureManager.h"
#include "Shader.h"
#include <iostream>

/*This class is a utility to simplify FBO rendering operations*/
class FBO
{
public:
	FBO() {};
	FBO(int w, int h) { scr_w = w; scr_h = h; }; 
	~FBO() {};

	void initFBO(); //This function initializes the framebuffer. Must make explicit call to init function instead of doing it in constructor.
	void render(); //This will render to the framebuffer. 
	void attachColorBuffer(int, int);
	void attachDepthBuffer(int, int); 
	void draw(Shader shader); 
	void bindDefaultFramebuffer(); 

	GLuint getColorTex() { return colorTexture; };
	GLuint getDepthTex() { return depthTexture; };

private:
	GLuint frameBuffer;
	GLuint depthBuffer; 
	GLuint colorTexture; 
	GLuint depthTexture; 
	GLboolean isComplete; 

	GLboolean isColorTexAttached = false;
	GLboolean isDepthTexAttached = false;

	GLuint scr_w, scr_h; 

	GLfloat screenQuad[24] = {   // Vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
		 //Positions   //TexCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};
};