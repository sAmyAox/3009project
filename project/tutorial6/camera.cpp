#include "camera.h"


Camera::Camera() {
	viewMat = glm::mat4(1.0f);
	projMat = glm::mat4(1.0f);
	zoom = 20.0f;
	aspect = 0.75f;

};
Camera::~Camera() {};

void Camera::setCamera(glm::vec3 position) {}




void Camera::zoomIn() {

	zoom -= 0.10f;

	if (zoom < 1.0f) {
		zoom = 1.0f;
	}
	else if (zoom > 89.0f) {
		zoom = 89.0f;
	}
	projMat = glm::perspective(zoom, aspect, 0.1f, 1000.0f);
	printf("zoom = %f", zoom);
}
void Camera::zoomOut() {
	zoom += 0.10f;

	if (zoom < 1.0f) {
		zoom = 1.0f;
	}
	else if (zoom > 45.0f) {
		zoom = 45.0f;
	}
	projMat = glm::perspective(zoom, aspect, 0.1f, 1000.0f);
	printf("zoom = %f",zoom);
		//	projMat = glm::perspective(70.0f,0.75f,0.1f,1000.0f);

}

glm::mat4 Camera::getViewMatrix() {	
	return viewMat;
}
glm::mat4 Camera::getProjMatrix() {
	return projMat;
}


void Camera::setCamera(glm::vec3 position, glm::vec3 lookAt, glm::vec3 up) {

	this->position = position;
	this->lookAtVector = glm::normalize(lookAt-position);
	this->upVector = glm::normalize(up);

	viewMat = glm::lookAt(position, position+lookAtVector, upVector);
	projMat = glm::perspective(zoom, aspect, 0.1f, 1000.0f);


	//备注：lookat 恒等于 （0，0，0）；
	//备注2： up 不等于（0，1，0）
}

void Camera::rotatePitch(float angle) {
	float angleRadians = glm::radians(angle);
	glm::vec3 rotVector = glm::vec3(1.0f, 0.0f, 0.0f);
	rotMat = glm::rotate(glm::mat4(1.0f), angleRadians, rotVector);//x axis
	viewMat = glm::rotate(viewMat,angleRadians,rotVector);



	glm::vec4 result = rotMat * glm::vec4(upVector,1.0f);
	upVector = glm::vec3(upVector.x, upVector.y, upVector.z);

	result = rotMat * glm::vec4(lookAtVector, 1.0f);
	lookAtVector = glm::vec3(lookAtVector.x, lookAtVector.y, lookAtVector.z);
}

void Camera::rotateYaw(float angle) {
	float angleRadians = glm::radians(angle);
	glm::vec3 rotVector = glm::vec3(0.0f, 1.0f, 0.0f);//y axis
	
	rotMat = glm::rotate(glm::mat4(1.0f), angleRadians, rotVector);
	viewMat = glm::rotate(viewMat, angleRadians, rotVector);

	glm::vec4 result = rotMat * glm::vec4(lookAtVector, 1.0f);
	lookAtVector = glm::vec3(lookAtVector.x, lookAtVector.y, lookAtVector.z);

}