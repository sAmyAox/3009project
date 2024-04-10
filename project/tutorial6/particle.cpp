#include "particle.h"
void Particle::LoadPartTexture() {
	PartTexture = new Texture("particle.png", 1);
}

void Particle::InitalPart() {
	LoadPartTexture();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

	for (int i=0; i < MAX_PARTICLES; i++)
	{
		part[i].active = true;
		part[i].life = 1.0f;
		part[i].fade = float(rand() % 100) / 1000.0f + 0.003f;
		part[i].r = white[0];
		part[i].g = white[1];
		part[i].b = white[2];
		part[i].xi = float((rand() % 50) - 25.0f) * 10.0f;
		part[i].yi = float((rand() % 50) - 25.0f) * 10.0f;
		part[i].zi = float((rand() % 50) - 25.0f) * 10.0f;
		part[i].xg = 0.0f;
		part[i].yg = 0.8f;
		part[i].zg = 0.0f;
	}
}

void Particle::DrawPart() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		if (part[i].active)
		{

			float x = part[i].x;
			float y = part[i].y;
			float z = part[i].z + zoom;
			glColor4f(part[i].r, part[i].g, part[i].b, part[i].life);

			glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2d(1, 1); glVertex3f(x + 0.5f, y + 0.5f, z);
			glTexCoord2d(0, 1); glVertex3f(x - 0.5f, y + 0.5f, z);
			glTexCoord2d(1, 0); glVertex3f(x + 0.5f, y - 0.5f, z);
			glTexCoord2d(0, 0); glVertex3f(x - 0.5f, y - 0.5f, z);
			glEnd();

			part[i].x += part[i].xi / (750);
			part[i].y += part[i].yi / (1000);
			part[i].z += part[i].zi / (750);
			if ((part[i].x > posX) && (part[i].y > (0.1 + posY))) {
				part[i].xg = -0.3f;
			}
			else if ((part[i].x < posX) && (par[i].y > (0.1 + posY))) {
				part[i].xg = 0.3f;
			}
			else {
				part[i].xg = 0.0f;
			}

			part[i].xi += (part[i].xg + gravX);
			part[i].yi += (part[i].yg + gravY);
			part[i].zi += (part[i].zg + gravZ);
			part[i].life -= particle[loop].fade;

			if (part[i].life < 0.0f)
			{
				part[i].life = 1.0f;
				part[i].fade = float(rand() % 100) / 1000.0f + 0.003f;
				part[i].x = posX;
				part[i].y = posY;
				part[i].z = posZ;
				part[i].xi = float((rand() % 60) - 30.0f);
				part[i].yi = float((rand() % 60) - 30.0f);
				part[i].zi = float((rand() % 60) - 30.0f);
				part[i].r = white[0];
				part[i].g = white[1];
				part[i].b = white[2];
			}
			else if (part[i].life < 0.4f)
			{
				part[i].r = red[0];
				part[i].g = red[1];
				part[i].b = red[2];
			}
			else if (part[i].life < 0.6f)
			{
				part[i].r = orange[0];
				part[i].g = orange[1];
				part[i].b = orange[2];
			}
			else if (part[i].life < 0.75f)
			{
				part[i].r = yellow[0];
				part[i].g = yellow[1];
				part[i].b = yellow[2];
			}
			else if (part[i].life < 0.85f)
			{
				part[i].r = blue[0];
				part[i].g = blue[1];
				part[i].b = blue[2];
			}
		}
	}
	glutPostRedisplay();
	glutSwapBuffers();
}