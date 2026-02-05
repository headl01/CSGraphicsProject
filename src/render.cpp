//This is more or less the main file, all changes to the backend code will be tested and rendered thru here

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <random>

#include "vec3/vec3.h"
#include "Framebuffer.h"
#include "handleGraphicsArgs.h"
#include "PerspectiveCamera.h"
//#include "camera.h"

int main(int argc, char *argv[])
{
  
  PerspectiveCamera p;
  Framebuffer fb(1000,800);

  for (int x = 0; x < 1000; x++) {
    for (int y = 0; y < 1000; y++) {
        ray r = p.generateRay(x, y);
      fb.setPixelColor(x * 1000 + y, r.direction());
    }
  }



  //fb.clearToGradient(vec3{ 255, 120, 0 }, vec3{ 0, 0, 255 });
  fb.exportToPNG("test.png");
}