#include <iostream>
#include <cstdlib>
#include <cstring>
#include <random>

#include "vec3/vec3.h"
#include "Framebuffer.h"
#include "png++/png.hpp"
#include "handleGraphicsArgs.h"

int main(int argc, char *argv[])
{
  Framebuffer fb(1000,800);
  fb.clearToGradient(vec3{ 255, 120, 0 }, vec3{ 0, 0, 255 });
  fb.exportToPNG("test.png");
}