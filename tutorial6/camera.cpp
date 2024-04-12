#include "camera.h"


Camera::Camera() {
	viewMat = glm::mat4(1.0f);
	projMat = glm::mat4(1.0f);
	zoom = 20.0f;
	aspect = 0.75f;
	yaw = -90.0f;
	pitch = 0.0f;
	update();

};
Camera::~Camera() {};

void Camera::setCamera(glm::vec3 position) {}




void Camera::zoomIn() {

	zoom -= 0.10f;

	if (zoom < 19.0f) {
		zoom = 19.0f;
	}
	projMat = glm::perspective(zoom, aspect, 0.1f, 1000.0f);
	printf("zoom = %f", zoom);
}
void Camera::zoomOut() {
	zoom += 0.10f;

	if (zoom > 21.0f) {
		zoom = 21.0f;
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
	upVector = glm::vec3(result.x, result.y, result.z);

	result = rotMat * glm::vec4(lookAtVector, 1.0f);
	lookAtVector = glm::vec3(result.x, result.y, result.z);
}

void Camera::rotateYaw(float angle) {
	float angleRadians = glm::radians(angle);
	glm::vec3 rotVector = glm::vec3(0.0f, 1.0f, 0.0f);//y axis
	
	rotMat = glm::rotate(glm::mat4(1.0f), angleRadians, rotVector);
	viewMat = glm::rotate(viewMat, angleRadians, rotVector);

	glm::vec4 result = rotMat * glm::vec4(lookAtVector, 1.0f);
	lookAtVector = glm::vec3(result.x, result.y, result.z);


}

glm::vec3 Camera::getViewPos() {
	return position;
}

void  Camera::moveForward() {
	position += factor * lookAtVector;
	//update();
	setCamera(position, lookAtVector, upVector);


}
void  Camera::moveBackward() {
	position-= factor * lookAtVector;
	//update();
	setCamera(position, lookAtVector, upVector);
}
void  Camera::moveLeft() {
	position -= glm::normalize(glm::cross(lookAtVector, upVector)) * factor;
	//update();
	setCamera(position, lookAtVector, upVector);
}
void  Camera::moveRight() {
	position += glm::normalize(glm::cross(lookAtVector, upVector)) * factor;
	//update();
	setCamera(position, lookAtVector, upVector);
}
void Camera::moveUp() {
	position.y += factor;
	setCamera(position, lookAtVector, upVector);

}

void Camera::moveDown() {
	position.y -= factor;
	setCamera(position, lookAtVector, upVector);

}
void Camera::update() {

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	lookAtVector = glm::normalize(front);
	// also re-calculate the Right and Up vector

	rightVector = glm::normalize(glm::cross(lookAtVector, glm::vec3(0.0f,1.0f,0.0f)));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	upVector = glm::normalize(glm::cross(rightVector, lookAtVector));
}