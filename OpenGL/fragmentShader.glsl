#version 330 core

in vec3 vColor; 

out vec4 fragmentColor;

void main(void)
{
    fragmentColor = vec4(vColor, 1.0);
}