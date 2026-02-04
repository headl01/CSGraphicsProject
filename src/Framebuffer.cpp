#include <string>

// needed for export function
#include "png++/png.hpp"

#include "Framebuffer.h"

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

void Framebuffer::clearToColor(color c)
{
  for (auto idx = 0u; idx < fbStorage.size(); ++idx) {
    fbStorage[idx] = c;
  }
}

float Framebuffer::getFbR(int index)
{
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

void Framebuffer::exportToPNG(std::string filename)
{
  // need to use example code in test_pngWrite.cpp to mesh here with
  // framebuffer data
    //int width = 100;
    //int height = 100;
    
    png::image<png::rgb_pixel> imData(width, height);
    for (unsigned int idx = 0; idx < imData.get_height() * imData.get_width(); ++idx) {
      size_t x = idx % width;
      size_t y = static_cast<size_t>(floor(idx / static_cast<float>(imData.get_width())));

      // non-checking equivalent of image.set_pixel(x, y, ...);
      imData[y][x] = png::rgb_pixel(getFbR(idx), getFbG(idx), getFbB(idx));
    }
    imData.write(filename);
}
