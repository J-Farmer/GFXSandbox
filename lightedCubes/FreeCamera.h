#pragma once
#include<vector>

#include"Dependencies\glew\glew.h"
#include"Dependencies\glm\glm.hpp"
#include"Dependencies\glm\gtc\matrix_transform.hpp"

using namespace glm; 

enum cameraMovement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

const GLfloat YAW			= -90.0f; 
const GLfloat PITCH			=  0.0f;
const GLfloat SPEED			=  3.0f;
const GLfloat SENSITIVTY	=  0.25f;
const GLfloat ZOOM			=  45.0f;

class FreeCamera
{
public:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	// Eular Angles
	GLfloat Yaw;
	GLfloat Pitch;

	// Camera options
	GLfloat MovementSpeed;
	GLfloat MouseSensitivity;
	GLfloat Zoom;

	FreeCamera();
	FreeCamera(vec3 postition = vec3(0.0f), vec3 up = vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH);
	FreeCamera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw = YAW, GLfloat pitch = PITCH);
	mat4 getViewMat() { return lookAt(Position, Position + Front, Up); };
	void processKeyboard(cameraMovement direction, GLfloat dTime); 
	void processMouse(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = true);
	void processScroll(GLfloat yoffset);

private:
	void updateCameraVectors();

};
