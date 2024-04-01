#pragma once
#ifndef CANDLE_HEADER
#define CANDLE_HEADER
#include "graphicsObject.h"

class Candle : public GraphicsObject
{
public:
    Candle() {};
    ~Candle() {};

    void initGeom();
    int render(Matrix4f parentWorldMat);
    void update();



private:
    Vertices    m_vertices;
    Indices		m_indices;

};

#endif