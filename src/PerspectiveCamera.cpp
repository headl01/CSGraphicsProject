#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera()
  : Camera()
{
  l = -imagePlane_width / 2.0;
  r = imagePlane_width / 2.0;

  b = -imagePlane_height / 2.0;
  t = imagePlane_height / 2.0;
}

PerspectiveCamera::PerspectiveCamera(int pixel_nx, int pixel_ny)
  : Camera(pixel_nx, pixel_ny)
{
}

// PerspectiveCamera( vec3 origin, vec3 viewdir, float focallength, ...)