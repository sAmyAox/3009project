#pragma once
#include "includPath.h"
class ShadowMap_FBO
{
public:
    ShadowMap_FBO();

    ~ShadowMap_FBO();

    bool Init(unsigned int WindowWidth, unsigned int WindowHeight);

    void BindForWriting();

    void BindForReading(GLenum TextureUnit);

public:
    unsigned int mWidth;
    unsigned int mHeight;
    GLuint m_fbo;
    GLuint m_shadowMap;
};

