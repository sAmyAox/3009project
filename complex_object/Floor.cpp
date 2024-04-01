#include "Floor.h"




void Floor::initGeom() 
{


    m_vertices.resize(8);
    // initial each vertex with a positin and colour
    m_vertices[0] = Vertex(Vector4f(-1, -1, 1, 1), Vector4f(0.5, 0.35, 0.05, 1));
    m_vertices[1] = Vertex(Vector4f(1, -1, 1, 1), Vector4f(0.5, 0.35, 0.05, 1));
    m_vertices[2] = Vertex(Vector4f(1, 1, 1, 1), Vector4f(0.5, 0.35, 0.05, 1));
    m_vertices[3] = Vertex(Vector4f(-1, 1, 1, 1), Vector4f(0.5, 0.35, 0.05, 1));

    m_vertices[4] = Vertex(Vector4f(-1, -1, -1, 1), Vector4f(0.5, 0.35, 0.05, 1));
    m_vertices[5] = Vertex(Vector4f(1, -1, -1, 1), Vector4f(0.5, 0.35, 0.05, 1));
    m_vertices[6] = Vertex(Vector4f(1, 1, -1, 1), Vector4f(0.5, 0.35, 0.05, 1));
    m_vertices[7] = Vertex(Vector4f(-1, 1, -1, 1), Vector4f(0.5, 0.35, 0.05, 1));

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

// Render the Floor

int Floor::render(Matrix4f parentWorldMat)
{
    int i, curVtx;

    Matrix4f worldMat;	// world matrix
    Vector4f p;
    
    // compute the transformation matrix - parnetMap*myWorldMap * modelMat


    worldMat = parentWorldMat * this->worldMat * modelMat;

    // compute the transformed object - set the colour and transform each vertex
    // Note that you have to create the set of triangles using the vertex information and
    // and the index of the faces

    // loop on all the vertices using the index array and
    glColor3f(1, 0, 0);
  
    glBegin(GL_TRIANGLES);
    for (i = 0; i < m_indices.size(); ++i) {
        curVtx = m_indices[i];   // getting the index of the current vertex 
        glColor3f(m_vertices[curVtx].col.x, m_vertices[curVtx].col.y, m_vertices[curVtx].col.z);
       // add the colour of the vertex 
        p = worldMat * m_vertices[curVtx].pos;
        //p = roof[i];
        glVertex3f(p.x, p.y, p.z);

       // compute the transformed geometry  and storing it in p       glVertex3f(p.x, p.y, p.z);
    }
    glEnd();
    
    for (int i = 0; i < m_children.size(); i++) {
        m_children[i]->render(parentWorldMat * this->worldMat);
    }

    // render any children  the parentWorldMat and "my" worldMat (this->WorldMat)
    // see similar code in the TwoStory class



    return(0);
}

/*********************************************************************/

void Floor::update()

{
    int i;

    // render any children
    //incrementModelRotations(1, 1, 0);
    /*
    for (int i = 0; i < m_children.size(); i++) {
        m_children[i]->incrementModelRotations(0, (i & 1) ?0 : 2, (i&1)?2:0);
    }
    */

}
