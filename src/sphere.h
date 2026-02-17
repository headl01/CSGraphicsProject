#pragma once

#include "vec3/vec3.h"
#include "Shape.h"

class Sphere : public Shape
{
public:
  Sphere() : center(0.0, 0.0, -15.0), radius(1) {}// unit sphere
  Sphere(vec3 center, float rad, vec3 c) : center(center), radius(rad), objectColor(c) {}

  // You'll want
  // Sphere( vec3 c, float r );

  bool intersect(const ray &r, float tmin, float &tmax) override;
  double hit_sphere(const ray &r);
  vec3 ray_color(const ray &r);

private:
  vec3 center;
  float radius;
  vec3 objectColor = vec3{ 0, 0, 0 };
};
