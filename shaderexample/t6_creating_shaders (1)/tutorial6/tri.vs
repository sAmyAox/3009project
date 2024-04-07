#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aUv;

out vec4 color;
out vec2 uv;

// mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec4 position = vec4(aPos, 1.0);
    position =  projection * view  * model * position;

    //gl_Position = projection * view * model * vec4(aPos,1.0);
    gl_Position = position;
    color = aColor;
    uv = aUv;
}