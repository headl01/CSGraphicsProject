#include "Framebuffer.h"
#include <string>


#include "../png++/png.hpp"
#include "../vec3/vec3.h"
#include "../frameBuffer/Framebuffer.h"

#include "../handleGraphicsArgs.h"

Framebuffer::Framebuffer()
  : width(100), height(100), fbStorage(width * height)
{
}

Framebuffer::Framebuffer(int w, int h)
  : width(w), height(h), fbStorage(width * height)
{
}

void Framebuffer::setPixelColor(int index, color c) {
  fbStorage[index] = c;
}

void Framebuffer::setPixelColor(int i, int j, color c)
{
  //fbStorage[i][j] = c;
}

void Framebuffer::clearToColor(color c)
{
  for (auto idx = 0u; idx < fbStorage.size(); ++idx) {
    fbStorage[idx] = c;
  }
}

void Framebuffer::clearToGradient(color c0, color c1)
{
  for (auto x = 0; x < width; x++) {
    for (auto y = 0; y < height; y++) {

      float t = y / (float)height;

      // need to loop over and lerp here...
      color c2 = c0 * (1 - t) + c1 * t;

      int idx = y * width + x;
      fbStorage[idx] = c2;
    }
  }
}

float Framebuffer::getFbR(int index) {
  return fbStorage[index].e[0];
};
float Framebuffer::getFbG(int index)
{
  return fbStorage[index].e[1];
};
float Framebuffer::getFbB(int index)
{
  return fbStorage[index].e[2];
};

void Framebuffer::exportToPNG(std::string filename)
{
  png::image<png::rgb_pixel> imData(width, height);

  for (unsigned int idx = 0; idx < imData.get_height() * imData.get_width(); ++idx) {
    size_t x = idx % width;
    size_t y = static_cast<size_t>(floor(idx / static_cast<float>(imData.get_width())));

    // non-checking equivalent of image.set_pixel(x, y, ...);
    imData[y][x] = png::rgb_pixel(getFbR(idx), getFbG(idx), getFbB(idx));
  }
  imData.write(filename);
}