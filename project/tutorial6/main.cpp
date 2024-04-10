
#include "includPath.h"
#include "texture.h"
#include "shader.h"
#include "camera.h"
#include "Emitter.h"

typedef struct point2D {
	GLfloat x, y;
} Point2D;

//globals
glm::vec3 lightPos = glm::vec3(0.0f, 25.5f, 0.0f);
glm::vec3 lightColor = glm::vec3(0.5f,0.5f,0.5f);

static const GLfloat g_vertex_buffer_data[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

static const GLfloat g_uv_buffer_data[] = {
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 0.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 0.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 0.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 0.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 0.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 0.0f
};

static const unsigned int g_indices_data[]{
	0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35

};

static const glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),//table
	glm::vec3(0.0f,  15.0f, 0.0f),//candle
	glm::vec3(0.0f,	 25.5f, 0.0f),//lightSrc
	glm::vec3(20.0f, 7.5f, 0.0f), //addtional cube position
	glm::vec3(20.0f, 7.5f, 20.0f), //addtional cube position
	glm::vec3(40.0f, 7.5f, 10.0f),//addtional cube position
	glm::vec3(0.0f,  50.0f, 0.0f) //addtional cube position


	//现在蜡烛的顶点为（0，25，0）
};

static const glm::vec3 cubeScaling[] = {
	glm::vec3(100.0f,10.0f,60.0f),
	glm::vec3(6.0f,20.0f,6.0f),
	glm::vec3(1.0f,1.0f,1.0f),
	glm::vec3(5.0f,5.0f,5.0f)
};

GLuint deskVbo, deskVao, deskEbo, deskNormalVbo, deskPosVbo, deskUvVbo;
GLuint candleVbo, candleVao, candleEbo, candleNormalVbo, candlePosVbo, candleUvVbo;
GLuint lightVbo, lightVao, lightEbo, lightNormalVbo, lightPosVbo, lightUvVbo;
Shader triShader;
Shader candleShader;
Shader lightShader;
Shader particleShader;
Texture* textureDesk = nullptr;
Texture* textureCandle = nullptr;
Texture* textureLight = nullptr;
Texture* textureShadow = nullptr;
bool marker = true;
bool lightSwitch = true;
Camera cam;
Point2D curMousePoint; // cur mouse point
Point2D lastMousePoint; // last mouse point
float angle = 0.0f;
float clearColour[4] = { 1.0,1.0,1.0,1.0 };
glm::mat4 transformDesk(1.0f);
glm::mat4 transformCandle(1.0f);
glm::mat4 transformLight(1.0f);
glm::mat4 transformCube1(1.0f);
glm::mat4 transformCube2(1.0f);
glm::mat4 transformCube3(1.0f);
glm::mat4 transformCube4(1.0f);
glm::mat4 viewMat(1.0f);
glm::mat4 projMat(1.0f);

float passedTime = 0.0f;
Emitter* e1;

//创建物体Vao

void prepareLightVao() {

	//2 创建vbo
	glGenBuffers(1, &lightPosVbo);
	glBindBuffer(GL_ARRAY_BUFFER, lightPosVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	//3	创建 ebo
	glGenBuffers(1, &lightEbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_indices_data), g_indices_data, GL_STATIC_DRAW);

	//4 创建vao
	glGenVertexArrays(1, &lightVao);
	glBindVertexArray(lightVao);
	// 5绑定vbo，ebo 加入描述信息
	glBindBuffer(GL_ARRAY_BUFFER, lightPosVbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);


	//5.2 加入ebo 到vao中
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightEbo);

	glBindVertexArray(0);
}

