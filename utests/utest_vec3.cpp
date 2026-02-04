#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "vec3/vec3.h"

TEST_CASE("Vector Addition")
{
  vec3 v1 = { 7.0, 14.0, 10.0 };
  vec3 v2 = { 2.0, 2.0, 2.0 };
  vec3 v3 = { 1.0, 1.0, 1.0 };
  vec3 productV;

  productV = v2+v3;
  REQUIRE(productV == vec3{ 3.0, 3.0, 3.0 }); //Test one, addition
}

TEST_CASE("Vector Subtraction") {
  vec3 v1 = { 7.0, 14.0, 10.0 };
  vec3 v2 = { 2.0, 2.0, 2.0 };
  vec3 v3 = { 1.0, 1.0, 1.0 };
  vec3 productV;

  
  productV = v2-v3;
  REQUIRE(productV == vec3{ 1.0, 1.0, 1.0 });// Test two, subtraction

}

TEST_CASE("Vector Multiplicaiton")
{
  vec3 v1 = { 7.0, 14.0, 10.0 };
  vec3 v2 = { 2.0, 2.0, 2.0 };
  vec3 v3 = { 1.0, 1.0, 1.0 };
  vec3 productV;

    productV = v2*v3;
  REQUIRE(productV == vec3{ 2.0, 2.0, 2.0 });// Test three, multiplicaiton

   productV = v2 * v1;
  REQUIRE(productV == vec3{ 14.0, 28.0, 20.0 });
}

TEST_CASE("Vector clamp at one")
{
  vec3 v1 = { 7.0, 14.0, 10.0 };
  vec3 v2 = { 2.0, 2.0, 2.0 };
  vec3 v3 = { 1.0, 1.0, 1.0 };
  vec3 productV;


  productV = clampToOne(v1);
  REQUIRE(productV == v3);// Test 4, clamping to one
}

TEST_CASE("Vector clamp at n")
{
  vec3 v1 = { 7.0, 14.0, 10.0 };
  vec3 v2 = { 2.0, 2.0, 2.0 };
  vec3 v3 = { 1.0, 1.0, 1.0 };
  vec3 productV;

   productV = clampToN(v1, 2);
  REQUIRE(productV == v2);// Test 5, clamping to N
}
