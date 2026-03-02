#include "Camera.h"

Camera::Camera()
  : pos(0, 0, 0), U(1, 0, 0), V(0, 1, 0), W(0, 0, 1),
    focalLength(1.0), imagePlane_width(0.25), imagePlane_height(0.25),
    nx(100), ny(100)
{
}

Camera::Camera(float pixel_nx, float pixel_ny)
  : pos(0, 0, 0), U(1, 0, 0), V(0, 1, 0), W(0, 0, 1),
    focalLength(1.0), imagePlane_width(0.25), imagePlane_height(0.25),
    nx(pixel_nx), ny(pixel_ny)
{
}