void prepareDeskVao() {

	//2 创建vbo
	glGenBuffers(1, &deskPosVbo);
	glBindBuffer(GL_ARRAY_BUFFER, deskPosVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	

	//glGenBuffers(1, &deskColorVbo);
	//glBindBuffer(GL_ARRAY_BUFFER, deskColorVbo);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);


	glGenBuffers(1, &deskUvVbo);
	glBindBuffer(GL_ARRAY_BUFFER, deskUvVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

	//3	创建 ebo
	glGenBuffers(1, &deskEbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, deskEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_indices_data), g_indices_data, GL_STATIC_DRAW);

	glGenBuffers(1, &deskNormalVbo);
	glBindBuffer(GL_ARRAY_BUFFER, deskNormalVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	//4 创建vao
	glGenVertexArrays(1, &deskVao);
	glBindVertexArray(deskVao);

	// 5绑定vbo，ebo 加入描述信息
	glBindBuffer(GL_ARRAY_BUFFER, deskPosVbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	//glBindBuffer(GL_ARRAY_BUFFER, deskColorVbo);
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

	
	glBindBuffer(GL_ARRAY_BUFFER, deskUvVbo);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	
	glBindBuffer(GL_ARRAY_BUFFER, deskNormalVbo);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));


	//5.2 加入ebo 到vao中
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, deskEbo);

	glBindVertexArray(0);
}

void prepareCandleVao() {

	//2 创建vbo
	glGenBuffers(1, &candlePosVbo);
	glBindBuffer(GL_ARRAY_BUFFER, candlePosVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	/*glGenBuffers(1, &candleColorVbo);
	glBindBuffer(GL_ARRAY_BUFFER, candleColorVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);*/


	glGenBuffers(1, &candleUvVbo);
	glBindBuffer(GL_ARRAY_BUFFER, candleUvVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &candleNormalVbo);
	glBindBuffer(GL_ARRAY_BUFFER, candleNormalVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	//3	创建 ebo
	glGenBuffers(1, &candleEbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, candleEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_indices_data), g_indices_data, GL_STATIC_DRAW);

	//4 创建vao
	glGenVertexArrays(1, &candleVao);
	glBindVertexArray(candleVao);

	// 5绑定vbo，ebo 加入描述信息
	glBindBuffer(GL_ARRAY_BUFFER, candlePosVbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	//glBindBuffer(GL_ARRAY_BUFFER, candleColorVbo);
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);


	glBindBuffer(GL_ARRAY_BUFFER, candleUvVbo);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, candleNormalVbo);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));



	//5.2 加入ebo 到vao中
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, candleEbo);
	
	//解绑
	glBindVertexArray(0);
}

//创建纹理对象
void prepareDeskTexture() {

	

	//textureDesk = new Texture("goku.jpg", 0);
	textureDesk = new Texture("desk.png", 0);

	printf("prepare texture complete\n");

}

void prepareCandleTexture() {

	textureCandle = new Texture("candle.png", 1);
}

void prepareLightTexture() {
	textureLight = new Texture("light.jpg", 2);
}

//相机相关：
void prepareCamera() {

	//viewMat = glm::lookAt(glm::vec3(100.0f,100.0f,100.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f));

	cam.setCamera(glm::vec3(00.0f, 00.0f, 100.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	//cam.viewMat = glm::lookAt(glm::vec3(100.0f, 100.0f, 100.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	
}

void setObjects() {

	transformDesk = glm::translate(transformDesk, cubePositions[0]);
	transformCandle = glm::translate(transformCandle, cubePositions[1]);
	transformLight = glm::translate(transformLight, cubePositions[2]);
	transformCube1 = glm::translate(transformCube1, cubePositions[3]);
	transformCube2 = glm::translate(transformCube2, cubePositions[4]);
	transformCube3 = glm::translate(transformCube3, cubePositions[5]);
	transformCube4 = glm::translate(transformCube4, cubePositions[6]);


	transformDesk = glm::scale(transformDesk, cubeScaling[0]);
	transformCandle = glm::scale(transformCandle, cubeScaling[1]);
	transformLight = glm::scale(transformLight, cubeScaling[2]);
	transformCube1 = glm::scale(transformCube1, cubeScaling[3]);
	transformCube2 = glm::scale(transformCube2, cubeScaling[3]);
	transformCube3 = glm::scale(transformCube3, cubeScaling[3]);
	transformCube4 = glm::scale(transformCube4, cubeScaling[3]);
}


//鼠标。键盘控制相关：

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
		//左键调整yaw pitch
	}

}

