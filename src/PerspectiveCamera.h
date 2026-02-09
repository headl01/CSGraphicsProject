#pragma once

#include "Camera.h"

class PerspectiveCamera : public Camera
{
public:
  PerspectiveCamera();
  PerspectiveCamera(int pixel_nx, int pixel_ny);

  // you do need this...
  // PerspectiveCamera( vec3 origin, vec3 viewdir, float focallength, ...)

  ray generateRay(int i, int j) override
  {
    float u, v;
    vec3 dir;
    u = l + (r - l) * (i + 0.5) / (float)nx;
    v = b + (t - b) * (j + 0.5) / (float)ny;

    dir = -W * focalLength + U * u + V * v;
    dir = (dir / dir.length())*255;

    ray tempRay(pos, dir);

    //std::cout << tempRay.direction();

    return tempRay;
  }

private:
  float l, r, b, t;
};