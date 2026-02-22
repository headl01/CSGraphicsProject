#include "Sphere.h"
#include "vec3/vec3.h"
#include <math.h>
#include <algorithm>


  vec3 Sphere::ray_color(const ray &r)
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
        if (objectColor != vec3{0,0,0}) {
            if (hit(r, 0.001, INFINITY, t)) {
              vec3 hitPoint = r.at(t);

              vec3 toLight = unit_vector(lightPos - hitPoint);
              vec3 N = unit_vector(hitPoint - center);
              float returnVector = (std::max(0.0, dot(N, toLight)));
              
              return vec3{returnVector, returnVector, returnVector}*unit_vector(objectColor);
            }

              vec3 unit_direction = unit_vector(r.direction());
              auto a = 0.5 * (unit_direction.y() + 1.0);
              return (1.0 - a) * vec3(1.0, 1.0, 1.0) + a * vec3(0.5, 0.7, 1.0);
          } //shader if color
    } 
    else if (shader == "Blinn-Phong") {
      if (objectColor != vec3{ 0, 0, 0 }) {
        if (hit(r, 0.001, INFINITY, t)) {
          vec3 hitPoint = r.at(t);

          vec3 toLight = unit_vector(lightPos - hitPoint);
          vec3 N = unit_vector(hitPoint - center);
          vec3 H = unit_vector(N + toLight);
          vec3 returnVector = clampToOne((std::pow(dot(N, H), 100) * objectColor));
          if (returnVector == vec3(0, 0, 0)) {
            return objectColor;
          }
          return returnVector;
        }

        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * vec3(1.0, 1.0, 1.0) + a * vec3(0.5, 0.7, 1.0);
      }
    }
}