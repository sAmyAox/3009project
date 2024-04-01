#pragma once
#ifndef TWO_STORY_OBJECT_HEADER
#define TWO_STORY_OBJECT_HEADER

//=============================================================================
// twoStory.h
//
//Author: Doron Nussbaum (C) 2023 All Rights Reserved.
//-----------------------------------------------------
//
// Purpose: 
//--------------
// a.  class for rendering a house. 
//
//
// Description:
//--------------
//  This class builds a two story house.  The first floor is a large cube and the second floor consists of two units which rotate on top
//
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
#include "graphicsObject.h"
#include "Floor.h"

class TwoStory : public GraphicsObject
{
public:
	void create();
	int render(Matrix4f parentWorldMat);
	void update();
	//void initGeom();

private:
	Floor firstFloor;		
	Floor secondFloor;		
	Floor apt1;
	Floor apt2;

};


/***************************************************/




#endif