#pragma once
#include "includPath.h"

class Texture {

public:
	Texture(const std::string& path, unsigned int unit);
	~Texture();

	void bind(); /* 外界对当前纹理更改时，需要绑定当前纹理 */
private:
	GLuint mTexture{ 0 };
	int mWidth{ 0 };
	int mHeight{ 0 };
	unsigned int mUnit{ 0 };

};

