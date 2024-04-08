
#include "includPath.h"
#include "texture.h"
#include "shader.h"
#include "camera.h"

typedef struct point2D {
	GLfloat x, y;
} Point2D;


//globals

static const GLfloat g_vertex_buffer_data[] = {
	-1.0f,-1.0f,-1.0f, // triangle 1 : begin
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, // triangle 1 : end
	1.0f, 1.0f,-1.0f, // triangle 2 : begin
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f, // triangle 2 : end
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f
};

static const GLfloat g_uv_buffer_data[] = {
	0.000059f, 1.0f - 0.000004f,
	0.000103f, 1.0f - 0.336048f,
	0.335973f, 1.0f - 0.335903f,
	1.000023f, 1.0f - 0.000013f,
	0.667979f, 1.0f - 0.335851f,
	0.999958f, 1.0f - 0.336064f,
	0.667979f, 1.0f - 0.335851f,
	0.336024f, 1.0f - 0.671877f,
	0.667969f, 1.0f - 0.671889f,
	1.000023f, 1.0f - 0.000013f,
	0.668104f, 1.0f - 0.000013f,
	0.667979f, 1.0f - 0.335851f,
	0.000059f, 1.0f - 0.000004f,
	0.335973f, 1.0f - 0.335903f,
	0.336098f, 1.0f - 0.000071f,
	0.667979f, 1.0f - 0.335851f,
	0.335973f, 1.0f - 0.335903f,
	0.336024f, 1.0f - 0.671877f,
	1.000004f, 1.0f - 0.671847f,
	0.999958f, 1.0f - 0.336064f,
	0.667979f, 1.0f - 0.335851f,
	0.668104f, 1.0f - 0.000013f,
	0.335973f, 1.0f - 0.335903f,
	0.667979f, 1.0f - 0.335851f,
	0.335973f, 1.0f - 0.335903f,
	0.668104f, 1.0f - 0.000013f,
	0.336098f, 1.0f - 0.000071f,
	0.000103f, 1.0f - 0.336048f,
	0.000004f, 1.0f - 0.671870f,
	0.336024f, 1.0f - 0.671877f,
	0.000103f, 1.0f - 0.336048f,
	0.336024f, 1.0f - 0.671877f,
	0.335973f, 1.0f - 0.335903f,
	0.667969f, 1.0f - 0.671889f,
	1.000004f, 1.0f - 0.671847f,
	0.667979f, 1.0f - 0.335851f
};

static const unsigned int g_indices_data[]{
	0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35

};

static const glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(0.0f,  12.5f, 0.0f)
	//��������Ķ���Ϊ��0��25��0��
};

static const glm::vec3 cubeScaling[] = {
	glm::vec3(25.0f,5.0f,20.0f),
	glm::vec3(3.0f,10.0f,3.0f)
};

GLuint deskVbo, deskVao, deskEbo, deskColorVbo, deskPosVbo, deskUvVbo;
GLuint candleVbo, candleVao, candleEbo, candleColorVbo, candlePosVbo, candleUvVbo;
Shader triShader;
Shader candleShader;
Texture* textureDesk = nullptr;
Texture* textureCandle = nullptr;
Camera cam;

Point2D curMousePoint; // cur mouse point
Point2D lastMousePoint; // last mouse point

float angle = 0.0f;
glm::mat4 transformDesk(1.0f);
glm::mat4 transformCandle(1.0f);
glm::mat4 viewMat(1.0f);
glm::mat4 projMat(1.0f);


void doTransform() {
	time_t currenttime = time(NULL);	
	//transform = glm::rotate(transform, angle, glm::vec3(0.0, 0.0, 1.0));//��z����ת
	//transformDesk = glm::rotate(transformDesk, angle, glm::vec3(1.0, 0.0, 0.0));//��x����ת
	//transformDesk = glm::rotate(transformDesk, angle, glm::vec3(0.0, 1.0, 0.0));//��y����ת

}


