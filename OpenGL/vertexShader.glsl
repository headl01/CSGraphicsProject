#version 330 core 

layout (location = 0) in vec3 in_Position; 
layout (location = 1) in vec3 in_color; 

out vec3 vColor; 

void main(void) 
{ 
	gl_Position = vec4(in_Position, 1.0); 
	vColor = in_color;
}