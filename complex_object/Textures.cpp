#include"Textures.h"
#include"GL/soil.h"
#include"stb_image.h"

Textures::Textures():texId(-1){}

Textures::~Textures() {

}

void Textures::loadTextures(char* imageFileName, GLuint texTarget) {
	int width, height;
	int numChannels;
	unsigned char* image = stbi_load("oak.png",&width,&height,&numChannels,0);

	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);
	if (image){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Textures::bindToTextureUnit(int textureUnit) {
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, texId);
	this->textureUnit = textureUnit;
}

GLuint Textures::getTexId() {
	return texId;
}