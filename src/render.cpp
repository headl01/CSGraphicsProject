#include <iostream>
#include <cstdlib>
#include <cstring>
#include <random>

#include "vec3/vec3.h"
#include "Framebuffer.h"

#include "handleGraphicsArgs.h"

int main(int argc, char *argv[])
{
  sivelab::GraphicsArgs args;
  args.process(argc, argv);

  int w = args.width, h = args.height;

  Framebuffer fb;
}
