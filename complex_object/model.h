#pragma once

#include <glut.h>
#include <vector>

#include "nuss_vector.h"
///////////////////////////////////////////////////////////////////////////////
float Random();
///////////////////////////////////////////////////////////////////////////////
struct Vertex{
    Vertex(){}
    Vertex( const Vector3f& _pos );
    Vertex( const Vector3f _pos, const Vector3f& _col ){
        pos[0] = _pos.x; pos[1] = _pos.y; pos[2] = _pos.z; pos[3] = 1.0f;
        col[0] = _col.x; col[1] = _col.y; col[2] = _col.z; col[3] = 1.0f;
    }
    float pos[4];
    float col[4];
};
typedef std::vector<Vertex> Vertices;
typedef std::vector<GLuint>	Indices;
///////////////////////////////////////////////////////////////////////////////
class Shader;
class Model{
public:
    Model();
    virtual ~Model(){};
    void Draw();
protected:
    void Create( Shader& shader );
    Vertices    m_vertices;
    Indices		m_indices;

    Shader*     m_shader;
    GLuint      m_vao;			//vertex array object
    GLuint      m_vbo;			//vertex buffer object for vertices
    GLuint		m_idxVbo;		//vertex buffer object for indices
};
///////////////////////////////////////////////////////////////////////////////
class Sphere : public Model{
public:
    Sphere(){}
    void Create(
        Shader& shader,
        int rings,								//latitude
        int sectors);							//longitude
};
///////////////////////////////////////////////////////////////////////////////
class Cylinder : public Model{
public:
    Cylinder(){}
    void Create(
        Shader& shader,
        int sectors );
};
///////////////////////////////////////////////////////////////////////////////
class Floor: public Model{
public:
    Floor(){}
    void Create( Shader& shader );
};
