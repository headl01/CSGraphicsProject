#version 330 core

layout(location=0) out vec4 fragmentColor;

in vec3 color;
out vec4 fragmentColor;

void main(void)
{
  fragmentColor = vec4(color, 1.0);
}s