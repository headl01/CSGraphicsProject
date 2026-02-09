#pragma once

#include "ray.h"

class Shape
{
public:
  virtual bool intersect(const ray &r, float tmin, float &tmax) = 0;
};
