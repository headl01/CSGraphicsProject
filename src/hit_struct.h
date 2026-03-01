#pragma once
#include "vec3/vec3.h"

class Shape;

struct HitStruct
{
  float t;
  vec3 point;
  const Shape *shape = nullptr;
};