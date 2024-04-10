#include "particle.h"

Particle::Particle(glm::vec3 loc) {
	location = loc;

	velocity = glm::vec3(0.03, 0.03, 0.03);
	color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	lifespan = 20.0f * random(1.0, 1.5);
}

void Particle::update() {
	float x_acc = 0.4f * random(1.0, 0.1);
	float y_acc = 0.4f * random(1.0, 0.1);
	float z_acc = 0.4f * random(1.0, 0.1);
	printf("x_acc = %f, y_acc = %f,z_acc = %f\n", x_acc, y_acc, z_acc);
	acceleration = glm::vec3(x_acc, y_acc, z_acc);

	velocity += acceleration;
	location += velocity;
	printf("velocity = (%f,%f,%f)\n", velocity.x, velocity.y, velocity.z);
	printf("location = (%f,%f,%f)\n", location.x, location.y, location.z);
	lifespan -= 0.7f;
	printf("lifespam = %f\n",lifespan);
	printf("color.r = %f\n", color.r);
	printf("color.g = %f\n", color.g);
	printf("color.b = %f\n", color.b);
	printf("color.a = %f\n", color.a);

}

bool Particle::isDead() {
	if (lifespan < 0.0) {
		return true;
	}
	else {
		return false;
	}
}

float Particle::random(float upper, float lower) {
	float range = (upper - lower);
	float random_float = lower + (range * ((float)rand()) / (RAND_MAX));
	printf("random_float = %f\n", random_float);
	return random_float;
}
glm::vec3 Particle::getPosition() {
	return location;
}

float Particle::getLifespan() {
	return lifespan;
}

glm::vec4 Particle::getColor() {
	return color;
}

void Particle::kill() {
	lifespan = 0.0;
}
glm::vec3 Particle::getAcceleration() {
	return acceleration;
}