
/*************************************************************************************/

// INCLUDE FILES


#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "GL/nuss_math.h"
#include "shader.h"
//********这个宏不能省略****************
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"



/*************************************************************************************/

// DATA STRUCTURES

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



void renderCB()
{
	// clear the back buffer
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

	// use the shader
	//glUseProgram(shaderProgId);
	glUseProgram(triShader.getProgId());

	glBindVertexArray(vao);
	// draw the triangle
	//glColor3f(1.0,1.0,1.0);
	/*glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(myVertex), 0);
	*/
    

	glDrawArrays(GL_TRIANGLES, 0, 3);
    
    //glDisableVertexAttribArray(0);

    glutSwapBuffers();
}


int initGeom() 
{
	tri[0].v.x = -1.0;  tri[0].v.y = -1.0;  tri[0].v.z = 0.0; 
	tri[1].v.x = 0.0;  tri[1].v.y = 1.0;  tri[1].v.z = 0.0; 
	tri[2].v.x = 1.0;  tri[2].v.y = -1.0;  tri[2].v.z = 0.0;


	float vertices[] = {
		0.5f, 0.5f, 0.0f,   // 右上角
		0.5f, -0.5f, 0.0f,  // 右下角
		-0.5f, -0.5f, 0.0f, // 左下角
		-0.5f, 0.5f, 0.0f   // 左上角
	};
	unsigned int indices[] = {
		// 注意索引从0开始! 
		// 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
		// 这样可以由下标代表顶点组合成矩形

		0, 1, 3, // 第一个三角形
		1, 2, 3  // 第二个三角形
	};

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);


	/*
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
 	*/
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tri), tri, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	

	return(0);
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
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// use the shader
	//glUseProgram(shaderProgId);
	glUseProgram(triShader.getProgId());

	triShader.setInt("sampler",0);//前往0号纹理单元读取数据
	//triShader.setInt("sampler", 1);//前往1号纹理单元读取数据，由于1号纹理单元没有挂载对象，渲染为黑色


	glBindVertexArray(vao);
	// draw the triangle
	//glColor3f(1.0,1.0,1.0);
	/*glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(myVertex), 0);
	*/

	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
	//	glDrawArrays(GL_TRIANGLES, 0, 6);

	//glDisableVertexAttribArray(0);

	glutSwapBuffers();

}


int initOpenGL()
{
	int rc = 0;
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Draw Triangle");

	glutDisplayFunc(renderCB);
 
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
	float positions[] = {
		-0.5f, -0.5f, 0.0f, // 左下角
		0.5f, -0.5f, 0.0f,  // 右下角
		-0.5f, 0.5f, 0.0f,  // 右下角
		0.5f, 0.5f, 0.0f,   // 右上角
	};

	float colors[] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f
	};

	float uvs[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f
	};


	unsigned int indices[] = {
		0, 1, 2, // 第一个三角形
		2, 1, 3  // 第二个三角形
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
	//1. stbimage 读取图片
	int width, height, channels;
	GLuint texture;

	//反转y轴
	stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load("desk.png", &width, &height, &channels, STBI_rgb_alpha);

	//2. 生成纹理，激活单元 绑定

	glGenTextures(1, &texture);

	//激活

	glActiveTexture(GL_TEXTURE0);

	//绑定

	glBindTexture(GL_TEXTURE_2D, texture);

	//3. 传输纹理数据, 开辟显存

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	//4. ***释放数据***
	stbi_image_free(data);


	//5. 设置纹理的过滤方式
	//放大图片
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//缩小图片
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//6. 设置纹理的包裹方式

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//s是横向方向，u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//t是纵向方向，t


	//7. 绑定采样器到纹理单元


	printf("prepare texture complete\n");

}




int main(int argc, char** argv)
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	int rc = 0;
    glutInit(&argc, argv);
 
	initOpenGL();
    //initGeom();
	prepareVao();
	prepareTexture();
	
	//Shader triShader;
	
	//triShader.printShaderStatus();
	
	rc = triShader.createShaderProgram("tri.vs","tri.fs");
	//rc = prepareBuffer();
	if (rc != 0) {
		printf("Error in create Shader \n");
		printf("Hit <cr> to terminate program \n");
		getchar();
		return(1);
	}
		
	//glBindVertexArray(vao);
	
	//rc = createShaders("tri.vs","tri.fs", &shaderProgId);
	//if (rc != 0) {
	//	printf("Error in create Shader \n");
	//	printf("Hit <cr> to terminate program \n");
	//	getchar();
	//	return(1);
	//}
	glBindVertexArray(vao);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glutDisplayFunc(render);
    glutMainLoop();

    return 0;
}




