

//=============================================================================
// solution.c
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

// INCLUDES

#include "Solution.h"

/***************************************************************************/

// DEFINES 

// MENU defines
#define EXIT_PROGRAM 0
#define CLEAR_SCREEN 1
#define RENDER_HOUSE_1 10
#define RENDER_HOUSE_2 20
#define PERSPECTIVE_ORTHO 5
#define RENDER_WIREFRAME 2
#define RENDER_FILLED	3



/************************************************************/
//	GLOBALS

Solution *Solution::sol = NULL;

/****************************************************************************/

Solution::Solution() : winWidth(0), winHeight(0)

{
	perspective = 1;
}

/*************************************************************************/


Solution::~Solution()
{

}

/******************************************************************************/


// initializing the opengl functions and windows
int Solution::initOpenGL(int argc, char **argv, int posX, int posY, int winWidth, int winHeight)
{
	int winid1;
	//initialize glut
	glutInit(&argc, argv);

	//initialize OpenGLwindow
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(posX, posY);
	glutInitWindowSize(winWidth, winHeight);
	this->winWidth = winWidth;
	this->winHeight = winHeight;
	winid1 = glutCreateWindow("Drawing Basic Objects");

//	glutSetWindow(winid1);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glDisable(GL_CULL_FACE);
	glutDisplayFunc(Solution::renderCB);
	glutReshapeFunc(Solution::winResizeCB);
	glutKeyboardFunc(Solution::keyboardCB);
	glutSpecialFunc(Solution::specialKeyboardCB);
	glutPassiveMotionFunc(Solution::passiveMouseCB);
	glutTimerFunc(FRAME_TIME, Solution::timerCB, UPDATE_RENDERRED_OBJECTS);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// create a menu
	createMenu();



	GLenum res = glewInit();
	if (res != GLEW_OK) {
		printf("Error - %s \n", glewGetErrorString(res));
		return (-1);
	}


	return 0;
}

/************************************************************/

// render callback function.  This is a static funcion


void Solution::renderCB()
{

	sol->render();
	
}


/************************************************************/

// keyboard callback function.  This is a static funcion


void Solution::passiveMouseCB(int x, int y)
{
	sol->passiveMouse(x, y);
}


/************************************************************/

// keyboard callback function.  This is a static funcion


void Solution::keyboardCB(unsigned char key, int x, int y)
{
	sol->keyboard(key, x, y);
}


/************************************************************/

// special keyboard callback function.  This is a static funcion



void Solution::specialKeyboardCB(int key, int x, int y)
{
	sol->specialKeyboard(key, x, y);
}


/************************************************************/

// window resize callback function.  This is a static funcion



void Solution::winResizeCB(int width, int height)
{
	sol->winResize(width, height);
	
}

/************************************************************/

// timer  callback function.  This is a static funcion


void Solution::timerCB(int operation)
{

	// set glut to inovke the timer function again. 
// Determine what the next action should be.


	glutTimerFunc(FRAME_TIME, Solution::timerCB, UPDATE_RENDERRED_OBJECTS);	
	sol->timer(operation);

}


/************************************************************/

// timrt  function.  


int Solution::timer(int operation)
{
	
	switch (operation) {
	case UPDATE_RENDERRED_OBJECTS:
		updateObjects();
	default:
		break;
	}
	return(0);
}




/******************************************************************************/
// initialization of the solution.  Here the class creates all the objects that are to be used during the rendering. 
// and it sets up the initial configuration.

int Solution::initSolution()
{
	int rc;
	Vertices vtx;
	Indices ind;


	// Add Code
	// initialize the geomegtry and transformation of the floor object
	// world position and scale
	//floor.setInitModel();
	/*
	floor.initGeom();
	floor.setModelScale(20, 5, 20);//model to model
	//i'm not sure if this should be (5,5,5)because the figure 2 looks like it is a cube , not rectangular
	floor.setModelPosition(0, 0, 0);//model to model
	*/


	// create the house by invoking the house create function

	house.create();
	house.setModelPosition(10, 10, 0);

	//table.initGeom();
	//table.setModelScale(50, 10, 10);
	//table.setModelPosition(300, 300, 0);

	//house.initGeom();




	// set the camera initial position
	cam.setCamera(Vector3f(15, 15, 70), Vector3f(15, 0, 0), Vector3f(0, 1, 0));

	



	return 0;
}


/**********************************************************************/

void Solution::setSolution(Solution * _sol)
{
	Solution::sol = _sol;
}



/************************************************************/

// render function.  


