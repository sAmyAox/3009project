#pragma once
#include "texture.h"
#include<assert.h>
#include<glaux.h>
#include<math.h>
#include<iostream>

using namespace std;
#define MAX_PARTICLES 10000
class Particle {
public:
	Particle();
	~Particle();
	void LoadPartTexture();
	void InitalPart();
	void DrawPart();
private:
	struct Particles
	{
		bool	active;
		float	life;
		float	fade;
		//colors
		float	r;
		float	g;
		float	b;
		//positiions
		float	x;
		float	y;
		float	z;
		//directions
		float	xd;
		float	yd;
		float	zd;
		//gravities
		float	xg;
		float	yg;
		float	zg;
	};
	Texture* PartTexture;
	Particles part[MAX_PARTICLES];
	static GLfloat white[3] = { 1.0f,1.0f,1.0f };
	static GLfloat blue[3] = { 0.0f,0.0f,1.0f };
	static GLfloat yellow[3] = { 1.0f,1.0f,0.0f };
	static GLfloat orange[3] = { 1.0f,0.5f,0.0f };
	static GLfloat red[3] = { 1.0f,0.1f,0.0f };

	float posX = 0.0f;
	float posY = -5.0f;
	float posZ = 0.0f;

	float gravX = 0.0f;
	float gravY = 0.0f;
	float gravZ = 0.0f;
};