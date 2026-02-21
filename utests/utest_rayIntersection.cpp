#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <../src/ray.h>
#include <../src/PerspectiveCamera.h>
#include <../src/sphere.h>

/**
TEST_CASE("Ray intersection true")
{
  int width = 1000;
  int height = 1000;
  PerspectiveCamera p(width, height);
  Sphere s;

  ray r = p.generateRay(500, 500);

  REQUIRE(s.hit_sphere(r) != -1);
}

TEST_CASE("Ray intersection false")
{
  int width = 1000;
  int height = 1000;
  PerspectiveCamera p(width, height);
  Sphere s;

  ray r = p.generateRay(1, 1);

  REQUIRE(s.hit_sphere(r) == -1);
}**/