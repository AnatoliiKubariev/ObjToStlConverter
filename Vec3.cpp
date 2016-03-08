#include "Vec3.h"

namespace ObjToStl
{

Vec3 operator*(const Vec3& lhs, const Vec3& rhs)
  {
  return Vec3{ lhs.y * rhs.z - lhs.z * rhs.y
             , lhs.z * rhs.x - lhs.x * rhs.z
             , lhs.x * rhs.y - lhs.y * rhs.x };
  }

}