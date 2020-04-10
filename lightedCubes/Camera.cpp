#include "Camera.h"


Camera::Camera()
{
	camPos = glm::vec3(4.0, 3.0f, 10.0f);
	camAt = glm::vec3(0.0f, 0.0f, 0.0f);
	camUp = glm::vec3(0.0f, 1.0f, 0.0f);
	camFront = vec3(0.0f, 0.0f, -1.0f);

	viewMat = glm::lookAt(camPos, camAt, camUp);

	projMat = perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
}

Camera::Camera(CameraType type, glm::mat4 projectionMatrix) : cameraType(cameraType), projMat(projectionMatrix)
{
	camPos = vec3(0.0, 0.0, 10.0);
	camAt = vec3(0.0f);
	camUp = vec3(0.0, 0.0, 1.0);
	camFront = vec3(0.0f, 0.0f, -1.0f); 

	viewMat = glm::lookAt(camPos, camPos + camFront, camUp);
}

void Camera::lookAt(vec3 & point)
{
	camAt = point;
	viewMat = glm::lookAt(camPos, camAt, camUp);
}

void Camera::translate(vec3 & offset)
{
	mat4 translation(1.0f);

	translation = glm::translate(translation, offset);
	viewMat = translation * viewMat;

	camPos = vec3(glm::inverse(viewMat) * vec4(0.0, 0.0, 0.0, 1.0));
}

void Camera::moveTo(vec3 & point)
{
	camPos = point;

	viewMat = glm::lookAt(camPos, camAt, camUp);
}

void Camera::scale(float zoomFactor)
{
	mat4 scale(1.0f);

	scale = glm::scale(scale, vec3(zoomFactor));

	projMat = scale * projMat;
	mScaleProj = scale * mScaleProj; 
}

void Camera::rotate(vec3 & rotation)
{
	mat4 allAxes = mat4(1.0f);

	if (rotation.x != 0.0f)
		allAxes = glm::rotate(allAxes, rotation.x, vec3(1.0f, 0.0f, 0.0f));
	if (rotation.y != 0.0f)
		allAxes = glm::rotate(allAxes, rotation.y, vec3(0.0f, 1.0f, 0.0f));
	if (rotation.z != 0.0f)
		allAxes = glm::rotate(allAxes, rotation.z, vec3(0.0f, 0.0f, 1.0f));

	camPos = vec3(allAxes * vec4(camPos, 1.0f));
}

void Camera::rotateAbout(vec3 rotation, vec3 point)
{
	mat4 mRot(1.0f);

	if (rotation.x != 0.0f)
		mRot = glm::rotate(mRot, rotation.x, vec3(1.0f, 0.0f, 0.0f));
	if (rotation.y != 0.0f)
		mRot = glm::rotate(mRot, rotation.y, vec3(0.0f, 1.0f, 0.0f));
	if (rotation.z != 0.0f)
		mRot = glm::rotate(mRot, rotation.z, vec3(0.0f, 0.0f, 1.0f));

	vec3 originalPos = camPos;

	point.y = 0.0f;

	camPos = vec3(glm::translate(mat4(1.0f), point) * mRot * glm::translate(mat4(1.0f), -point) * vec4(camPos, 1.0f));
}

vec3 Camera::windowToWorld(vec3 winCoord, vec4 viewPort)
{
	return glm::unProject(winCoord, viewMat, projMat, viewPort); 
}


