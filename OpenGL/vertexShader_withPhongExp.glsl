#version 330 core

layout(location=0) in vec3 in_Position;
layout(location=1) in vec3 in_Normal;

uniform mat4 projMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 normalMatrix;

uniform vec4 light;
uniform vec3 cameraPosWorld;

out vec4 normal;
out vec4 lightDir;
out vec4 viewDir;

void main(void)
{
  vec4 vcamPos = vec4(cameraPosWorld, 1.0);
  vec4 vertexWorldPos = modelMatrix * vec4(in_Position, 1.0);
  
  normal = normalize(normalMatrix * vec4(in_Normal, 0.0));
  lightDir = normalize(light - vertexWorldPos);
  viewDir = normalize(vcamPos - vertexWorldPos);
  
  gl_Position = projMatrix * viewMatrix * vertexWorldPos;
}







