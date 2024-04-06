#version 330 core
in vec4 color;
in vec2 uv;
out vec4 FragColor;

uniform sampler2D sampler;

void main()
{
    //tempFragColor = vec4(color);
    FragColor = texture(sampler, uv);
} 