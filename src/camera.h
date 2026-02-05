#pragma once

#include "ray.h"

class Camera
{
public:
  Camera();
  Camera(int pixel_nx, int pixel_ny);

  // camera needs to know pixel image dimensions...
  // so, you can provide to the Camera constructor or use a default,
  // or even pass in as an argument to the generateRay function
  // virtual ray generateRay( int i, int j, int nx, int ny ) = 0;

  virtual ray generateRay(int i, int j) = 0;

protected:
  vec3 pos;// position of camera

  // basis vectors for camera
  vec3 U, V, W;

  float l = (-imagePlane_width / 2);
  float rb = (imagePlane_width / 2);
  float b = (-imagePlane_height / 2);
  float t = (imagePlane_height / 2);

  float focalLength;// also sometimes referred to as "d"
  float imagePlane_width, imagePlane_height;

  int nx, ny;
};