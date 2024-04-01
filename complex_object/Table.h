#pragma once
#ifndef TABLE_HEADER
#define TABLE_HEADER
#include "graphicsObject.h"

class Table : public GraphicsObject
{
public:
    Table() {};
    ~Table() {};

    void initGeom();
    int render(Matrix4f parentWorldMat);
    void update();



private:
    Vertices    m_vertices;
    Indices		m_indices;

};

#endif