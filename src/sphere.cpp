#include "Sphere.h"

bool Sphere::intersect(const ray &r, float tmin, float &tmax)
{
  return true;
  // compute code from slides here
  // return true if hit...
}

bool Sphere::hit_sphere(const ray &r)
{
  vec3 oc = center - r.origin();
  auto a = dot(r.direction(), r.direction());
  auto b = -2.0 * dot(r.direction(), oc);
  auto c = dot(oc, oc) - radius * radius;
  auto discriminant = b * b - 4 * a * c;
  return (discriminant >= 0);
}