// main.cpp : Defines the entry point for the console application.
/*

File is the entry to program
*/


#include "Solution.h"


int main(int argc, char** argv)
{
	Solution sol;
	int posX = 100, posY= 10;	// windows position
	int winWidth = 600, winHeight = 600;	// window size

	sol.initOpenGL(argc, argv, posX, posY, winWidth, winHeight);
	sol.initSolution();
	Solution::setSolution(&sol);

	glutMainLoop();



	return 0;
}

