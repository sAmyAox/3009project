#pragma once
#ifndef GRPHICS_IOBJECT_HEADER
#define GRPHICS_IOBJECT_HEADER

//=============================================================================
// graphicsObject.h
//
//Author: Doron Nussbaum (C) 2023 All Rights Reserved.
//-----------------------------------------------------
//
// Purpose: 
//--------------
// a. generic class for graphics objects. 
//
//
// Description:
//--------------
//  sub classes of objects can be inherited.  The class does the main funcionality of setting and rendering objects.

//
//
// License
//--------------
//
// Code can be used for instructional and educational purposes.
// Usage of code for other purposes is not allowed without a given permission by the author.
//
//
// Disclaimer
//--------------
//
// The code is provided as is without any warranty

//=============================================================================


#include "GL/glew.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include "GL/glut.h"
#endif

#include <vector>
#include "GL/nuss_math.h"


struct Vertex {
	Vertex() {
		pos = Vector4f(0, 0, 0, 1);
		col = Vector4f(0, 0, 0, 0);
	}
	Vertex(const Vector4f& _pos);
	Vertex(const Vector4f _pos, const Vector4f _col) {
		pos = _pos;
		col = _col;
		//memcpy(pos, (void*)&_pos, sizeof(pos));
		//memcpy(col, (void*)&_col, sizeof(col));
	}

	Vector4f pos;
	Vector4f col;
	//float pos[4];
	//float col[4];
};

typedef struct Vertex Vertex;

typedef std::vector<Vertex> Vertices;
typedef std::vector<unsigned int>	Indices;



class GraphicsObject
{
public:
	GraphicsObject();
	virtual ~GraphicsObject();

	virtual int render();
	virtual int render(Matrix4f worldMat);
	virtual void update() {};




protected:
	
	float rollAngle;	// rotation around the z-axis
	float pitchAngle;	// rotation around the x-axis
	float yawAngle;		// rotation around the y-axis
	Vector3f position;	// object position in space
	Vector3f scale;		// scaling of the object

	float worldRollAngle;	// rotation around the z-axis
	float worldPitchAngle;	// rotation around the x-axis
	float worldYawAngle;		// rotation around the y-axis
	Vector3f worldPosition;	// object position in space
	Vector3f worldScale;		// scaling of the object
	std::vector<GraphicsObject*> m_children;


	Matrix4f modelMat;
	Matrix4f worldMat;

	 


public:
	void setModelRotations(float rollAngle, float pitchAngle, float yawAngle);
	void setModelPosition(Vector3f position);
	void setModelPosition(float x, float y, float z);
	void incrementModelRotations(float rollAngle, float pitchAngle, float yawAngle);
	void incrementModelPosition(Vector3f position);
	void incrementModelPosition(float deltaX, float deltaY, float deltaZ);
	void setModelScale(Vector3f position);
	void setModelScale(float x, float y, float z);


	void setWorldRotations(float rollAngle, float pitchAngle, float yawAngle);
	void setWorldPosition(Vector3f position);
	void incrementWorldRotations(float rollAngle, float pitchAngle, float yawAngle);
	void addChild(GraphicsObject *obj);

private:


	void computeModelMat();
	void computeWorldMat();



};

#endif