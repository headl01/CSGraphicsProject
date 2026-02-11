//This is more or less the main file, all changes to the backend code will be tested and rendered thru here

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <random>

#include "vec3/vec3.h"
#include "Framebuffer.h"
#include "handleGraphicsArgs.h"
#include "PerspectiveCamera.h"
#include "camera.h"
#include "sphere.h"

int main(int argc, char *argv[])
{
  int width = 1000;
  int height = 1000;
  PerspectiveCamera p(width,height);
  Framebuffer fb(width,height);

  Sphere s;

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
        ray r = p.generateRay(x, y);
        /**/
        if (s.hit_sphere(r)) {
          fb.setPixelColor(x * width + y, s.ray_color(r));
        } else {
          fb.setPixelColor(x * width + y, r.direction());

        }
    }
  }



  //fb.clearToGradient(vec3{ 255, 120, 0 }, vec3{ 0, 0, 255 });
  fb.exportToPNG("test1.png");
}