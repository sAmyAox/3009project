#pragma once
#ifndef SOLUTION_HEADER
#define SOLUTION_HEADER



//=============================================================================
// solution.h
//
//Author: Doron Nussbaum (C) 2023 All Rights Reserved.
//-----------------------------------------------------
//
// Purpose: 
//--------------
// a. solution framework for assignments
//
//
// Description:
//--------------
// A simple framework for drawing objecs 
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

#include "house.h";
#include "Cube.h"
#include "TwoStory.h"
#include "camera.h"
#include "Table.h"



#define UPDATE_RENDERRED_OBJECTS 1000
#define FRAME_TIME 30

class Solution
{
public:
	Solution();
	~Solution();
	// initializing the opengl functions and windows
	int initOpenGL(int argc, char** argv, int posX, int posY, int winWidth, int winHeight);


	// static callback function 
	static void renderCB();
	static void passiveMouseCB(int x, int y);
	static void keyboardCB(unsigned char key, int x, int y);
	static void specialKeyboardCB(int key, int x, int y);
	static void winResizeCB(int width, int height);
	static void timerCB(int operation);
	static void menuFunCB(int num);

	static void setSolution(Solution * _sol);

	// generaL shader that will be used by all objects
	// initialization of the solution
	int initSolution();


	
	
private:
	static Solution* sol;
	Cube floor;
	TwoStory house;
	Table table;
	int perspective;

	int winWidth, winHeight;

	Camera cam;
	int factor;


	void render();
	void keyboard(unsigned char key, int x, int y);

	void passiveMouse(int x, int y);

	void specialKeyboard(int key, int x, int y);
	void winResize(int width, int height);
	int timer(int operation);

	void createMenu(void);
	int updateObjects();
};



#endif