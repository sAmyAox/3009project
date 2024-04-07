
#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
//#include "GL/nuss_math.h"
//#include "GL/nuss_matrix.h"
#include "shader.h"
#include "texture.h"
#include "graphicsObject.h"
#include <time.h>
//#include "table.h"
//ʹ��glm�⣬���±�д



//globals

struct point3D {
	float x; 
	float y; 
	float z;
};

struct myVertex {
	struct point3D v;  // the vertex geomtry
} ;

struct myVertex tri[3];

GLuint vbo;
GLuint vao;
GLuint ebo;
GLuint shaderProgId;
Shader triShader;
Texture* texture = nullptr;

float angle = 0.0f;
glm::mat4 transform(1.0f);

glm::mat4 viewMat(1.0f);
glm::mat4 projMat(1.0f);

////Matrix4f transform = Matrix4f::identity();
//Matrix4f modelMat = Matrix4f::identity(); // = Matrix4f::rotateRollPitchYaw(rollAngle, pitchAngle, yawAngle, 1);
//Matrix4f scaleMat = Matrix4f::identity();//scale(0.5f,0.5f,0.5f);//scale(scale.x, scale.y, scale.z);
//Matrix4f rotMat = Matrix4f::identity();//rotateX(45.0f,1);//rotateRollPitchYaw(rollAngle, pitchAngle, yawAngle, 1);
//
//
//glm::
//
//
//
////�۲���������λ�ã�
//Matrix4f viewMat = Matrix4f::translation(0.0f, 0.0f, -3.0f);
//
////ͶӰ����
//Matrix4f projMat = Matrix4f::identity();//symmetricPerspectiveProjectionMatrix(45.0f, 0.75f, 0.1f, 100.0f);
//
//
//
//Matrix4f final = projMat * viewMat * rotMat * modelMat;
//
////Matrix4f modelViewProjMat = Matrix4f::translation(0.0f,0.0f,-3.0f); //cam.getProjectionMatrix(NULL) * modelViewMat;




void doTransform() {
	time_t currenttime = time(NULL);


	//modelMat = rotMat* scaleMat * modelMat;
	
	//transform = glm::rotate(transform, angle, glm::vec3(0.0, 0.0, 1.0));//��z����ת
	//transform = glm::rotate(transform, angle, glm::vec3(1.0, 0.0, 0.0));//��x����ת
	transform = glm::rotate(transform, angle, glm::vec3(0.0, 1.0, 0.0));//��y����ת
	//transform = glm::scale(transform, glm::vec3(1.0f,0.5f,1.0f));


	//transform = glm::rotate(transform, (float)currenttime * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
	//transform = glm::rotate(transform,);
}



int prepareBuffer() {
	float vertices[] = {
	-0.5f,-0.5f,0.0f,	1.0f,0.0f,0.0f,
	0.5f,-0.5f,0.0f,	0.0f,1.0f,0.0f,
	0.0f,0.5f,0.0f,		0.0f,0.0f,1.0f 
	};
	//����vbo
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//����vao

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);//����
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));

	return 0;
}


void prepareVAOForGLTriangles() {
	float positions[] = {
	-0.5f,-0.5f,0.0f,
	0.5f,-0.5f,0.0f,
	0.0f, 0.5f, 0.0f,
	0.5f, 0.5f, 0.0f,
	0.8f,0.8f,0.0f,
	0.8f,0.0f,0.0f
	};

	//2 ʹ����������position vbo
	GLuint posVbo;
	glGenBuffers(1, &posVbo);
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	//3 generate vao and bind

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//4����λ������
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindVertexArray(0);

	


}


void render() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// use the shader
	glUseProgram(triShader.getProgId());

	triShader.setInt("sampler",0);//ǰ��0������Ԫ��ȡ����
	//triShader.setInt("sampler", 1);//ǰ��1������Ԫ��ȡ���ݣ�����1������Ԫû�й��ض�����ȾΪ��ɫ
	triShader.setMatrix4("transform", transform);
	triShader.setMatrix4("view", viewMat);
	triShader.setMatrix4("projection", projMat);
	//triShader.setMatrix4("transform",model);
	//int rc = triShader.copyMatrixToShader(model,"transform");
	//printf("rc = %d\n",rc);

	glBindVertexArray(vao);

	glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0);
	//glDrawArrays(GL_TRIANGLES, 0,36);

	glutSwapBuffers();
	printf("swapbuffer called\n");

}


int initOpenGL()
{
	int rc = 0;
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Draw Triangle");

	glutDisplayFunc(render);
 
    // Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK) {
      printf("Error - %s \n", glewGetErrorString(res));
      return (-1);
    }

	return(rc);
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


