#pragma once

#include "Dependencies\glew\glew.h"
#include "Dependencies\glfw\glfw3.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtx\quaternion.hpp"
#include "Dependencies\soil\SOIL.h"

#include"FreeCamera.h"
#include"Shader.h"
#include"TextureManager.h"
#include"FBO.h"
#include"Model.h"

#include<stdio.h>
#include<iostream>
using namespace std;
using namespace glm;

#pragma region definitions

const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 768;

void key_callback(GLFWwindow*, int, int, int, int);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void framebuffer_size_callback(GLFWwindow* window, int width, int height); 


void renderScene(); 
void loadTextures(); 
void initFBO(); 

void move();

bool keys[1024];
float a = 0.0f;
float b = 10.0f; 
float radius = 1.0f;

GLFWwindow* window;

Shader shader, lightShader, frameBufferShader;
FreeCamera camera(glm::vec3(0.0f, 0.0f, 10.0f));
Model diver, vFAST, cube;
GLuint tex1, tex2, tex3; 

GLuint frameBuffer = 0;
GLuint renderedTexture; 
GLuint depthTexture; 
GLuint depthrenderbuffer;

FBO buffer(SCR_WIDTH, SCR_HEIGHT); 

GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

vec3 lightPos;
vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);

int attenuationType = 1;
bool firstPress = false;

vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(5.0f, 0.0f,  0.0f),
	glm::vec3(-5.0f, 0.0f, 0.0f),
	glm::vec3(0.0f,  0.0f,  0.0f)
};

vec3 cubeColors[] = {
	glm::vec3(1.0f,  0.0f,  0.0f),
	glm::vec3(0.0f, 1.0f,  0.0f),
	glm::vec3(0.0f, 0.0f, 1.0f),
	glm::vec3(0.0f,  0.5f,  0.5f)
};

GLfloat screenQuad[24] = {   // Vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
							 // Positions   // TexCoords
	-1.0f,  1.0f,  0.0f, 1.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,
	1.0f, -1.0f,  1.0f, 0.0f,

	-1.0f,  1.0f,  0.0f, 1.0f,
	1.0f, -1.0f,  1.0f, 0.0f,
	1.0f,  1.0f,  1.0f, 1.0f
};
#pragma endregion

