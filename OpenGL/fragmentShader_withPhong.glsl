#version 330 core

layout(location=0) out vec4 fragmentColor;

uniform vec3 diffuseComponent;
uniform vec3 specularComponent;
uniform float phongExp;

in vec4 normal;
in vec4 lightDir;
in vec4 viewDir;

void main(void)
{
  vec4 n = normalize(normal);
  vec4 l = normalize(lightDir);
  vec4 v = normalize(viewDir);
  
  vec4 halfVector = normalize(v + l);
  
  float val = max(0.0, dot(n, l));
  vec3 diffuse = vec3( diffuseComponent.r * val, diffuseComponent.g * val, diffuseComponent.b * val );

  vec3 specular = specularComponent * pow(max(0.0, dot(n, halfVector)), phongExp);

  vec3 finalColor = diffuse + specular;
  fragmentColor = vec4(finalColor, 1.0);
}