#include "Triangle.h"

namespace ObjToStl
{

Triangle::Triangle(const Vec3& vertex1, const Vec3& vertex2, const Vec3& vertex3)
  : m_vertices{ vertex1, vertex2, vertex3 }
  , m_normal{0, 0, 0}
  {
  m_normal = vertex1 * vertex2;
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}