int init()
{
	glfwInit();
	//window = glfwCreateWindow(1920, 1080, "Cubes", glfwGetPrimaryMonitor(), NULL);
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Cubes", NULL, NULL);

	if (!window)
	{
		cout << "Could not open window with GLFW!" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	//glfwSetScrollCallback(window, scroll_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;
	glewInit();

	const GLubyte* render = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);

	printf("Renderer: %s\n", render);
	printf("Version: %s\n", version);
	cout << endl;

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void initShaders()
{
	shader.loadComplieShaders("shaders/vs.glsl", "shaders/fs.glsl", NULL);
	lightShader.loadComplieShaders("shaders/light_vs.glsl", "shaders/light_fs.glsl", NULL);
	frameBufferShader.loadComplieShaders("shaders/frameBuffer_v.glsl", "shaders/frameBuffer_f.glsl", NULL);
	//frameBufferShader.loadComplieShaders("shaders/fb_vertex.glsl", "shaders/fb_vertex.glsl"); 
}

void loadModels()
{
	diver.loadModel("models/diver.ms3d");
	vFAST.loadModel("models/triangulationModel2.obj"); 
	cube.loadModel("models/cube.obj");
}

int main()
{
	init();
	initShaders();
	initFBO(); 
	loadModels(); 
	loadTextures(); 

	while (!glfwWindowShouldClose(window))
	{
		buffer.render();
		renderScene();

		buffer.draw(frameBufferShader);

		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}

void initFBO()
{
	buffer.initFBO(); 
	buffer.attachColorBuffer(SCR_WIDTH, SCR_HEIGHT);
	buffer.attachDepthBuffer(SCR_WIDTH, SCR_HEIGHT); 
}

void renderScene()
{
	double currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	glfwPollEvents();
	move();

	mat4 view = camera.getViewMat();
	mat4 proj = glm::perspective(camera.Zoom, (float)(SCR_WIDTH / SCR_HEIGHT), 0.1f, 1000.0f);

	radius += 0.001f;
	lightPos = vec3(10.0f * cos(a), 5 * sin(radius * 3), 10.0f * sin(a));
	
	shader.useShader(); 

	for (int i = 0; i < 4; i++)
	{
		mat4 model = mat4();
		model = glm::translate(model, cubePositions[i]);

		if (i == 0)
		{
			model = glm::translate(model, vec3(0.0f, 0.0f, sin(a) * 2.0f));

			model = glm::rotate(model, a, vec3(1.0f, 0.0f, 0.0f));
		}

		if (i == 1 || i == 2)
		{
			model = glm::translate(model, vec3(0.0f, 0.0f, cos(a) * 2.0f));

			if (i == 1)
				model = glm::rotate(model, -a, vec3(0.0f, 1.0f, 0.0f));
			else
				model = glm::rotate(model, a, vec3(0.0f, 1.0f, 0.0f));
		}
		if (i == 3)
		{
			model = glm::scale(model, vec3(25.0f));
			shader.setUniformInteger("reverseNormals", 1);
		}
		else
			shader.setUniformInteger("reverseNormals", 0);

		shader.setUniformMatrix4("proj", &proj[0][0]);
		shader.setUniformMatrix4("view", &view[0][0]);
		shader.setUniformMatrix4("model", &model[0][0]);
		shader.setUniformFloat("objectColor", cubeColors[i]);
		shader.setUniformFloat("lightColor", lightColor);
		shader.setUniformFloat("lightPos", lightPos);
		shader.setUniformFloat("viewPos", camera.Position);
		shader.setUniformInteger("attenuationType", attenuationType); 

		shader.setUniformInteger("tex", 0);
		shader.setUniformInteger("tex2", 1);

		TextureManager::bindTexture(tex1, 0);
		TextureManager::bindTexture(tex2, 1);

		diver.renderCube();
		//cube.draw(); 
	}

	shader.disableShader();

	lightShader.useShader();

	mat4 model = mat4();
	model = glm::translate(model, lightPos);
	model = glm::scale(model, vec3(0.2));

	lightShader.setUniformMatrix4("proj", &proj[0][0]);
	lightShader.setUniformMatrix4("view", &view[0][0]);
	lightShader.setUniformMatrix4("model", &model[0][0]);
	lightShader.setUniformFloat("color", lightColor);

	diver.draw(lightShader); 

	//vFAST.draw(lightShader);

	a += 0.01f; 
}

void loadTextures()
{
	tex1 = TextureManager::loadTexture("textures/tex.jpg"); 
	tex2 = TextureManager::loadTexture("textures/skull.jpg"); 
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (action == GLFW_PRESS)
		keys[key] = true;

	else if (action == GLFW_RELEASE)
		keys[key] = false;

	if (key == GLFW_KEY_T && action == GLFW_PRESS)
	{
		if (!firstPress)
		{
			attenuationType = 1;
			firstPress = true;
		}
		else
		{
			attenuationType = 0;
			firstPress = false;
		}
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

//void scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
//{
//	camera.processScroll(yoffset);
//}

void mouse_callback(GLFWwindow * window, double xpos, double ypos)
{

	int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	if (state == GLFW_PRESS)
	{
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		GLfloat xoffset = xpos - lastX;
		GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

		lastX = xpos;
		lastY = ypos;

		camera.processMouse(xoffset, yoffset);
	}
}

void move()
{
	// Camera controls
	if (keys[GLFW_KEY_W])
		camera.processKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.processKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.processKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.processKeyboard(RIGHT, deltaTime);
	if (keys[GLFW_KEY_Q])
		camera.processKeyboard(UP, deltaTime);
	if (keys[GLFW_KEY_E])
		camera.processKeyboard(DOWN, deltaTime);
	if (keys[GLFW_KEY_EQUAL])
		lightColor += 0.1f;
	if (keys[GLFW_KEY_MINUS])
		lightColor -= 0.1f;
}
