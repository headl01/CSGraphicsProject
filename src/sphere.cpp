#include "Sphere.h"
#include "vec3/vec3.h"
#include <math.h>
#include <algorithm>
#include <vector>
    
/*
  vec3 Sphere::ray_color(const ray &r, std::vector<point3> lights, std::vector<Sphere> objectList, int recursions)
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
          vec3 V = unit_vector(r.origin()-hitPoint);
          vec3 H = unit_vector(toLight + V);

          //Diffuse
          float diff = std::max(dot(N, toLight), 0.0);
          vec3 diffuse = kd * diff * objectColor;

          //specular
          float spec = std::pow(std::max(0.0, dot(N, H)), p);
          vec3 specular = ks * spec * vec3(1,1,1);

          float colorSpec = spec * diff;

          vec3 returnVector =clampToOne( clampToOne( diffuse ) + clampToOne(specular));
          return returnVector;
        }

        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * vec3(1.0, 1.0, 1.0) + a * vec3(0.5, 0.7, 1.0);
    } else if (shader == "mirror") {
      if (hit(r, 0.001, INFINITY, t)) {

        vec3 N = unit_vector(r.at(t) - center);

        vec3 D = unit_vector(r.direction());

        vec3 reflection = D - 2 * dot(D, N) * N;

        ray tempRay(r.at(t) + 0.001 * N, reflection);

        return ray_color(tempRay, lights, objectList, recursions--);
      }
    
    }
}
*/

vec3 Sphere::getColor(ray r, std::vector<point3> lights) const
{
  float t;
  HitStruct tempHit;
  float t_max = std::numeric_limits<float>::max();


  if (shader == "normal") {
    if (objectColor != vec3{ 0, 0, 0 }) {
      if (intersect(r, 0.001, t_max, tempHit)) {
        vec3 hitPoint = r.at(tempHit.t);

        vec3 N = unit_vector(hitPoint - center);
        return 0.5 * vec3(N.x() + 1, N.y() + 1, N.z() + 1);
      }
    }
  } else if (shader == "lambertian") {
    vec3 color = vec3(0, 0, 0);

    if (objectColor != vec3{ 0, 0, 0 }) {
      if (intersect(r, 0.001, t_max, tempHit)) {
        vec3 hitPoint = r.at(tempHit.t);

        vec3 N = unit_vector(hitPoint - center);
        for (int i = 0; i < lights.size(); i++) {
          vec3 toLight = unit_vector(lights[i] - hitPoint);
          float returnVector = (std::max(0.0, dot(N, toLight)));
          color = vec3{ color.x() + returnVector, color.y() + returnVector, color.z() + returnVector };
        }
        return clampToOne(color * unit_vector(objectColor));
      }

      vec3 unit_direction = unit_vector(r.direction());
      auto a = 0.5 * (unit_direction.y() + 1.0);
      return (1.0 - a) * vec3(1.0, 1.0, 1.0) + a * vec3(0.5, 0.7, 1.0);
    }// shader if color
  } else if (shader == "Blinn-Phong") {

    if (intersect(r, 0.001, t_max, tempHit)) {
      float kd = 1.0f;
      float ks = 0.6f;
      float p = 32.0f;
      vec3 hitPoint = r.at(tempHit.t);
      vec3 V = unit_vector(-r.direction());

      vec3 N = unit_vector(tempHit.point);
      vec3 diffuse, specular;

      for (int i = 0; i < lights.size(); i++) {
        vec3 toLight = unit_vector(lights[i] - hitPoint);
      
        vec3 H = unit_vector(toLight + V);
        // Diffuse
        float diff = std::max(dot(N, toLight), 0.0);
        diffuse = kd * diff * objectColor;

        // specular
        float spec = std::pow(std::max(0.0, dot(N, H)), p);
        specular = ks * spec * vec3(1, 1, 1);

      }
      

      vec3 returnVector = clampToOne(clampToOne(diffuse) + clampToOne(specular));
      return returnVector;
    }
  }
  return objectColor;
} 

  bool Sphere::intersect(const ray &r, float t_min, float &t_max, HitStruct &hit) const
{
  vec3 oc = r.origin() - center;

  float a = dot(r.direction(), r.direction());
  float b = 2.0f * dot(oc, r.direction());
  float c = dot(oc, oc) - radius * radius;

  float discriminant = b * b - 4 * a * c;

  if (discriminant < 0) {
    return false;
  }

  float sqrt_disc = std::sqrt(discriminant);

  float t1 = (-b - sqrt_disc) / (2.0f * a);
  float t2 = (-b + sqrt_disc) / (2.0f * a);

  if (t1 > t_min && t1 < t_max) {
    t_max = t1;
    hit.t = t1;
    hit.point = r.at(t1);
    hit.shape = this;
    return true;
  }

  if (t2 > t_min && t2 < t_max) {
    t_max = t2;
    hit.t = t2;
    hit.point = r.at(t2);
    hit.shape = this;
    return true;
  }

  return false;
}