#include "triangle.h"
#include "vec3/vec3.h"
#include <vector>


vec3 computeRayColor(const ray &r, const std::vector<std::shared_ptr<Shape>> &shapes, std::vector<point3> lights, int recursions)
{
  float t_min = 0.001f;
  float t_max = std::numeric_limits<float>::max();

  HitStruct closestHit;
  closestHit.t = t_max;
  bool hitAnything = false;

  // Check intersection with all shapes, find closest
  for (const auto &shape : shapes) {
    HitStruct tempHit;
    if (shape->intersect(r, t_min, t_max, tempHit)) {
      if (tempHit.t < closestHit.t) {
        closestHit = tempHit;
        hitAnything = true;
        t_max = tempHit.t;
      }
    }
  }

  if (hitAnything) {
    for (int i = 0; i < lights.size(); i++) {

      vec3 toLight = lights[i] - closestHit.point;
      float lightDist = toLight.length();
      vec3 lightDir = unit_vector(toLight);

      ray shadowRay(closestHit.point + 0.001 * closestHit.normal, lightDir);

      HitStruct tempHit;
      bool inShadow = false;

      for (const auto &shape : shapes) {
        HitStruct tempHit;

        if (shape->intersect(shadowRay, 0.001, lightDist, tempHit)) {
          if (shape->getShader() != "mirror" && shape->getShader() != "glass") {
            inShadow = true;
            break;
          }
        }
      }
      if (inShadow) {
        return vec3(0, 0, 0);
      }
    }// loop checks to see if there are any shadow-casting objects between light sources

    if (recursions <= 0) {
      return vec3(0, 0, 0);
    }

    return closestHit.shape->getColor(r, lights, recursions - 1, shapes);
  }

  // Background color
  vec3 unit_direction = unit_vector(r.direction());
  auto a = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - a) * vec3(1.0, 1.0, 1.0) + a * vec3(0.5, 0.7, 1.0);
}


bool Triangle::intersect(const ray &r, float t_min, float &t_max, HitStruct &hit) const
{
  double a = vertex_a[0] - vertex_b[0];
  double b = vertex_a[1] - vertex_b[1];
  double c = vertex_a[2] - vertex_b[2];

  double d = vertex_a[0] - vertex_c[0];
  double e = vertex_a[1] - vertex_c[1];
  double f = vertex_a[2] - vertex_c[2];

  double g = r.direction()[0];
  double h = r.direction()[1];
  double i = r.direction()[2];

  double j = vertex_a[0] - r.origin()[0];
  double k = vertex_a[1] - r.origin()[1];
  double l = vertex_a[2] - r.origin()[2];

  double ei_hf = e * i - h * f;
  double gf_id = g * f - d * i;
  double dh_eg = d * h - e * g;

  double M = a * ei_hf + b * gf_id + c * dh_eg;

  double t = -1.0, gamma = -1.0, beta = -1.0;

  double ak_jb = a * k - j * b;
  double jc_al = j * c - a * l;
  double bl_kc = b * l - k * c;

  t = -(f * ak_jb + e * jc_al + d * bl_kc) / M;
  if (t < t_min || t > t_max) {
    return false;
  }

  gamma = (i * ak_jb + h * jc_al + g * bl_kc) / M;
  if (gamma < 0.0 || gamma > 1.0) {
    return false;
  }

  beta = (j * ei_hf + k * gf_id + l * dh_eg) / M;
  if (beta < 0.0 || beta > 1.0 - gamma) {
    return false;
  }

  t_max = t;
  hit.t = t;
  hit.point = r.at(t);
  hit.shape = this;

  return true;
}

vec3 Triangle::getColor(ray r, std::vector<point3> lights, int recursions, std::vector<std::shared_ptr<Shape>> shapes) const
{
  HitStruct tempHit;
  float t_max = std::numeric_limits<float>::max();
    if (shader == "lambertian") {
    vec3 buildColor = vec3(0, 0, 0);

    if (color != vec3{ 0, 0, 0 }) {
      if (intersect(r, 0.001, t_max, tempHit)) {
        vec3 hitPoint = r.at(tempHit.t);

        vec3 N = unit_vector(cross(vertex_b-vertex_a,vertex_c-vertex_a));
        for (int i = 0; i < lights.size(); i++) {
          vec3 toLight = unit_vector(lights[i] - hitPoint);
          float returnVector = (std::max(0.0, dot(-N, toLight)));
          buildColor = vec3{ color.x() + returnVector, color.y() + returnVector, color.z() + returnVector };
        }
        return clampToOne(buildColor * unit_vector(color));
      }

      vec3 unit_direction = unit_vector(r.direction());
      auto a = 0.5 * (unit_direction.y() + 1.0);
      return (1.0 - a) * vec3(1.0, 1.0, 1.0) + a * vec3(0.5, 0.7, 1.0);
    }
    }
    if (shader == "glass") {
      vec3 buildColor = vec3(0, 0, 0);
      if (intersect(r, 0.001, t_max, tempHit)) {
        vec3 dir = vec3(0, 0, 0);
        vec3 hitPoint = r.at(tempHit.t);

        float refraction_index = 1.5;
        vec3 N = unit_vector(cross(vertex_b - vertex_a, vertex_c - vertex_a));
        vec3 unit_direction = unit_vector(r.direction());

        bool front_face = dot(unit_direction, N) < 0;
        vec3 outward_normal = front_face ? N : -N;
        float ri = front_face ? (1.0 / refraction_index) : refraction_index;

        float cos_theta = fmin(dot(-unit_direction, outward_normal), 1.0);
        float sin_theta = sqrt(1.0 - cos_theta * cos_theta);

        if (ri * sin_theta > 1.0) {
          dir = reflect(unit_direction, outward_normal);
        } else {
          dir = refract(unit_direction, outward_normal, ri);
        }
        if (recursions <= 0) {
          return vec3(0, 0, 0);
        }

        return computeRayColor(ray(hitPoint + 0.001 * dir, dir),
          shapes,
          lights,
          recursions - 1);
      }



      vec3 unit_direction = unit_vector(r.direction());
      auto a = 0.5 * (unit_direction.y() + 1.0);
      return (1.0 - a) * vec3(1.0, 1.0, 1.0) + a * vec3(0.5, 0.7, 1.0);
    }
    
    if (shader == "perfectCeramic") {
      vec3 buildColor = vec3(0, 0, 0);

      if (color != vec3{ 0, 0, 0 }) {
        if (intersect(r, 0.001, t_max, tempHit)) {
          vec3 hitPoint = r.at(tempHit.t);

          vec3 N = unit_vector(cross(vertex_b - vertex_a, vertex_c - vertex_a));
          for (int i = 0; i < lights.size(); i++) {
            vec3 toLight = unit_vector(lights[i] - hitPoint);
            float returnVector = (std::max(0.0, dot(-N, toLight)));
            buildColor = vec3{ color.x() + returnVector, color.y() + returnVector, color.z() + returnVector };
          }
          return clampToOne(buildColor * unit_vector(color));
        }

        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * vec3(1.0, 1.0, 1.0) + a * vec3(0.5, 0.7, 1.0);
      }
    }
  return color;
}