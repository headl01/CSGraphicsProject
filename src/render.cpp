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
#include "hit_struct.h"
#include "triangle.h"

vec3 computeRayColor(const ray &r, const std::vector<std::shared_ptr<Shape>> &shapes, std::vector<point3> lights)
{
  float t_min = 0.001f;
  float t_max = std::numeric_limits<float>::max();

  HitStruct closestHit;
  closestHit.t = t_max;
  bool hitAnything = false;

  // Check intersection with all shapes, find closest
  for (const auto &shape : shapes) {
    HitStruct tempHit;
    if (shape->intersect(r, t_min, t_max, tempHit)) {
      if (tempHit.t < closestHit.t) {
        closestHit = tempHit;
        hitAnything = true;
        t_max = tempHit.t;
      }
    }
  }

  if (hitAnything) {
    for (int i = 0; i < lights.size(); i++) {

      vec3 toLight = lights[i] - closestHit.point;
      float lightDist = toLight.length();
      vec3 lightDir = unit_vector(toLight);

      ray shadowRay(closestHit.point + 0.001 * closestHit.normal, lightDir);

      HitStruct tempHit;
      for (const auto &shape : shapes) {
        
        if (shape->intersect(shadowRay, 0.001, lightDist, tempHit)) {
          if (shape->getShader() != "mirror") {
            return vec3(0, 0, 0);// in shadow
          }
        }
      }
    } //loop checks to see if there are any shadow-casting objects between light sources

    return closestHit.shape->getColor(r, lights, 5, shapes);
  }

  // Background color
  vec3 unit_direction = unit_vector(r.direction());
  auto a = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - a) * vec3(1.0, 1.0, 1.0) + a * vec3(0.5, 0.7, 1.0);
}

float random_float()
{
  float random = rand() / (RAND_MAX + 1.0);
  //std::cout << random; for debug
  return random;
}

int main(int argc, char *argv[])
{
  int width = 1000;
  int height = 1000;
  PerspectiveCamera p(width, height);
  Framebuffer fb(width, height);
  srand(time(0));

  std::vector<Sphere> objectList;
  std::vector<point3> lights;

  point3 l1 = vec3{ 10, 150, 0 };
  //lights.push_back(l1);
  //point3 l2 = vec3{ 0, 0, -300 };
  //lights.push_back(l2);
  point3 l2 = vec3{ 15, -15, 0 };
  lights.push_back(l2);

   std::vector<std::shared_ptr<Shape>> shapes;
  // Red Triangle 1
  //shapes.push_back(std::make_shared<Triangle>(vec3(30, 0, -500), vec3(800, -5, -500), vec3(9, 10, -500), vec3(1.0, 0.0, 0.0), ""));

  // Green Triangle 2
  //shapes.push_back(std::make_shared<Triangle>(
    //vec3(0.773205, -0.93923, -7), vec3(0.0330127, 0.94282, -5), vec3(-0.45, 0.779423, -5), vec3(0.0, 1.0, 0.0)));

  // Blue Triangle 3
  //shapes.push_back(std::make_shared<Triangle>(
    //vec3(0.426795, 1.13923, -7), vec3(-0.833013, -0.44282, -5), vec3(-0.45, -0.779423, -5), vec3(0.0, 0.0, 1.0)));
 
  Sphere s1(vec3{ 2.5, 0.0, -30.0 }, 1, vec3{ 0, 0, 100 }, "mirror");
  shapes.push_back(std::make_shared<Sphere>(s1));
  Sphere s2(vec3{ -2.5, 0.0, -30.0 }, 1, vec3{ 0, 0, 100 }, "mirror");
  Sphere s(vec3{ 0.0, 0.0, -25.0 }, 1, vec3{ 0, 0, 100 }, "lambertian");

  Sphere s3(vec3{ 0.0, -1000.0, 0 }, 980, vec3{ 0, 0, 100 }, "lambertian");
  
 //shapes.push_back(std::make_shared<Sphere>(s2));
 shapes.push_back(std::make_shared<Sphere>(s));

 shapes.push_back(std::make_shared<Sphere>(s3));

 Sphere ground(vec3{ 0.0, 1003.0, -30.0 }, 1000, vec3{ 0.5, 0.5, 0.5 }, "lambertian");
 shapes.push_back(std::make_shared<Sphere>(ground));


  fb.clearToColor(vec3{ 0, 0, 175 });
 /*
  float t;
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      ray r = p.generateRay(x, y);
      fb.setPixelColor(y * width + x, computeRayColor(r, shapes, lights));
    }
  }
  */
  //troublesome attempt at anti aliasing...
  
  int samplessqrd = 3;

  float t;
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {

      vec3 avgColor(0, 0, 0);

      for (int i = 0; i < samplessqrd; i++) {
        for (int j = 0; j < samplessqrd; j++) {

          float Xij = (x + (i + random_float()) / samplessqrd) / width;
          float Yij = (y + (j + random_float()) / samplessqrd) / height;

          ray r = p.generateRay(Xij, Yij);
          avgColor += computeRayColor(r, shapes, lights);
        }
      }

      avgColor = avgColor/(samplessqrd * samplessqrd);
      
      
      // Gamma correction
      avgColor = vec3(
        sqrt(avgColor.x()),
        sqrt(avgColor.y()),
        sqrt(avgColor.z()));

        avgColor = clampToOne(avgColor);

      fb.setPixelColor(x + y * width, avgColor);
    }
  }

         



  //fb.greyscaleFilter();

  //fb.clearToGradient(vec3{ 255, 120, 0 }, vec3{ 0, 0, 255 });
  fb.exportToPNG("test1.png");
}