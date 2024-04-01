#include "TwoStory.h"



/*****************************************************************************/
/*Purpose: initilize the geometry of the house*/

void TwoStory::create()
{
			// create the geometry of the first floor

	firstFloor.initGeom();
	// set the first floor geometry (modelScale wrt the x,y and z axis)

	firstFloor.setModelScale(20, 5, 5);
	// set the scale of the first floor

	firstFloor.setWorldPosition(Vector3f(10, 0, 10));
	// set the world position of the first floor


			// create the second floor 
	//Floor apt1;
	// create the second floor apt1;

	apt1.initGeom();
	// initialize the geometry

	apt1.setModelScale(2, 2, 2);
	// set the scale

	apt1.setWorldPosition(Vector3f(-15,8,0));
	// position the apt1 with respect to the ground floor

	firstFloor.addChild(&apt1);
	// add the apt1 as a child of the first floor

		
	//Floor apt2;
	// create the second floor apt2;

	apt2.initGeom();
	// initialize the geometry
	apt2.setModelScale(2, 2, 2);
	// set the scale
	apt2.setWorldPosition(Vector3f(15, 8, 0));
	// position the apt2 with respect to the ground floor

	firstFloor.addChild(&apt2);
	// add the apt2 as a child of the first floor

}

/**************************************************************************************/

// Render TwoStory

int TwoStory::render(Matrix4f parentWorldMat)
{
	int i,j;

	Matrix4f worldMat;	// world matrix
	Vector4f p;
// compute the house transformation matrix (transMat) using parentMatrix, object's worldMat and 
	// the object's modelMat
	worldMat = parentWorldMat * this->worldMat * modelMat;

	// render the my object (floor)- using the transsformation matrix (transMat)
	
	firstFloor.render(worldMat);
	// render any children

	for (int i = 0; i < m_children.size(); i++) {
		m_children[i]->render(parentWorldMat * worldMat);
	}

	return(0);
}

/*********************************************************************/

void TwoStory::update()

{
	int i;
	static int nc = 0;
	int changeDir = 75;
	static int dir = 1;

	nc++;
	firstFloor.update();
	if (nc > changeDir) {
		dir *= -1;
		nc = 0;
	}
	//firstFloor.incrementWorldRotations(0, 0, 1 * dir);
}
