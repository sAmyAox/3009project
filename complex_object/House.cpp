#include "House.h"



/*****************************************************************************/
/*Purpose: initilize the geometry of the house*/

void House::initGeom()
{


	// initialize the vertex buffer to be drawn


	roof[0].x = -15;    roof[0].y = 10;	roof[0].w = 1;
	roof[1].x = 15;    roof[1].y = 10;	roof[1].w = 1;
	roof[2].x = 0;    roof[2].y = 15;	roof[2].w = 1;

	house[0].x = -10; 	house[0].y = -10;	house[0].w = 1;
	house[1].x = 10; 	house[1].y = -10;	house[1].w = 1;
	house[2].x = 10; 	house[2].y = 10;	house[2].w = 1;
	house[3].x = -10; 	house[3].y = 10;	house[3].w = 1;

	// set the roof colour
	roofColour[0].r = 1.0; roofColour[0].g = 0.0; roofColour[0].b = 0.0;
	roofColour[1].r = 0.0; roofColour[1].g = 1.0; roofColour[1].b = 0.0;
	roofColour[2].r = 0.0; roofColour[2].g = 0.0; roofColour[2].b = 1.0;


}

/**************************************************************************************/

// Render house

int House::render()
{
	int i;

	Matrix3f rotMat;  // rotation matrix;
	Matrix3f scaleMat; // scaling matrix;
	Matrix3f transMat;	// translation matrix
	Matrix3f modelMat;	// final model matrix
	Matrix3f worldMat;	// world matrix
	Matrix3f shearMat;	// a shear transformatin matrix
	Vector3f p;

	// set the transformation matrix - the model transfomration
	modelMat = Matrix3f::identity(); // = Matrix4f::rotateRollPitchYaw(rollAngle, pitchAngle, yawAngle, 1);

	// set the scaling - this is model space to model space transformation
	scaleMat = Matrix3f::scale(4,4);
	modelMat = scaleMat * modelMat;


	// set the positon in the world model -> world
	transMat = Matrix3f::translation(100, 100);
	worldMat = transMat * modelMat;
	glBegin(GL_TRIANGLES);
	for (i = 0; i < 3; ++i) {
		glColor3f(roofColour[i].r, roofColour[i].g, roofColour[i].b);
		p = worldMat * roof[i];
		//p = roof[i];
		glVertex2f(p.x,p.y);
	}
	glEnd();

	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_TRIANGLE_FAN);
	for (i = 0; i < 4; ++i) {
		p = worldMat * house[i];
		//p = house[i];
		glVertex2fv((GLfloat*) &p);
	}
	glEnd();


	return(0);
}