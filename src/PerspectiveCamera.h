#pragma once

#include "vec3/vec3.h"
#include "camera.h"


class PerspectiveCamera : public Camera
{
public:
  PerspectiveCamera()
    : Camera(1000, 1000) {}
  ///PerspectiveCamera(vec3 origin, vec3 viewDir, vec3 focalLength);

  ray generateRay(int i, int j) {
      //dist from origin modified with the pixel size

      float u, v;

      ray tempRay(pos, -W * focalLength + U * u + V * v);

      return tempRay;
  }
};