#include  "Candle.h"

void Candle::initGeom() {
    m_vertices.resize(8);
    // initial each vertex with a positin and colour
    m_vertices[0] = Vertex(Vector4f(-1, -1, 1, 1), Vector4f(1, 0, 0, 1));
    m_vertices[1] = Vertex(Vector4f(1, -1, 1, 1), Vector4f(0, 1, 0, 1));
    m_vertices[2] = Vertex(Vector4f(1, 1, 1, 1), Vector4f(0, 0, 1, 1));
    m_vertices[3] = Vertex(Vector4f(-1, 1, 1, 1), Vector4f(1, 1, 0, 1));

    m_vertices[4] = Vertex(Vector4f(-1, -1, -1, 1), Vector4f(1, 0, 1, 1));
    m_vertices[5] = Vertex(Vector4f(1, -1, -1, 1), Vector4f(0, 1, 1, 1));
    m_vertices[6] = Vertex(Vector4f(1, 1, -1, 1), Vector4f(0.5, 0.5, 0, 1));
    m_vertices[7] = Vertex(Vector4f(-1, 1, -1, 1), Vector4f(0.5, 0, 0.5, 1));

    m_indices.resize(36);
    int indices[] = {
        // front face
        0, 1, 2,
        2, 3, 0,
        // top face
        3, 2, 6,
        6, 7, 3,
        // back face
        7, 6, 5,
        5, 4, 7,
        // bottom face
        4, 5, 1,
        1, 0, 4,
        // left face
        4, 0, 3,
        3, 7, 4,
        // right face
        1, 5, 6,
        6, 2, 1
    };


    m_indices.assign(std::begin(indices), std::end(indices));
}