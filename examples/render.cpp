#include <iostream>
#include <cstdlib>
#include <cstring>
#include <random>

#include "../src/png++/png.hpp"
#include "../src/vec3/vec3.h"
#include "../src/frameBuffer/Framebuffer.h"

#include "../src/handleGraphicsArgs.h"

int main(int argc, char *argv[])
{
  sivelab::GraphicsArgs args;
  args.process(argc, argv);

  int w = args.width, h = args.height;
  png::image<png::rgb_pixel> imData(w, h);

  for (unsigned int idx = 0; idx < imData.get_height() * imData.get_width(); ++idx) {
    size_t x = idx % w;
    size_t y = static_cast<size_t>(floor(idx / static_cast<float>(imData.get_width())));

    // non-checking equivalent of image.set_pixel(x, y, ...);
    imData[y][x] = png::rgb_pixel(0,0,25);
  }
  imData.write("simpleGradient.png");

}
