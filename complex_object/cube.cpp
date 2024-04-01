#include "Cube.h"




void Cube::initGeom() //model to model
{


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

    // set the colours


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






/**************************************************************************************/

// Render the Cube

int Cube::render(Matrix4f parentWorldMat)
{
    int i, j;

    Matrix4f worldMat;	// world matrix
    Vector4f p;
    
    
    worldMat = parentWorldMat * this->worldMat * modelMat;

    glColor3f(1, 0, 0);

    glBegin(GL_TRIANGLES);
    for (i = 0; i < m_indices.size(); ++i) {
        j = m_indices[i];
        glColor3f(m_vertices[j].col.x, m_vertices[j].col.y, m_vertices[j].col.z);
        p = worldMat * m_vertices[j].pos;
        //p = roof[i];
        glVertex3f(p.x, p.y, p.z);
    }
    glEnd();


    // render any children
    for (int i = 0; i < m_children.size(); i++) {
        m_children[i]->render(parentWorldMat * this->worldMat);
    }



    return(0);
}

/*********************************************************************/

void Cube::update()

{
    int i;

    // render any children
    incrementModelRotations(0, 1, 1);
    for (int i = 0; i < m_children.size(); i++) {
        m_children[i]->incrementModelRotations(0, (i & 1) ?0 : 2, (i&1)?2:0);
    }


}
