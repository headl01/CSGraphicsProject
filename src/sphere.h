#pragma once

#ifndef SPHERE_H
#define SPHERE_H

#include "hit_list.h"
#include "shape.h"
#include "vec3/vec3.h"
#include <vector>

class Sphere : public Shape
{
public:
  Sphere(const point3 &center, double radius, vec3 color, std::string shader) : center(center), radius(std::fmax(0, radius)), objectColor(color), shader(shader) {}

  bool intersect(const ray &r, float t_min, float &t_max, HitStruct &hit) const override;

  vec3 ray_color(const ray &r, std::vector<point3> lights, std::vector<Sphere> objectList, int recursions);

  vec3 getColor(ray r, std::vector<point3> lights) const override;

private:
  point3 center;
  double radius;
  vec3 objectColor = vec3{ 0, 0, 0 };
  std::string shader;
};

#endif

/**
#include "vec3/vec3.h"
#include "Shape.h"

class Sphere : public Shape
{
public:
  Sphere() : center(0.0, 0.0, -15.0), radius(1) {}// unit sphere
  Sphere(vec3 center, float rad, vec3 c) : center(center), radius(rad), objectColor(c) {}

  bool intersect(const ray &r, float tmin, float &tmax) override;
  double hit_sphere(const ray &r);
  vec3 ray_color(const ray &r);

private:
  vec3 center;
  float radius;
  vec3 objectColor = vec3{ 0, 0, 0 };
};
**/