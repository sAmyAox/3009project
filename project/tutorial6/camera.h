#pragma once
#include "includPath.h"

class Camera
{
public:
	Camera();
	~Camera();

	void setCamera(glm::vec3 position);
	void rotatePitch(float angle);
	void rotateYaw(float angle);
	void move(int x, int y);

	void zoomIn();
	void zoomOut();

	glm::mat4 getViewMatrix();
	glm::mat4 getProjMatrix();
	glm::vec3 getViewPos();
	void setCamera(glm::vec3 position, glm::vec3 lookAt, glm::vec3 up);

public:
	//projMat
	float zoom;// ”≥°Ω«FOV
	float aspect;


	//viewMat
	glm::vec3 position;
	glm::vec3 upVector;
	glm::vec3 lookAtVector;


	glm::mat4 viewMat;
	glm::mat4 projMat;
	glm::mat4 rotMat;


};

