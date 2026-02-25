#include "Sphere.h"
#include "vec3/vec3.h"
#include <math.h>
#include <algorithm>
#include <vector>


  vec3 Sphere::ray_color(const ray &r, std::vector<point3> lights)
{
    vec3 lightPos = point3(-25, 10, 0);
    float t;

    if (shader == "normal") {
    
      
      if (objectColor != vec3{ 0, 0, 0 }) {
        if (hit(r, 0.001, INFINITY, t)) {
          vec3 hitPoint = r.at(t);

          vec3 N = unit_vector(hitPoint - center);
          return 0.5 * vec3(N.x() + 1, N.y() + 1, N.z() + 1);
        }

        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * vec3(1.0, 1.0, 1.0) + a * vec3(0.5, 0.7, 1.0);
      }
    }
    else if (shader == "lambertian") {
      vec3 color = vec3(0, 0, 0);

        if (objectColor != vec3{0,0,0}) {
            if (hit(r, 0.001, INFINITY, t)) {
                vec3 hitPoint = r.at(t);
                
                vec3 N = unit_vector(hitPoint - center);
                for (int i = 0; i < lights.size(); i++) {
                  vec3 toLight = unit_vector(lights[i] - hitPoint);  
                  float returnVector = (std::max(0.0, dot(N, toLight)));
                  color = vec3{ color.x() + returnVector, color.y() + returnVector, color.z() + returnVector };
                }
              return clampToOne( color*unit_vector(objectColor));
            }

              vec3 unit_direction = unit_vector(r.direction());
              auto a = 0.5 * (unit_direction.y() + 1.0);
              return (1.0 - a) * vec3(1.0, 1.0, 1.0) + a * vec3(0.5, 0.7, 1.0);
          } //shader if color
    } 
    else if (shader == "Blinn-Phong") {
        if (hit(r, 0.001, INFINITY, t)) {
        float kd = 1.0f;
        float ks = 0.6f;
        float p = 32.0f;


          vec3 hitPoint = r.at(t);

          vec3 toLight = unit_vector(lightPos - hitPoint);
          vec3 N = unit_vector(hitPoint - center);
          vec3 V = unit_vector(-r.direction());
          vec3 H = unit_vector(toLight + V);

          //Diffuse
          float diff = std::max(dot(N, toLight), 0.0);
          vec3 diffuse = kd * diff * objectColor;

          //specular
          float spec = std::pow(std::max(0.0, dot(N, H)), p);
          vec3 specular = ks * spec * vec3(1,1,1);

          float colorSpec = spec * diff;

          vec3 returnVector = clampToOne( diffuse + specular);
          return returnVector;
        }

        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * vec3(1.0, 1.0, 1.0) + a * vec3(0.5, 0.7, 1.0);
    } else if (shader == "mirror") {
        
    }
}