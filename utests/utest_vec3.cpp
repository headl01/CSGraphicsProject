#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <../src/vec3/Vec3.h>

TEST_CASE("Vectors")
{
  vec3 v1 = { 7.0, 14.0, 10.0 };
  vec3 v2 = { 2.0, 2.0, 2.0 };
  vec3 v3 = { 1.0, 1.0, 1.0 };
  vec3 productV;

  productV = operator+(v2, v3);
  REQUIRE(productV == vec3{ 3.0, 3.0, 3.0 }); //Test one, addition

  productV = operator-(v2, v3);
  REQUIRE(productV == vec3{ 1.0, 1.0, 1.0 }); //Test two, subtraction

  productV = operator*(v2, v3);
  REQUIRE(productV == vec3{ 2.0, 2.0, 2.0 }); //Test three, multiplicaiton 

  productV = clampToOne(v1);
  REQUIRE(productV == v3); //Test 4, clamping to one

   productV = clampToN(v1, 2);
  REQUIRE(productV == v2); //Test 5, clamping to N

}
