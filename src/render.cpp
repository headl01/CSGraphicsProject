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

int main(int argc, char *argv[])
{
  int width = 1000;
  int height = 1000;
  PerspectiveCamera p;
  Framebuffer fb(width,height);

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
        ray r = p.generateRay(x, y);
      fb.setPixelColor(x * width + y, r.direction());
    }
  }



  //fb.clearToGradient(vec3{ 255, 120, 0 }, vec3{ 0, 0, 255 });
  fb.exportToPNG("test1.png");
}