#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 normal;


uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightColor;

void main()
{
	gl_Position = projection * view * transform * vec4(aPos, 1.0);

}