#pragma once
#include "includPath.h"
class Particle
{
public:
	Particle();
	Particle(glm::vec3 location);

	void update();
	bool isDead();
	float random(float upper, float lower);
	float getLifespan();
	glm::vec4 getColor();
	glm::vec3 getPosition();
	glm::vec3 getAcceleration();
	void kill();

private:
	glm::vec3 location;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	glm::vec4 color;
	float lifespan;
};