#include "Emitter.h"
Emitter::Emitter(glm::vec3 loc) {
	location = loc;
}

Emitter::~Emitter() {}


void Emitter::createParticles(GLuint numOfParticles) {
	NumberOfParticles = numOfParticles;

	//create particle based on given number

	for (int i = 0; i < NumberOfParticles; ++i) {
		glm::vec3 temp = random();
		temp += location;
		printf("temp = %f,%f,%f\n", temp.x, temp.y, temp.z);
		Particle p(location);
		particles.push_back(p);

		//printf("p acceleration = (%f, %f, %f)\n",p.getAcceleration().x, p.getAcceleration().y, p.getAcceleration().z);
		
		
		
		particlePosition.push_back(p.getPosition().x);
		particlePosition.push_back(p.getPosition().y);
		particlePosition.push_back(p.getPosition().z);
		particlePosition.push_back(p.getColor().r);
		particlePosition.push_back(p.getColor().g);
		particlePosition.push_back(p.getColor().b);

		//setting the rgb'A' to have effect of fade when a particle is died
		float alpha = 1.2 - p.getLifespan() / 255;

		if (alpha > 0.95f) {
			alpha = 0.94f;
		}

		particlePosition.push_back(alpha);


		printf("p.getPosition().x = %f\n", p.getPosition().x);
		printf("p.getPosition().y = %f\n", p.getPosition().y);
		printf("p.getPosition().z = %f\n", p.getPosition().z);
		printf("p life span = %f\n", p.getLifespan());

		printf("p.r = %f\n", p.getColor().r);
		printf("p.g = %f\n", p.getColor().g);
		printf("p.b = %f\n", p.getColor().b);
		printf("p.a = %f\n", p.getColor().a);


		glGenVertexArrays(1, &ParticleObjectLocation);
		glBindVertexArray(ParticleObjectLocation);

		glGenBuffers(1, &particlePositionBuffer);

		glBindBuffer(GL_ARRAY_BUFFER, particlePositionBuffer);
		glBufferData(GL_ARRAY_BUFFER, particlePosition.size() * sizeof(float), particlePosition.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	}
}

void Emitter::render() {
	glBindVertexArray(ParticleObjectLocation);
	glDrawArrays(GL_POINTS, 0, NumberOfParticles);
	//printf("number of particles = %d\n",NumberOfParticles);
	//printf("drawing particles\n");
	glBindVertexArray(0);
}


void Emitter::update() {
	glBindBuffer(GL_ARRAY_BUFFER, particlePositionBuffer);

	// Updates the data for each individual particle
	for (int i = 0; i < NumberOfParticles; i++) {
		particles[i].update();
		printf("updateing particle num %d\n", i);
	}

	for (int i = 0; i < NumberOfParticles; i = i++) {

		// Setting the alpha based on lifespan with clamps so it does not get too dark or too light
		float alpha = 1.2 - particles[i].getLifespan() / 255;

		if (alpha > .95) {
			alpha = 1.0;
		}
		else if (alpha < 0.75) {
			alpha = 0.75;
		}
		if (particles[i].isDead()) {
			// If a particle dies, it is respawned at the emitter
			printf("particle num %d is dead, regenerating\n", i);
			glm::vec3 temp = particles[i].getPosition();
			temp += location;
			Particle p(location);
			particles[i] = p;
		}
		else {
			float curr_x = particles[i].getPosition().x;
			float curr_y = particles[i].getPosition().y;
			float curr_z = particles[i].getPosition().z;
			// 7 in a group
			particlePosition[i * 7 + 0] = curr_x;
			particlePosition[i * 7 + 1] = curr_y;
			particlePosition[i * 7 + 2] = curr_z;

			if (curr_y > 28.0f) {
				particles[i].kill();
			}

			else if (curr_y < 100.0f) {
				particlePosition[i * 7 + 3] = 1.0f;
				particlePosition[i * 7 + 4] = 0.5f;
				particlePosition[i * 7 + 5] = 0.0f;
			
			}
			particlePosition[i * 7 + 6] = alpha;
		
		}



	}
	glBufferSubData(GL_ARRAY_BUFFER, 0, particlePosition.size() * sizeof(GLfloat), particlePosition.data());
}

glm::vec3 Emitter::random() {
	float lower = -0.02f;
	float upper = 0.02f;
	float range = upper - lower;
	float rand_x = lower + (range * ((float)rand()) / (RAND_MAX));
	float rand_y = lower + (range * ((float)rand()) / (RAND_MAX));
	float rand_z = lower + (range * ((float)rand()) / (RAND_MAX));


	return glm::vec3(rand_x, rand_y, rand_z);
}
