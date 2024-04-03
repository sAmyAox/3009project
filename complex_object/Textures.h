#pragma once
#include <windows.h>
#include "GL/glew.h"
#include "GL/glut.h"
#include "GL/glut.h"

#include "gl/gl.h"
#include "Shader.h"

class Textures {
	GLuint texId;
	int textureUnit;

public:
	Textures();
	~Textures();

	void loadTextures(char* imageFileName, GLuint texTarget);
	void bindToTextureUnit(int textureUnit);
	GLuint setTextureSampler(Shader shader, char* sampleName, GLuint samplerId);

	GLuint getTexId();