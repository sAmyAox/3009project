#pragma once
#ifndef HOUSE_OBJECT_HEADER
#define HOUSE_OBJECT_HEADER

//=============================================================================
// house.h
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
//  .

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
class House : public GraphicsObject
{
public:
	void House::initGeom();
	int render();

private:
	Vector3f roof[3];		// roof coordinates
	Vector3f house[4];		// house coordinates
	Vector3f roofColour[3];	// roof colour (per vertex)
	Vector3f houseColour;	// colour of the house
};


/***************************************************/




#endif