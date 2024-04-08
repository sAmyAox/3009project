#pragma once

#ifndef SHADER_HEADER
#define SHADER_HEADER
#include "includPath.h"


class Shader
{
public:
	Shader(void);
	~Shader(void);

	// creates a shader program from files vsFileName and fsFileName
	int createShaderProgram(char* vsFileName, char* fsFileName);
	int createFromFiles(char** vert, char** frag);

	GLuint	getProgId() const { return shaderProgramid; }

	int printShaderStatus(void);
	void useProgram(int useProg);
	//int copyMatrixToShader(const Matrix4f matrix, const char* name);
	//int copyFloatVectorToShader(float* v, int vectorSize, int elementSize, const char* name);
	//int copyIntVectorToShader(int* v, int vectorSize, int elementSize, const char* name);

	void setInt(const std::string& name, int value);
	void setVector3(const std::string& name, float* values);
	void setMatrix4(const std::string& name, glm::mat4 matrix);


private:
	GLuint vertShaderid;
	GLuint fragShaderid;
	GLuint shaderProgramid;

	char* readCode(char* fileName);
	int createShaderObj(char* fileName, int shaderType, GLuint* shaderid);
	// functions creates a shader program.  The two shader programs (vertex and fragment) were already compiled.
	GLint ceateShaderProgram(GLint vertShaderid, GLint fragShaderid, GLuint* shaderProgId);
	int createShaderProgram(char* vsFileName, char* fsFileName, GLuint* shaderProgramid);
	int	filesExist(char** fileNames);



};


#endif