void myMotion(int x, int y)
{
	static int posX = 0, posY = 0;
	//如果x++，pitch++
	//if  x-- pitch --
	//if y ++ yaw ++
	//if y -- yaw --
	if (lastMousePoint.x < x) {
		printf("pitch +\n");
		cam.rotateYaw(-0.30f);
	
	}else if(lastMousePoint.x > x) {
		printf("pitch -\n");
		cam.rotateYaw(0.30f);

	}
	else if (lastMousePoint.y < y) {
		printf("yaw+\n");
		cam.rotatePitch(-0.30f);
	}
	else if (lastMousePoint.y > y) {
		printf("yaw -\n");
		cam.rotatePitch(0.30f);
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


//初始化
int readCode(char* fileName, char** shaderCode, int* codeLength)
{
	int length = 0;
	FILE* fp = NULL;
	int rc = 0;
	// check for error in file name
	fp = fopen(fileName, "r");	// open file and check for errors
	if (fp == NULL) {
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
		*shaderCode = (char*)malloc(length + 1);	// add a space for the '\0'
		if (*shaderCode == NULL) return(-2);
		memset((void*)*shaderCode, 0, length + 1);
		fread((void*)*shaderCode, sizeof(char), length, fp);
		(*shaderCode)[length] = 0;
	}

	if (codeLength != NULL) *codeLength = length;

err:
	if (fp != NULL) fclose(fp);

	return(rc);
}

void render() {
	//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// use the shader
	glUseProgram(triShader.getProgId());

	triShader.setInt("sampler", 0);//前往0号纹理单元读取数据
	triShader.setMatrix4("view", cam.getViewMatrix());
	triShader.setMatrix4("projection", cam.getProjMatrix());
	triShader.setMatrix4("transform", transformDesk);
	triShader.setVector3("lightPos", lightPos);
	triShader.setVector3("lightColor", lightColor);
	triShader.setVector3("viewPos", cam.getViewPos());


	glBindVertexArray(deskVao);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);



	triShader.setMatrix4("transform", transformCube1);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	triShader.setMatrix4("transform", transformCube2);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	triShader.setMatrix4("transform", transformCube3);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	triShader.setMatrix4("transform", transformCube4);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//解绑
	glBindVertexArray(0);



	//candle shader 

	glUseProgram(candleShader.getProgId());

	candleShader.setInt("sampler", 1);//前往0号纹理单元读取数据

	candleShader.setMatrix4("view", cam.getViewMatrix());
	candleShader.setMatrix4("projection", cam.getProjMatrix());
	candleShader.setMatrix4("transform", transformCandle);
	candleShader.setVector3("lightPos", lightPos);
	candleShader.setVector3("lightColor", lightColor);
	candleShader.setVector3("viewPos", cam.getViewPos());


	glBindVertexArray(candleVao);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);


	//light shader

	glUseProgram(lightShader.getProgId());

	lightShader.setMatrix4("view", cam.getViewMatrix());
	lightShader.setMatrix4("projection", cam.getProjMatrix());
	lightShader.setMatrix4("transform", transformLight);
	lightShader.setVector3("lightColor", lightColor);

	glBindVertexArray(lightVao);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);


	//particle

	glUseProgram(particleShader.getProgId());
	//particleShader;
	e1->render();
	//Particle p1;

	glutSwapBuffers();
	
}