void render() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// use the shader
	glUseProgram(triShader.getProgId());

	triShader.setInt("sampler",0);//ǰ��0������Ԫ��ȡ����
	//triShader.setInt("sampler", 1);//ǰ��1������Ԫ��ȡ���ݣ�����1������Ԫû�й��ض�����ȾΪ��ɫ
	
	triShader.setMatrix4("view", cam.getViewMatrix());
	triShader.setMatrix4("projection", cam.getProjMatrix());
	triShader.setMatrix4("transform", transformDesk);

	glBindVertexArray(deskVao);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//���
	glBindVertexArray(0);


	candleShader.setInt("sampler", 1);//ǰ��0������Ԫ��ȡ����

	candleShader.setMatrix4("view", cam.getViewMatrix());
	candleShader.setMatrix4("projection", cam.getProjMatrix());
	candleShader.setMatrix4("transform", transformCandle);


	glBindVertexArray(candleVao);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//for (unsigned int i = 0; i < 2; i++)
	//{
	//	// calculate the model matrix for each object and pass it to shader before drawing
	//	//
	//	transformDesk = glm::mat4(1.0f);
	//	transformDesk = glm::translate(transformDesk, cubePositions[i]);
	//	transformDesk = glm::scale(transformDesk, cubeScaling[i]);

	//	triShader.setMatrix4("transform", transformDesk);

	//	
	//}
	

	glutSwapBuffers();

}






int readCode(char * fileName, char **shaderCode, int *codeLength)
{
   int length = 0;
   FILE *fp = NULL;
   int rc = 0;
	// check for error in file name
    fp = fopen(fileName, "r");	// open file and check for errors
    if ( fp == NULL ) {
		rc = -1; 
		goto err;
	}

     // find the length of code
    fseek(fp, 0L, SEEK_END); 
    length = ftell(fp);
    rewind(fp);		// could use fseek(fp, 0L, SEEK_SET)
	if (length <= 0) {
		rc = -2;
		goto err;
	}

    if (length > 0) {
		// allocated space for code and check for errors
		*shaderCode = (char *) malloc(length+1);	// add a space for the '\0'
		if (*shaderCode == NULL) return(-2);
		memset((void *) *shaderCode, 0, length+1);
		fread((void *) *shaderCode, sizeof(char), length, fp);
		(*shaderCode)[length] = 0;
     }

	if (codeLength != NULL) *codeLength = length;

err:
	if (fp != NULL) fclose(fp);

	return(rc);
}


void prepareDeskVao() {


	
	float colors[] = {
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
	};


	//2 ����vbo
	glGenBuffers(1, &deskPosVbo);
	glBindBuffer(GL_ARRAY_BUFFER, deskPosVbo);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	
	glGenBuffers(1, &deskColorVbo);
	glBindBuffer(GL_ARRAY_BUFFER, deskColorVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);


	glGenBuffers(1, &deskUvVbo);
	glBindBuffer(GL_ARRAY_BUFFER, deskUvVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

	//3	���� ebo
	glGenBuffers(1, &deskEbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, deskEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_indices_data), g_indices_data, GL_STATIC_DRAW);

	//4 ����vao
	glGenVertexArrays(1, &deskVao);
	glBindVertexArray(deskVao);
	// 5��vbo��ebo ����������Ϣ
	glBindBuffer(GL_ARRAY_BUFFER, deskPosVbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, deskColorVbo);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

	
	glBindBuffer(GL_ARRAY_BUFFER, deskUvVbo);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	


	//5.2 ����ebo ��vao��
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, deskEbo);

	glBindVertexArray(0);
}

void prepareCandleVao() {
	float colors[] = {
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
	};


	//2 ����vbo
	glGenBuffers(1, &candlePosVbo);
	glBindBuffer(GL_ARRAY_BUFFER, candlePosVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &candleColorVbo);
	glBindBuffer(GL_ARRAY_BUFFER, candleColorVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);


	glGenBuffers(1, &candleUvVbo);
	glBindBuffer(GL_ARRAY_BUFFER, candleUvVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

	//3	���� ebo
	glGenBuffers(1, &candleEbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, candleEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_indices_data), g_indices_data, GL_STATIC_DRAW);

	//4 ����vao
	glGenVertexArrays(1, &candleVao);
	glBindVertexArray(candleVao);

	// 5��vbo��ebo ����������Ϣ
	glBindBuffer(GL_ARRAY_BUFFER, candlePosVbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, candleColorVbo);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);


	glBindBuffer(GL_ARRAY_BUFFER, candleUvVbo);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);


	//5.2 ����ebo ��vao��
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, candleEbo);
	
	//���
	glBindVertexArray(0);
}

//�����������
void prepareDeskTexture() {

	

	//textureDesk = new Texture("goku.jpg", 0);
	textureDesk = new Texture("desk.png", 0);

	printf("prepare texture complete\n");

}

void prepareCandleTexture() {

	textureCandle = new Texture("candle.png", 1);
}



