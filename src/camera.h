#pragma once
#include "vec3/Vec3.h";
#include "ray.h"

class Camera
{

	public:
  Camera(int pixel_nx, int pixel_ny) : pos(0,0,0), U(1,0,0), V(0,1,0), W(0,0,1), 
	  focalLength(1.0), imageplane_width(0.25), imageplane_height(0.25),
      nx(pixel_nx), ny(pixel_ny){}; //Default camera

  virtual ~Camera(); //Destructor

  virtual void generateRay(int i, int j, ray &r) = 0;

	protected:
  vec3 U, V, W; //basis unit vectors for orientation
  vec3 pos;

  float focalLength; //Also d

  float imageplane_width, imageplane_height;
  int nx, ny;
};