void doTransform() {
	time_t currenttime = time(NULL);
	//transform = glm::rotate(transform, angle, glm::vec3(0.0, 0.0, 1.0));//绕z轴旋转
	//transformDesk = glm::rotate(transformDesk, angle, glm::vec3(1.0, 0.0, 0.0));//绕x轴旋转
	//transformDesk = glm::rotate(transformDesk, angle, glm::vec3(0.0, 1.0, 0.0));//绕y轴旋转
	if (lightSwitch == true) {
		if (marker == true) {
			lightColor.r -= 0.01f;
			lightColor.g -= 0.01f;
			lightColor.b -= 0.01f;
			if (lightColor.r <= 0.4f) {
				marker = false;
			}
			printf("current color float: %f\n", lightColor.r);

		}
		else if (marker == false) {
			lightColor.r += 0.01f;
			lightColor.g += 0.01f;
			lightColor.b += 0.01f;
			if (lightColor.r >= 0.99f) {
				marker = true;
			}
			printf("current color float: %f\n", lightColor.r);
		}
	}
	else {
		lightColor = glm::vec3(1.0f,1.0f,1.0f);
	
	}
}

void update(int value) {
	angle = 0.01f; // 增加旋转角度
	doTransform();
	e1->update();

	//candleShader.setVector3("viewPos", cam.getViewPos());
	//triShader.setVector3("viewPos", cam.getViewPos());
	glutTimerFunc(25, update, 0);
	glutPostRedisplay(); // 标记窗口需要重新绘制
}

void mainMenuCB(int id)
{
	switch (id) {
	case MAIN_MENU_WIRE:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glutPostRedisplay();
		break;

	case MAIN_MENU_FILL:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glutPostRedisplay();
		break;

	case MAIN_MENU_LUMIOSITY:
		lightSwitch = false;
		glutPostRedisplay();
		break;

	case MAIN_MENU_LUMIOSITYFALSE:
		lightSwitch = true;
		glutPostRedisplay();
		break;


	case MAIN_MENU_MOVEUP:
		transformCandle = glm::translate(transformCandle, glm::vec3(0.0f, 1.0f, 0.0f));
		transformLight = glm::translate(transformLight, glm::vec3(0.0f, 1.0f*20.0f, 0.0f));
		lightPos = lightPos + glm::vec3(0.0f, 20.0f, 0.0f);
		glutPostRedisplay();
		break;

	case MAIN_MENU_MOVEDOWN:
		transformCandle = glm::translate(transformCandle, glm::vec3(0.0f, -1.0f, 0.0f));
		transformLight = glm::translate(transformLight, glm::vec3(0.0f, -1.0f * 20.0f, 0.0f));
		lightPos = lightPos + glm::vec3(0.0f, -20.0f, 0.0f);
		glutPostRedisplay();
		break;




	case MAIN_MENU_MOVERIGHT:
		transformCandle = glm::translate(transformCandle, glm::vec3(1.0f, 0.0f, 0.0f));
		transformLight = glm::translate(transformLight, glm::vec3(1.0f*6.0f, 0.0f, 0.0f));
		lightPos = lightPos + glm::vec3(1.0f * 6.0f, 0.0f, 0.0f);
		glutPostRedisplay();
		break;


	case MAIN_MENU_MOVELEFT:
		transformCandle = glm::translate(transformCandle, glm::vec3(-1.0f, 0.0f, 0.0f));
		transformLight = glm::translate(transformLight, glm::vec3(-1.0f * 6.0f, 0.0f, 0.0f));
		lightPos = lightPos + glm::vec3(-1.0f * 6.0f, 0.0f, 0.0f);
		glutPostRedisplay();
		break;
	case MAIN_MENU_QUIT:
		exit(0);
		break;

	default:
		printf("menu items undefined!! id = %d \n", id);
		break;
	}
}

void subMenuCB(int id)
{

	switch (id) {
	case SUB_MENU_RED_BG:

		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glutPostRedisplay();
		break;

	case SUB_MENU_WHITE_BG:
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glutPostRedisplay();
		break;

	case SUB_MENU_GREY_BG:
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glutPostRedisplay();
		break;

	default:
		printf("menu items undefined!! id = %d \n", id);
		break;
	}
}

