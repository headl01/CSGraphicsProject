#pragma once
#include <cmath>
#include <iostream>

class vec3
{
public:
  double e[3];

  vec3() : e{ 0, 0, 0 } {}
  vec3(double e0, double e1, double e2) : e{ e0, e1, e2 } {}

  double x() const { return e[0]; }
  double y() const { return e[1]; }
  double z() const { return e[2]; }

  vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
  double operator[](int i) const { return e[i]; }
  double &operator[](int i) { return e[i]; }

  vec3 &operator+=(const vec3 &v)
  {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
  }

  vec3 &operator*=(double t)
  {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
  }

  vec3 &operator/=(double t)
  {
    return *this *= 1 / t;
  }

  double length() const
  {
    return std::sqrt(length_squared());
  }

  double length_squared() const
  {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
  }
};

// point3 is just an alias for vec3, but useful for geometric clarity in the code.
using point3 = vec3;


// Vector Utility Functions

inline std::ostream &operator<<(std::ostream &out, const vec3 &v)
{
  return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline bool operator==(const vec3 &u, const vec3 &v)
{
  return u.e[0] == v.e[0] 
      && u.e[1] == v.e[1] 
      && u.e[2] == v.e[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v)
{
  return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v)
{
  return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v)
{
  return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3 &v)
{
  return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3 &v, double t)
{
  return t * v;
}

inline vec3 operator/(const vec3 &v, double t)
{
  return (1 / t) * v;
}

inline double dot(const vec3 &u, const vec3 &v)
{
  return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v)
{
  return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
    u.e[2] * v.e[0] - u.e[0] * v.e[2],
    u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(const vec3 &v)
{
  return v / v.length();
}

// bounding function, kinda ugly, fix later 
inline vec3 clampToOne(vec3 v)
{
  for (int i = 0; i < 3; i++) {
    if (v.e[i] < 0) v.e[i] = 0;
    if (v.e[i] > 1) v.e[i] = 1;
  }
  return v;
}


inline vec3 clampToN(vec3 v, float n)
{
  for (int i = 0; i < 3; i++) {
    if (v.e[i] < 0) v.e[i] = 0;
    if (v.e[i] > n) v.e[i] = n;
  }
  return v;
}


inline vec3 constLerp(vec3 c1, vec3 c2, float t) {
  return (1.0 - t) * c1 + t * c2;
 
}

/*
vec3 columnarLerp(vec3 c1, vec3 c2, float pixel)
{

}

vec3 rowLerp(vec3 c1, vec3 c2, float pixel)
{
}
*/

inline vec3 toRGB(vec3 v) {
  return v*255;
}