void Solution::render()
{

	Vector3f viewerPosition;
	Vector3f lookAtPoint;
	Vector3f upVector;;
	Matrix4f viewMat, projMat;

	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glDisable(GL_CULL_FACE);

	glViewport(0, 0, (GLsizei)winWidth, (GLsizei)winHeight);

	// set the view model transformation
	glMatrixMode(GL_MODELVIEW);
	viewMat = cam.getViewMatrix(NULL);	// get the camera view transformation

	// pass it to opengl before draw
	viewMat = Matrix4f::transpose(viewMat);
	//viewMat = Matrix4f::identity();
	glLoadMatrixf((GLfloat*)viewMat.data());


	// set the projection matrix
	projMat = cam.getProjectionMatrix(NULL);

	glMatrixMode(GL_PROJECTION);
	// pass it to opengl - Note that OpenGL accepts the matrix in column major
	projMat = Matrix4f::transpose(projMat);
	glLoadMatrixf((GLfloat*)projMat.data());



	// render the objects
	floor.render(Matrix4f::identity());
	house.render(Matrix4f::identity());
	//firFloor.render(Matrix4f::identity());
	table.render(Matrix4f::identity());

	glutSwapBuffers();
}


/************************************************************/

// passive motion function. 


void Solution::passiveMouse(int x, int y)

{
	int winid = glutGetWindow();
	//std::cout << "Passive Mouse winId=" << winid << "(" << x << " , " << y << ")" << std::endl;
}


/************************************************************/

// keyboard handling function. 


void Solution::keyboard(unsigned char key, int x, int y)
{
	int winId;

	switch (key) {
	case 'q':
		winId = glutGetWindow();
		glutDestroyWindow(winId);
		exit(0);
		break;	
	case 'i':
		house.incrementModelPosition(Vector3f(-1, 0, 0)); // translate to left
		printf("i pressed\n");

		break;
	case 'l':
		house.incrementModelPosition(Vector3f(1, 0, 0)); // translate to right
		printf("L pressed\n");

		break;
	case 'j':
		house.incrementModelPosition(Vector3f(0, 0, -1)); // translate to down
		printf("J pressed\n");

		break;
	case 'k':
		house.incrementModelPosition(Vector3f(0, 0, 1)); // translate to rup
		printf("K pressed\n");

		break;
	case 'a':
		house.incrementWorldRotations(1, 0, 0); //CCW x-axis

		break;
	case 'd':
		house.incrementWorldRotations(-1, 0, 0); // CW x-axis

		break;
	case 'w':
		house.incrementWorldRotations(0, 1, 0); // CCW y-axis

		break;
	case 's':
		house.incrementWorldRotations(0, -1, 0); // CW y-axis

		break;

	default:

		break;
	}

	glutPostRedisplay();
}


/************************************************************/

// special keyboard handling  function.  



void Solution::specialKeyboard(int key, int x, int y)
{
}


/************************************************************/

// window resize handling function.  



void Solution::winResize(int width, int height)
{
	//winWidth = width;
	//winHeight = height;
	/* use the full view port */
	glViewport(0, 0, width, height);

	// update the window width and height
	winWidth = width;
	winHeight = height;


}

/***********************************************************/
// update the state of the objects

int Solution::updateObjects()
{

	// recall that this will be carried out in the model space
	house.update();
	floor.update();
	glutPostRedisplay();
	return 0;
}




/******************************************************************************/
/* purpose: Creates a menu and a sub menuassigns it to the right mouse button*/

void Solution::createMenu(void) {

	// create a submenu
	int submenu_id = glutCreateMenu(menuFunCB);
	glutAddMenuEntry("Render filled ", RENDER_FILLED);
	glutAddMenuEntry("Render wireframe", RENDER_WIREFRAME);

	// create the main menu
	int menu_id = glutCreateMenu(menuFunCB);
	//glutAddMenuEntry("Clear Screen", CLEAR_SCREEN);
	glutAddSubMenu("Render Objects", submenu_id);
	glutAddMenuEntry("Quit", EXIT_PROGRAM);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/******************************************************************************/
/* purpose: Processes the response from the GLUT menu entry

Note that the function asigns to a global variable the optin that the user wanted

*/

void Solution::menuFunCB(int num) 
{
	int winId;
	switch (num) {
	case EXIT_PROGRAM:
		winId = glutGetWindow();
		glutDestroyWindow(winId);
		exit(0);
		break;
	case RENDER_FILLED:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		break;
	case RENDER_WIREFRAME:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		break;

	default: 
		break;
	}
	glutPostRedisplay();

}