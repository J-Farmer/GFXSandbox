#pragma once
#include"Dependencies\glew\glew.h"
#include"Dependencies\glfw\glfw3.h"
#include<stdio.h>
#include<math.h>
#include"Dependencies\glm\glm.hpp"
#include"Dependencies\glm\gtc\matrix_transform.hpp"
#include"Dependencies\glm\gtc\type_ptr.hpp"
#include<vector>

using namespace glm;

typedef enum { ORTHOGRAPHIC = 1, PERSEPCTIVE = 2 } CameraType;

class Camera
{
public:
	Camera();
	Camera(CameraType type, glm::mat4 projectionMatrix);

	void lookAt(vec3& point);
	void translate(vec3& offset);
	void moveTo(vec3& point);
	void scale(float zoomFactor);
	void rotate(vec3& rotation);
	void rotateAbout(vec3 rotation, vec3 point);
	mat4 getInverse() { return glm::inverse(viewMat); };
	vec3 windowToWorld(vec3 winCoord, vec4 viewPort);

	vec3 getPos() { return camPos; };
	mat4 getViewMat() { return viewMat; };
	mat4 getProjMat() { return projMat; };
	vec3 getFront() { return camFront; };
	void setViewMat(mat4 view) { viewMat = view; };
	void setProjMat(mat4 proj) { projMat = proj; };

private:
	mat4 viewMat;
	mat4 projMat;
	mat4 mScaleProj;
	vec3 camPos;
	vec3 camUp;
	vec3 camAt;
	vec3 camFront; 
	CameraType cameraType;
};
