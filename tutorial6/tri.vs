#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUv;
layout (location = 2) in vec3 aNormal;


out vec2 uv;
out vec3 normal;
out vec3 fragPos;
out vec4 FragPosLightSpace;



uniform vec3 viewPos;
uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform mat4 lightSpaceMatrix;



void main()
{
    vec4 position = vec4(aPos, 1.0);
    position =  projection * view  * transform * position;
    gl_Position = position;
    uv = aUv;
    normal = mat3(transpose(inverse(transform)))*aNormal;
    FragPosLightSpace = lightSpaceMatrix * vec4(fragPos, 1.0);
    fragPos = vec3(transform * vec4(aPos,1.0));

}