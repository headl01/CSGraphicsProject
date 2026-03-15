#pragma once

#include "Camera.h"

class PerspectiveCamera : public Camera
{
public:
  PerspectiveCamera();
  PerspectiveCamera(float pixel_nx, float pixel_ny);

  // you do need this...
  // PerspectiveCamera( vec3 origin, vec3 viewdir, float focallength, ...)

  ray generateRay(float i, float j) override
  {
    float u, v;
    vec3 dir;

    u = l + (r - l) * i;
    v = b + (t - b) * j;

    dir = -W * focalLength + U * u + V * v;
    dir = dir / dir.length();

    return ray(pos, dir);
  }

private:
  float l, r, b, t;
};