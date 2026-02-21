#pragma once

#ifndef SPHERE_H
#define SPHERE_H

#include "hit_list.h"
#include "vec3/vec3.h"

class Sphere : public hittable
{
public:
  Sphere(const point3 &center, double radius, vec3 color, std::string shader) : center(center), radius(std::fmax(0, radius)), objectColor(color), shader(shader) {}

  /**
  //funcitons for normal shading
  double hit_sphere(const ray &r)
  {
    vec3 oc = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto b = -2.0 * dot(r.direction(), oc);
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
      return -1.0;
    } else {
      return (-b - std::sqrt(discriminant)) / (2.0 * a);
    }
  }

  vec3 ray_color(const ray &r)
  {
    auto t = hit_sphere(r);
    if (t > 0.0) {
      vec3 N = unit_vector(r.at(t) - center);
      return 0.5 * vec3(N.x() + 1, N.y() + 1, N.z() + 1);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * vec3(1.0, 1.0, 1.0) + a * vec3(0.5, 0.7, 1.0);
  }

  //functions for normal shading ^
  */
  bool hit(const ray &r, float ray_tmin, float ray_tmax, float &t) const override
  {
    vec3 oc = center - r.origin();
    auto a = r.direction().length_squared();
    auto h = dot(r.direction(), oc);
    auto c = oc.length_squared() - radius * radius;

    auto discriminant = h * h - a * c;
    if (discriminant < 0)
      return false;

    auto sqrtd = std::sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (h - sqrtd) / a;
    if (root <= ray_tmin || ray_tmax <= root) {
      root = (h + sqrtd) / a;
      if (root <= ray_tmin || ray_tmax <= root)
        return false;
    }

    t = root;

    return true;
  }

  vec3 ray_color(const ray &r);

private:
  point3 center;
  double radius;
  vec3 objectColor = vec3{ 0, 0, 0 };
  std::string shader;
};

#endif

/**
#include "vec3/vec3.h"
#include "Shape.h"

class Sphere : public Shape
{
public:
  Sphere() : center(0.0, 0.0, -15.0), radius(1) {}// unit sphere
  Sphere(vec3 center, float rad, vec3 c) : center(center), radius(rad), objectColor(c) {}

  bool intersect(const ray &r, float tmin, float &tmax) override;
  double hit_sphere(const ray &r);
  vec3 ray_color(const ray &r);

private:
  vec3 center;
  float radius;
  vec3 objectColor = vec3{ 0, 0, 0 };
};
**/