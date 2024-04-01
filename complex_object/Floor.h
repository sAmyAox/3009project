#pragma once
#ifndef FLOOR_HEADER
#define FLOOR_HEADER

//=============================================================================
// floor.h
//
//Author: Doron Nussbaum (C) 2023 All Rights Reserved.
//-----------------------------------------------------
//
// Purpose: 
//--------------
// a.  class for rendering a subobject in a hierarchical object.  In this case it is a floor in a building 
//
//
// Description:
//--------------
//  This class defines a floor in a two story building. 
//
//	The base geometry is a cube
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


// INCLUDES 

#include "graphicsObject.h"

#include "graphicsObject.h"

class Floor : public GraphicsObject
{
public:
    Floor() {};
    ~Floor() {};

    void initGeom();
    int render(Matrix4f parentWorldMat);
    void update();



private:
    Vertices    m_vertices;
    Indices		m_indices;
};

#endif