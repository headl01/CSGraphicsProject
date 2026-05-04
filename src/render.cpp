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
          if (shape->getShader() != "mirror" && shape->getShader() != "glass") {
            return vec3(0, 0, 0);// in shadow
          }
        }
      }
    } //loop checks to see if there are any shadow-casting objects between light sources

    return closestHit.shape->getColor(r, lights, 10, shapes);
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
  //shapes.push_back(std::make_shared<Triangle>(vec3(30, 0, -500), vec3(800, -5, -500), vec3(9, 10, -500), vec3(1.0, 0.0, 0.0), "glass"));

  // Green Triangle 2
  //shapes.push_back(std::make_shared<Triangle>(
    //vec3(0.773205, -0.93923, -7), vec3(0.0330127, 0.94282, -5), vec3(-0.45, 0.779423, -5), vec3(0.0, 1.0, 0.0)));

  // Blue Triangle 3
  //shapes.push_back(std::make_shared<Triangle>(
    //vec3(0.426795, 1.13923, -7), vec3(-0.833013, -0.44282, -5), vec3(-0.45, -0.779423, -5), vec3(0.0, 0.0, 1.0)));
 
   Sphere cue(vec3{ -1.0, 0.03, -20.0 }, 0.6, vec3{ 250, 250, 227 }, "basicCeramic");
   shapes.push_back(std::make_shared<Sphere>(cue));
   Sphere glassCueBall(vec3{ -1.0, 0.03, -20.0 }, 0.7, vec3{ 0, 25, 100 }, "glass");
   shapes.push_back(std::make_shared<Sphere>(glassCueBall));
   Sphere blue1(vec3{ 1.0, 0.0, -35.0 }, 0.6, vec3{ 0, 0, 227 }, "basicCeramic");
   shapes.push_back(std::make_shared<Sphere>(blue1));
   Sphere glassblue1(vec3{ 1.0, 0.0, -35.0 }, 0.7, vec3{ 0, 25, 100 }, "glass");
   shapes.push_back(std::make_shared<Sphere>(glassblue1));
   Sphere red1(vec3{ 2.5, 0.0, -35.0 }, 0.6, vec3{ 102, 0, 23 }, "basicCeramic");
   shapes.push_back(std::make_shared<Sphere>(red1));
   Sphere glassRed1(vec3{ 2.5, 0.0, -35.0 }, 0.7, vec3{ 0, 25, 100 }, "glass");
   shapes.push_back(std::make_shared<Sphere>(glassRed1));
   Sphere orange1(vec3{ 2.5, 0.450, -30.0 }, 0.2, vec3{ 204, 85, 0 }, "basicCeramic");
   shapes.push_back(std::make_shared<Sphere>(orange1));
   Sphere glassorange1(vec3{ 2.5, 0.450, -30.0 }, 0.3, vec3{ 0, 25, 100 }, "glass");
   shapes.push_back(std::make_shared<Sphere>(glassorange1));
   Sphere blue2(vec3{ 3.5, 0.45, -30.0 }, 0.2, vec3{ 4, 4, 100 }, "basicCeramic");
   shapes.push_back(std::make_shared<Sphere>(blue2));
   Sphere glassblue2(vec3{ 3.5, 0.450, -30.0 }, 0.3, vec3{ 0, 25, 100 }, "glass");
   shapes.push_back(std::make_shared<Sphere>(glassblue2));

 Sphere ground(vec3{ 0.0, 1003.0, -30.0 }, 1002.265, vec3{ 1, 109, 8 }, "lambertian");
 shapes.push_back(std::make_shared<Sphere>(ground));

 Sphere background(vec3{ 0.0, 1003.0, -30000.0 }, 10000, vec3{ 116, 32, 63 }, "lambertian");
 shapes.push_back(std::make_shared<Sphere>(background));
 Sphere ceiling(vec3{ 0.0, -1053.0, -30.0 }, 1005, vec3{ 25, 25, 25 }, "basicCeramic");
 shapes.push_back(std::make_shared<Sphere>(ceiling));

  fb.clearToColor(vec3{ 116, 32, 63 });
 
  
  int samplessqrd = 3;
  int total = height * width;
  int count = 0;
  int percent = 0;
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

      count++;

      double progress = (double)count / total * 100;

      while ((int)progress >= percent && percent <= 100) {
        std::cout << percent << "% completed out of 100" << std::endl;
        if (percent < 95) {
          percent += 5;
        } else {
          percent++;
        }
      }
        //std::cout << "Processed pixel: " << count << " out of " << total << std::endl;
    }
  }

         



  //fb.greyscaleFilter();

  //fb.clearToGradient(vec3{ 255, 120, 0 }, vec3{ 0, 0, 255 });
  fb.exportToPNG("test1.png");
}