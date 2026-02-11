#include "Sphere.h"
#include "vec3/vec3.h"

bool Sphere::intersect(const ray &r, float tmin, float &tmax)
{
  return true;
  // compute code from slides here
  // return true if hit...
}

double Sphere::hit_sphere(const ray &r)
{
  vec3 oc = center - r.origin();
  auto a = dot(r.direction(), r.direction());
  auto b = -2.0 * dot(r.direction(), oc);
  auto c = dot(oc, oc) - radius * radius;
  auto discriminant = b * b - 4 * a * c;

  if (discriminant < 0) {
    return -1.0;
  } else {
    return (-b - std::sqrt(discriminant)) / (2.0 * a);
  }
}

vec3 Sphere::ray_color(const ray &r)
{
  auto t = hit_sphere(r);
  if (t > 0.0) {
    vec3 N = unit_vector(r.at(t) - center);
    return 255 * vec3(N.x() + 1,N.y() + 1,N.z() + 1);
  }

  vec3 unit_direction = unit_vector(r.direction());
  auto a = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - a) * vec3(1.0, 1.0, 1.0) + a * vec3(0.5, 0.7, 1.0);
}