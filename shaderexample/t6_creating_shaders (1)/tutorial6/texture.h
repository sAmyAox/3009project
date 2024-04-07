#pragma once
#include <string>
#include "GL/glew.h"
#include "GL/nuss_matrix.h"
#include "GL/glut.h"
#include "gl/gl.h"


class Texture{

public:
	Texture(const std::string& path, unsigned int unit);
	~Texture();

	void bind(); /* ���Ե�ǰ�������ʱ����Ҫ�󶨵�ǰ���� */
private:
	GLuint mTexture{0};
	int mWidth{ 0 };
	int mHeight{ 0 };
	unsigned int mUnit{ 0 };

};