//�����أ�
void prepareCamera() {

	//viewMat = glm::lookAt(glm::vec3(100.0f,100.0f,100.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f));

	cam.setCamera(glm::vec3(00.0f, 00.0f, 100.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	//cam.viewMat = glm::lookAt(glm::vec3(100.0f, 100.0f, 100.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	
}

void prepareProjection() {
	projMat = glm::perspective(70.0f,0.75f,0.1f,1000.0f);
}


void update(int value) {
	angle = 0.01f; // ������ת�Ƕ�
	doTransform();
	glutPostRedisplay(); // ��Ǵ�����Ҫ���»���
	glutTimerFunc(16, update, 0); // ÿ16�������һ��update����
}


void specialKeyboard(int key, int x, int y)
{
	switch (key) {
	case 033:
	case 'Q':
	case 'q':
		exit(1);
		break;
	case GLUT_KEY_LEFT:
		break;
	case GLUT_KEY_UP:
		
		break;
	case GLUT_KEY_RIGHT:
		
		break;
	case GLUT_KEY_DOWN:
		
		break;
	}
}


void setObjects() {

	transformDesk = glm::translate(transformDesk, cubePositions[0]);
	transformCandle = glm::translate(transformCandle, cubePositions[1]);



	transformDesk = glm::scale(transformDesk, cubeScaling[0]);
	transformCandle = glm::scale(transformCandle, cubeScaling[1]);

}



void mymouse(int button, int state, int x, int y)
{
	static int posX = 0, posY = 0;
	static int winWidth = 0, winHeight = 0;
	static int fullScreenState = 0;
	if (state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON) {
		printf("state is right mouse button pressed x,y=(%d, %d)\n", x, y);

	}
	else if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
		printf("state is left mouse button pressed x,y=(%d, %d)\n", x, y);
		//�������yaw pitch
	}

}



/**********************************************************************************************/
void myMotion(int x, int y)
{
	static int posX = 0, posY = 0;
	//���x++��pitch++
	//if  x-- pitch --
	//if y ++ yaw ++
	//if y -- yaw --
	if (lastMousePoint.x < x) {
		printf("pitch +\n");
		cam.rotateYaw(-0.10f);
	
	}else if(lastMousePoint.x > x) {
		printf("pitch -\n");
		cam.rotateYaw(0.10f);

	}
	else if (lastMousePoint.y < y) {
		printf("yaw+\n");
		cam.rotatePitch(-0.10f);
	}
	else if (lastMousePoint.y > y) {
		printf("yaw -\n");
		cam.rotatePitch(0.10f);
	}
	lastMousePoint.x = x;
	lastMousePoint.y = y;
	//printf("mouse motion  x,y = %d %d\n", x, y);

}

void mywheel(int wheel, int direction, int x, int y) {

	printf("wheel action: direction:%d\n", direction);
	//1 = up
	//-1 = down

	if (direction == 1) {
		//cam.zoomin();
		printf("pretned zoom in\n");
		cam.zoomIn();
	}
	else if (direction == -1) {
		//cam.zoomout();
		printf("pretned zoom out\n");
		cam.zoomOut();

	}

}

int initOpenGL()
{
	int rc = 0;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Sence Generation");
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glutDisplayFunc(render);

	glutMouseFunc(mymouse);
	glutMotionFunc(myMotion);
	glutMouseWheelFunc(mywheel);

	glutTimerFunc(25, update, 0);

	glEnable(GL_DEPTH_TEST);

	// Must be done after glut is initialized!
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		printf("Error - %s \n", glewGetErrorString(res));
		return (-1);
	}

	return(rc);
}



int main(int argc, char** argv)
{
	int rc = 0;
    glutInit(&argc, argv);


	//initialize
	initOpenGL();

	//creating Objects
	prepareDeskVao();
	prepareCandleVao();

	//set object positions
	setObjects();
	//prepare shader + textures
	prepareDeskTexture();
	prepareCandleTexture();

	//prepare camera attrib
	prepareCamera();
	prepareProjection();


	//create shader obj
	rc = triShader.createShaderProgram("tri.vs","tri.fs");
	if (rc != 0) {
		printf("Error in create Shader \n");
		printf("Hit <cr> to terminate program \n");
		getchar();
		return(1);
	}
	rc = candleShader.createShaderProgram("tri.vs", "tri.fs");
	if (rc != 0) {
		printf("Error in create Shader \n");
		printf("Hit <cr> to terminate program \n");
		getchar();
		return(1);
	}
	

    glutMainLoop();

    return 0;
}


