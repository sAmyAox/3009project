#pragma once
#include "includPath.h"
#include "texture.h"
#include "particle.h"
class Emitter
{

public:
	Emitter(glm::vec3 loc);
	~Emitter();
	void update();
	void render();
	void createParticles(GLuint numOfParticles);
	glm::vec3 random();
	//glm::vec3 particlePosition;
	std::vector<float> particlePosition;
	//glm::vec4 particleColor;
	std::vector<float> particleColor;

	GLuint particlePositionBuffer;
	GLuint particleColorBuffer;
	std::vector<Particle> particles;

	public:
	GLuint ParticleObjectLocation;
	GLuint ParticleColorLocation;
	GLuint NumberOfParticles;
	glm::vec3 location;
};

