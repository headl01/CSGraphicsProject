#pragma once

#include "hit_struct.h"
#include "ray.h"
#include "vec3/vec3.h"
#include <vector>

class Shape
{
public:
  virtual bool intersect(const ray &r, float t_min, float &t_max, HitStruct &hit) const = 0;
  virtual vec3 getColor(ray r, std::vector<point3> lights, int recursions, std::vector<std::shared_ptr<Shape>> shapes) const = 0;
  virtual std::string getShader() const = 0;
  virtual vec3 getObjColor() const = 0;
};