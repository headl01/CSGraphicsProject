//This is more or less the main file, all changes to the backend code will be tested and rendered thru here

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <random>
#include <list>

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
  PerspectiveCamera p(width, height);
  Framebuffer fb(width, height);

  std::vector<Sphere> objectList;
  std::vector<point3> lights;

  point3 l1 = vec3{ 0, 15, 0 };
  lights.push_back(l1);
  //point3 l2 = vec3{ 15, -15, 0 };
  //lights.push_back(l2);

  Sphere s(vec3{ 0.0, 0.0, -30.0 }, 1, vec3{ 0, 0, 100 }, "lambertian");
  objectList.push_back(s);
  Sphere s1(vec3{ 2.5, 0.0, -30.0 }, 1, vec3{ 0, 0, 100 }, "normal");
  objectList.push_back(s1);
  Sphere s2(vec3{ -2.5, 0.0, -30.0 }, 1, vec3{ 0, 0, 100 }, "Blinn-Phong");
  objectList.push_back(s2);
  Sphere s3(vec3{ 0, 0, -10000.0 }, 1000, vec3{ 250, 0, 0 }, "lambertian");
  objectList.push_back(s3);

  fb.clearToColor(vec3{ 0, 0, 175 });

  float t;
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      ray r = p.generateRay(x, y);
      for (int i = 0; i < objectList.size(); i++) {
        if (objectList[i].hit(r, 0.001, 10000000, t)) {
          fb.setPixelColor(y * width + x, objectList[i].ray_color(r, lights));
          break;
        } 
      }
    }
  }

      


  //fb.greyscaleFilter();

  //fb.clearToGradient(vec3{ 255, 120, 0 }, vec3{ 0, 0, 255 });
  fb.exportToPNG("test1.png");
}