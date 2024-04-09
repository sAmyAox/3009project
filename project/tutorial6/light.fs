#version 330 core
out vec4 FragColor;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragColor = vec4(1.0); // 将向量的四个分量全部设置为1.0
}