int createShaders(char *vertexShaderFileName, char *fragmentShaderFileName, GLuint *shaderProgId)
{

	int rc = 0;
	char *shaderCode[1];  
	int codeLength = 0;
	
	GLuint vtxShader = -1;
	GLuint fragShader = -1;
	GLuint shaderId = -1;

	
	*shaderProgId = -1;

	// create a vertex shader
	vtxShader = glCreateShader(GL_VERTEX_SHADER);

	
	shaderCode[0] = NULL;
	


	// read and compile the vertex shader
	rc = readCode(vertexShaderFileName, &shaderCode[0], &codeLength);

	// check for error reading the code
	if (rc != 0) {
		rc = -1; 
		goto err;
	}
	
	// transfer the shader source to OpenGL
	glShaderSource(vtxShader, 1, shaderCode, 0);

	// compile the shader
	glCompileShader(vtxShader);

	// check for errors
	glGetShaderiv(vtxShader, GL_COMPILE_STATUS, &rc);
	if (rc != GL_TRUE) {
		char errorLog[2048];
		glGetShaderInfoLog(vtxShader, sizeof(errorLog) - 1, NULL, errorLog);
		fprintf(stderr, "Error when creating the vertex Shader - % s \n", errorLog);
	}
	else {
		printf("vtx shader success\n");
	}
	// free the allocated shader code


	// create a fragment shader 

	fragShader = glCreateShader(GL_FRAGMENT_SHADER);


	// read the fragment shader code
	rc = readCode(fragmentShaderFileName, &shaderCode[0], &codeLength);


	// check for error reading the code
	if (rc != 0) {
		rc = -1;
		goto err;
	}

	// transfer the shader source to OpenGL
	glShaderSource(fragShader, 1, shaderCode, 0);


	// transfer the shader code to OpenGL
	glCompileShader(fragShader);
	// compile the code
	
	// check for errors
	glGetShaderiv(vtxShader, GL_COMPILE_STATUS, &rc);
	if (rc != GL_TRUE) {
		char errorLog[2048];
		glGetShaderInfoLog(vtxShader, sizeof(errorLog) - 1, NULL, errorLog);
		fprintf(stderr, "Error when creating the fragment Shader - % s \n", errorLog);
	}
	else {
		printf("frag shader success\n");
	}
	// free the shader code


	// create a shader program
	shaderId = glCreateProgram();

	// attach the shaders to the program
	glAttachShader(shaderId, vtxShader);
	glAttachShader(shaderId, fragShader);

	// link the program
	glLinkProgram(shaderId);

	// check for errors
	glGetProgramiv(shaderId, GL_LINK_STATUS, &rc);
	if (!rc) {
		char errorLog[2048];
		glGetProgramInfoLog(shaderId, 512,NULL, errorLog);
		fprintf(stderr, "Error when link the program Shader - % s \n", errorLog);
	}
	else {
		printf("link program success\n");
	}


	// set the output shader program
	*shaderProgId = shaderId;

	//clear shaders
	glDeleteShader(vtxShader);
	glDeleteShader(fragShader);


	rc = 0;
err:
	if (shaderCode[0] != NULL) free(shaderCode[0]);

	// release the vertex shader
	if (vtxShader != -1) {
		glDeleteShader(vtxShader);
		if (shaderId != -1) glDetachShader(shaderId, vtxShader);
	}

	// release the fragment shader
	if (fragShader != -1) {
		glDeleteShader(fragShader);
		if (shaderId != -1) glDetachShader(shaderId, fragShader);
	}
	return(rc);
}


