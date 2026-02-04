#include "Framebuffer.h"
#include <string>

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
  // need to use example code in test_pngWrite.cpp to mesh here with framebuffer data
}