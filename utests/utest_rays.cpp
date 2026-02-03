#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <../src/ray.h>

TEST_CASE("Ray Addition") {
  ray r1({ 0, 0, 0 }, {1,0,1});
  ray r2({ 0, 0, 0 }, { 0,1,0 });

  ray r3({ 0, 0, 0 }, { 1, 1, 1 });

  REQUIRE(r1.direction() + r2.direction() == r3.direction());
}

TEST_CASE("Ray Multiplicaiton")
{
  ray r1({ 0, 0, 0 }, { 1, 0, 1 });
  ray r2({ 0, 0, 0 }, { 2, 1, 0 });

  ray r3({ 0, 0, 0 }, { 2, 0, 0 });

  REQUIRE(r1.direction() * r2.direction() == r3.direction());
}

TEST_CASE("Ray construction")
{
  ray r1({ 0, 0, 0 }, { 1, 0, 1 });
  ray r2({ 0, 0, 0 }, { 0, 1, 0 });

  ray r3({ 0, 0, 0 }, { 1, 1, 1 });

  REQUIRE(r1.direction() == vec3{ 1, 0, 1 });
  REQUIRE(r1.origin() == point3{ 0, 0, 0 });
}

TEST_CASE("Ray origin test")
{
  ray r1({ 0, 0, 0 }, { 1, 0, 1 });
  ray r2({ 0, 0, 0 }, { 2, 1, 0 });

  ray r3({ 0, 0, 0 }, { 2, 0, 0 });

  r2.setDirection(r1.direction() * r2.direction());
  
  REQUIRE(r2.origin() == r1.origin());
} //tests to make sure that the origin point is not altered in any way