void prepareVao() {
	//����
	float vertices[] = {
	-1.0f,	-1.0f,	 1.0f,
	 1.0f,	-1.0f,	 1.0f,
	 1.0f,	 1.0f,	 1.0f,
	-1.0f,	 1.0f,	 1.0f,
	-1.0f,	-1.0f,	-1.0f,
	 1.0f,	-1.0f,	-1.0f,
	 1.0f,	 1.0f,	-1.0f,
	-1.0f,	 1.0f,	-1.0f
	};
	unsigned int indices[] = {
		// front face
		0, 1, 2,
		2, 3, 0,
		// top face
		3, 2, 6,
		6, 7, 3,
		// back face
		7, 6, 5,
		5, 4, 7,
		// bottom face
		4, 5, 1,
		1, 0, 4,
		// left face
		4, 0, 3,
		3, 7, 4,
		// right face
		1, 5, 6,
		6, 2, 1
	};



	//float positions[] = {
	//-1.0f, 0.0f, 0.0f, // ���½�
	//1.0f, 0.0f, 0.0f,  // ���½�
	//0.0f, 1.0f, 0.0f,  // ���½�
	//0.0f, -1.0f, 0.0f,   // �м��
	//};

	float colors[] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		//0.5f, 0.5f, 0.5f, 1.0f
	};

	float uvs[] = {
		// Front face
	0.0f, 0.0f, // ����0����������
	1.0f, 0.0f, // ����1����������
	1.0f, 1.0f, // ����2����������
	0.0f, 1.0f, // ����3����������

	// Top face
	0.0f, 1.0f, // ����3����������
	1.0f, 1.0f, // ����2����������
	1.0f, 0.0f, // ����6����������
	0.0f, 0.0f, // ����7����������

	// Back face
	0.0f, 0.0f, // ����7����������
	1.0f, 0.0f, // ����6����������
	1.0f, 1.0f, // ����5����������
	0.0f, 1.0f, // ����4����������

	// Bottom face
	0.0f, 0.0f, // ����4����������
	1.0f, 0.0f, // ����5����������
	1.0f, 1.0f, // ����1����������
	0.0f, 1.0f, // ����0����������

	// Left face
	0.0f, 0.0f, // ����4����������
	1.0f, 0.0f, // ����0����������
	1.0f, 1.0f, // ����3����������
	0.0f, 1.0f, // ����7����������

	// Right face
	0.0f, 0.0f, // ����1����������
	1.0f, 0.0f, // ����5����������
	1.0f, 1.0f, // ����6����������
	0.0f, 1.0f  // ����2����������
	};


	//unsigned int indices[] = {
	//	0, 1, 2, // ��һ��������
	//	2, 1, 3  // �ڶ���������
	//};

	GLuint colorVbo, posVbo, uvVbo;
	//2 ����vbo
	glGenBuffers(1, &posVbo);
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &colorVbo);
	glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	glGenBuffers(1, &uvVbo);
	glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

	//3	���� ebo
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//4 ����vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	// 5��vbo��ebo ����������Ϣ
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);


	glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);


	//5.2 ����ebo ��vao��
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer();
	glBindVertexArray(0);
}

//�����������
void prepareTexture() {

	////1. stbimage ��ȡͼƬ
	//int width, height, channels;
	//GLuint texture;

	////��תy��
	//stbi_set_flip_vertically_on_load(true);

	//unsigned char* data = stbi_load("desk.png", &width, &height, &channels, STBI_rgb_alpha);

	////2. �����������Ԫ ��

	//glGenTextures(1, &texture);

	////����

	//glActiveTexture(GL_TEXTURE0);

	////��

	//glBindTexture(GL_TEXTURE_2D, texture);

	////3. ������������, �����Դ�

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	////4. ***�ͷ�����***
	//stbi_image_free(data);


	////5. ��������Ĺ��˷�ʽ
	////�Ŵ�ͼƬ
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	////��СͼƬ
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	////6. ��������İ�����ʽ

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//s�Ǻ�����u
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//t��������t


	////7. �󶨲�����������Ԫ

	texture = new Texture("goku.jpg", 0);
	//texture = new Texture("desk.png", 0);

	printf("prepare texture complete\n");

}


//�����أ�
void prepareCamera() {

	//viewMat = Matrix4f::cameraMatrix(Vector3f(0.0f,0.0f,10.0f),Vector3f(0.0f,0.0f,0.0f),Vector3f(0.0f,1.0f,0.0f));
	viewMat = glm::lookAt(glm::vec3(1.0f,1.0f,5.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f));
	
}

void prepareProjection() {
	projMat = glm::perspective(45.0f,0.75f,0.1f,1000.0f);
}

int getWinHeight(){
	return 600;
}
int getWinWidth() {
	return 800;
}


void prepare3DTriangleVao() {
	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	//unsigned int VBO, VAO;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);


	//glBindVertexArray(0);
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







int main(int argc, char** argv)
{
	int rc = 0;
    glutInit(&argc, argv);


	
	initOpenGL();
    //initGeom();
	prepareVao();
	//prepare3DTriangleVao();
	prepareTexture();
	prepareCamera();
	prepareProjection();
	//transform = glm::scale(glm::mat4(1.0f), glm::vec3(1.2f, 0.3f, 0.6f));
	
	rc = triShader.createShaderProgram("tri.vs","tri.fs");
	if (rc != 0) {
		printf("Error in create Shader \n");
		printf("Hit <cr> to terminate program \n");
		getchar();
		return(1);
	}
	doTransform();

	glBindVertexArray(vao);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(render);
	glutTimerFunc(25, update, 0);
	//glutMouseFunc(mouseCB);
    glutMainLoop();

    return 0;
}