void createMenu()
{

	int optionSubmenu = glutCreateMenu(subMenuCB);
	glutAddMenuEntry("Red", SUB_MENU_RED_BG);
	glutAddMenuEntry("White", SUB_MENU_WHITE_BG);
	glutAddMenuEntry("Grey", SUB_MENU_GREY_BG);




	int menu = glutCreateMenu(mainMenuCB);
	glutAddMenuEntry("enable wireframe", MAIN_MENU_WIRE);
	glutAddMenuEntry("disable wireframe", MAIN_MENU_FILL);
	glutAddMenuEntry("Change lumiosity to 1.0", MAIN_MENU_LUMIOSITY);
	glutAddMenuEntry("Change lumiosity via time", MAIN_MENU_LUMIOSITYFALSE);
	glutAddMenuEntry("move candle along x with +1", MAIN_MENU_MOVERIGHT);
	glutAddMenuEntry("move candle along x with -1", MAIN_MENU_MOVELEFT);
	glutAddMenuEntry("move candle along y with +1", MAIN_MENU_MOVEUP);
	glutAddMenuEntry("move candle along Y with -1", MAIN_MENU_MOVEDOWN);

	glutAddSubMenu("Set BG colour ", optionSubmenu);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
	glutAddMenuEntry("Exit", MAIN_MENU_QUIT);

}

int initOpenGL()
{
	int rc = 0;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(50, 50);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glutCreateWindow("Sence Generation");
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glutDisplayFunc(render);

	glutMouseFunc(mymouse);
	glutMotionFunc(myMotion);
	glutMouseWheelFunc(mywheel);

	glutTimerFunc(25, update, 0);

	glEnable(GL_DEPTH_TEST);
	//for particle
	glEnable(GL_POINTS);
	//glEnable(GL_PROGRAM_POINT_SIZE);
	glPointSize(50);

	// Must be done after glut is initialized!
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		printf("Error - %s \n", glewGetErrorString(res));
		return (-1);
	}
	const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	if (glslVersion) {
		printf("GLSL Version: %s\n", glslVersion);
	}
	else {
		printf("Failed to retrieve GLSL version information");
	}

	return(rc);
}


int main(int argc, char** argv)
{
	srand(time(nullptr));
	int rc = 0;
    glutInit(&argc, argv);


	//initialize
	initOpenGL();

	//creating Objects
	prepareDeskVao();
	prepareCandleVao();
	prepareLightVao();

	//set object positions
	setObjects();

	//prepare shader + textures
	prepareDeskTexture();
	prepareCandleTexture();

	//prepare camera attrib
	prepareCamera();


	//create shader obj
	rc = triShader.createShaderProgram("tri.vs","tri.fs");
	if (rc != 0) {
		printf("Error in create Shader \n");
		printf("Hit <cr> to terminate program \n");
		return(1);
	}
	rc = candleShader.createShaderProgram("tri.vs", "tri.fs");
	if (rc != 0) {
		printf("Error in create Shader \n");
		printf("Hit <cr> to terminate program \n");
		return(1);
	}
	rc = lightShader.createShaderProgram("light.vs", "light.fs");
	if (rc != 0) {
		printf("Error in create Shader \n");
		printf("Hit <cr> to terminate program \n");
		return(1);
	}
	rc = particleShader.createShaderProgram("particle.vs", "particle.fs");
	if (rc != 0) {
		printf("Error in create particle Shader \n");
		printf("Hit <cr> to terminate program \n");
		return(1);
	}

	//particle + emitter

	e1 = new Emitter(glm::vec3(0.0f, 26.0f, 0.0f));
	e1->createParticles(50);

	createMenu();
    glutMainLoop();

    return 0;
}