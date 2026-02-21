#include "Sphere.h"
#include "vec3/vec3.h"
#include <math.h>
#include <algorithm>

/*
bool Sphere::intersect(const ray &r, float tmin, float &tmax)
{
  return true;
  // compute code from slides here
  // return true if hit...
}
*/
/*
vec3 Sphere::ray_color(const ray &r)
{

  hit_record rec;
  float t;
  if (objectColor != vec3{0,0,0}) {
    if (hit(r, 0.001, INFINITY, t)) {
      vec3 hitPoint = r.at(t);

      vec3 lightPos = point3(-15, 10, 0);
      vec3 toLight = unit_vector(lightPos - hitPoint);
      vec3 N = unit_vector(hitPoint - center);

      return std::max(0.0, dot(N, toLight)) * objectColor;
    }

      vec3 unit_direction = unit_vector(r.direction());
      auto a = 0.5 * (unit_direction.y() + 1.0);
      return (1.0 - a) * vec3(1.0, 1.0, 1.0) + a * vec3(0.5, 0.7, 1.0);
  } //shader if color
  */
  /*
  else {
    if (t > 0.0) {
      vec3 N = unit_vector(r.at(t) - center);
      // N = vec3(0, 0, 1);
      return 0.5 * vec3(N.x() + 1, N.y() + 1, N.z() + 1);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * vec3(1.0, 1.0, 1.0) + a * vec3(0.5, 0.7, 1.0);
  } //normal if no object color
 
} */