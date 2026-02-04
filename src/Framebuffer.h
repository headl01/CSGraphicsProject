#pragma once

#include <vector>
#include "vec3/vec3.h"

using color = vec3;

class Framebuffer
{
public:
  // default constructor -- want a simple width and height
  Framebuffer();

  Framebuffer(int w, int h);

  void clearToColor(color c);
  void clearToGradient(color c0, color c1);

  void setPixelColor(int i, int j, color c);
  void setPixelColor(int index, color c);

  void exportToPNG(std::string filename);

  float getFbR(int index);
  float getFbG(int index);
  float getFbB(int index);

private:
  int width, height;
  std::vector<color> fbStorage;
};
