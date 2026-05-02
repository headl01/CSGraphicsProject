#ifndef MAKECERAMICTEX_H
#define MAKECERAMIXTEX_H

#include "vec3/vec3.h"
#include <vector>

using color = vec3;

class makeCeramicTex
{
public:
  void genCeramicBk(vec3 color);

private:
  int width, height;

  std::vector<vec3> fbStorage;

};

#endif// ! MAKECERAMICTEX_H
