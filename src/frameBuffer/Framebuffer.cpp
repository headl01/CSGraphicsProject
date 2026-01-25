#include "Framebuffer.h"
#include "../vec3/vec3.h"

using color = vec3;


Framebuffer::Framebuffer() 
: width(100), height(100), fbStorage(width*height)
{

}

Framebuffer::Framebuffer(int x, int y)
  : width(x), height(y), fbStorage(width*height)
{

}




void clearToColor(color c, std::vector<vec3> fbStorage)
{
  for (auto idx = 0u; idx < fbStorage.size(); idx++) {
    fbStorage[idx] = c;
  }
}

void clearToGradient(color c1, color c2, std::vector<vec3> fbStorage)
{
  for (auto idx = 0u; idx < fbStorage.size(); idx++) {
    fbStorage[idx] = constLerp(c1, c2, idx/fbStorage.size());
  }
} //produces a constant gradient, so it will have kind of a diagonal look





void setWidth(int w) {};
int getWidth();

void setHeight(int h);
int getHeight();

std::vector<vec3> getFbStorage();
void setFbStorage(std::vector<vec3> v);