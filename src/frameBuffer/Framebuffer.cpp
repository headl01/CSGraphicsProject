#include "Framebuffer.h"
#include "../vec3/Vec3.h"

Framebuffer::Framebuffer() 
: width(100), height(100), fbStorage(width*height)
{

}

Framebuffer::Framebuffer(int x, int y)
  : width(x), height(y), fbStorage(width*height)
{

}




void Framebuffer::clearToColor(vec3 c) {
  std::vector<vec3> tempVec;

 // tempVec = 
  for (auto idx = 0u; idx < fbStorage.size(); idx++) {
    fbStorage[idx] = c;
  }

}





void setWidth(int w) {};
int getWidth();

void setHeight(int h);
int getHeight();

std::vector<vec3> getFbStorage();
void setFbStorage(std::vector<vec3> v);