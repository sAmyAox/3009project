
#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "GL/nuss_math.h"
#include "GL/nuss_matrix.h"
#include "shader.h"

#include "texture.h"
#include "graphicsObject.h"
//使用glm库，重新编写
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


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

//Matrix4f transform = Matrix4f::identity();
Matrix4f modelMat = Matrix4f::identity(); // = Matrix4f::rotateRollPitchYaw(rollAngle, pitchAngle, yawAngle, 1);
Matrix4f scaleMat = Matrix4f::identity();//scale(0.5f,0.5f,0.5f);//scale(scale.x, scale.y, scale.z);
Matrix4f rotMat = Matrix4f::identity();//rotateX(45.0f,1);//rotateRollPitchYaw(rollAngle, pitchAngle, yawAngle, 1);

//观察矩阵（摄像机位置）
Matrix4f viewMat = Matrix4f::translation(0.0f, 0.0f, -3.0f);

//投影矩阵
Matrix4f projMat = Matrix4f::identity();//symmetricPerspectiveProjectionMatrix(45.0f, 0.75f, 0.1f, 100.0f);



Matrix4f final = projMat * viewMat * rotMat * modelMat;

//Matrix4f modelViewProjMat = Matrix4f::translation(0.0f,0.0f,-3.0f); //cam.getProjectionMatrix(NULL) * modelViewMat;




void doTransform() {
	modelMat = rotMat* scaleMat * modelMat;
	
}



int prepareBuffer() {
	float vertices[] = {
	-0.5f,-0.5f,0.0f,	1.0f,0.0f,0.0f,
	0.5f,-0.5f,0.0f,	0.0f,1.0f,0.0f,
	0.0f,0.5f,0.0f,		0.0f,0.0f,1.0f 
	};
	//创建vbo
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//创建vao

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);//激活
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

	//2 使用数据生成position vbo
	GLuint posVbo;
	glGenBuffers(1, &posVbo);
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	//3 generate vao and bind

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//4描述位置属性
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindVertexArray(0);

	


}


void render() {
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// use the shader
	glUseProgram(triShader.getProgId());

	triShader.setInt("sampler",0);//前往0号纹理单元读取数据
	//triShader.setInt("sampler", 1);//前往1号纹理单元读取数据，由于1号纹理单元没有挂载对象，渲染为黑色
	triShader.setMatrix4("model", modelMat);
	triShader.setMatrix4("view", viewMat);
	triShader.setMatrix4("projection", projMat);
	//triShader.setMatrix4("transform",model);
	//int rc = triShader.copyMatrixToShader(model,"transform");
	//printf("rc = %d\n",rc);

	glBindVertexArray(vao);

	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

	glutSwapBuffers();

}


int initOpenGL()
{
	int rc = 0;
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
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
	//float positions[] = {
	//	-0.5f, -0.5f, 0.0f, // 左下角
	//	0.5f, -0.5f, 0.0f,  // 右下角
	//	0.0f, 0.5f, 0.0f,  // 右下角
	//	//0.0f, 0.5f, 0.0f,   // 中间角
	//};

	float positions[] = {
	-1.0f, 0.0f, 0.0f, // 左下角
	1.0f, 0.0f, 0.0f,  // 右下角
	0.0f, 1.0f, 0.0f,  // 右下角
	0.0f, -1.0f, 0.0f,   // 中间角
	};

	float colors[] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		//0.5f, 0.5f, 0.5f, 1.0f
	};

	float uvs[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.5f, 1.0f,
		0.5f, -1.0f
	};


	unsigned int indices[] = {
		0, 1, 2, // 第一个三角形
		0, 1, 3  // 第二个三角形
	};

	GLuint colorVbo, posVbo, uvVbo;
	//2 创建vbo
	glGenBuffers(1, &posVbo);
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	glGenBuffers(1, &colorVbo);
	glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	glGenBuffers(1, &uvVbo);
	glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

	//3	创建 ebo
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//4 创建vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	// 5绑定vbo，ebo 加入描述信息
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);


	glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);


	//5.2 加入ebo 到vao中
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer();
	glBindVertexArray(0);
}

//创建纹理对象
void prepareTexture() {

	////1. stbimage 读取图片
	//int width, height, channels;
	//GLuint texture;

	////反转y轴
	//stbi_set_flip_vertically_on_load(true);

	//unsigned char* data = stbi_load("desk.png", &width, &height, &channels, STBI_rgb_alpha);

	////2. 生成纹理，激活单元 绑定

	//glGenTextures(1, &texture);

	////激活

	//glActiveTexture(GL_TEXTURE0);

	////绑定

	//glBindTexture(GL_TEXTURE_2D, texture);

	////3. 传输纹理数据, 开辟显存

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	////4. ***释放数据***
	//stbi_image_free(data);


	////5. 设置纹理的过滤方式
	////放大图片
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	////缩小图片
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	////6. 设置纹理的包裹方式

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//s是横向方向，u
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//t是纵向方向，t


	////7. 绑定采样器到纹理单元

	texture = new Texture("goku.jpg", 0);

	printf("prepare texture complete\n");

}


//相机相关：
void prepareCamera() {

	viewMat = Matrix4f::cameraMatrix(Vector3f(0.0f,0.0f,10.0f),Vector3f(0.0f,0.0f,0.0f),Vector3f(0.0f,1.0f,0.0f));
	
}

void prepareProjection() {
	projMat = Matrix4f::symmetricPerspectiveProjectionMatrix(60.0f,1.0f,0.1f,1000.0f);
	projMat = Matrix4f::identity();
	projMat = glm::perspective(glm::radians(60.0f),0.75f,0.1f,1000.0f);
}

int getWinHeight(){
	return 600;
}
int getWinWidth() {
	return 800;
}

int main(int argc, char** argv)
{
	int rc = 0;
    glutInit(&argc, argv);


	
	initOpenGL();
	doTransform();
    //initGeom();
	prepareVao();
	prepareTexture();
	prepareCamera();
	prepareProjection();

	
	rc = triShader.createShaderProgram("tri.vs","tri.fs");
	if (rc != 0) {
		printf("Error in create Shader \n");
		printf("Hit <cr> to terminate program \n");
		getchar();
		return(1);
	}

	glBindVertexArray(vao);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glutDisplayFunc(render);
    glutMainLoop();

    return 0;
}




