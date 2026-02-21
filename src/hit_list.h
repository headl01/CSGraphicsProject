#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include <algorithm>

class hit_record
{
public:
  point3 p;
  vec3 normal;
  double t;
};

class hittable
{
public:
  virtual ~hittable() = default;

  virtual bool hit(const ray &r, float ray_tmin, float ray_tmax, float &t) const = 0;
};

#endif