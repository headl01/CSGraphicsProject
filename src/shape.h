#pragma once

#include "hit_struct.h"
#include "ray.h"
#include "vec3/vec3.h"

class Shape
{
public:
  virtual bool intersect(const ray &r, float t_min, float &t_max, HitStruct &hit) const = 0;
  virtual vec3 getColor() const = 0;
};