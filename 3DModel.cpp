#include "3DModel.h"

#include "Triangle.h"
#include "Vec3.h"
#include <string>
#include <sstream>
#include <ostream>

namespace ObjToStl
{
using Face = std::vector<int>;
Vec3 GetVertex(std::istringstream& str_stream);
Face GetFace(std::istringstream& str_stream);
std::vector<Triangle> Triangulate(const std::vector<Vec3>& vertices, const Face& face);

void Write3DModelToStl(const Model3D& model_3d, std::ostream& o_stream)
  {
  for(auto& t : model_3d)
    {
    o_stream << "facet normal " << t.m_normal.x << " " << t.m_normal.x << " " << t.m_normal.x << std::endl;
    o_stream << " outer loop" << std::endl;
    for(auto& v : t.m_vertices)
      {
      o_stream << "  vertex " << v.x << " " << v.y << " " << v.z << std::endl;
      }
    o_stream << " endloop" << std::endl;
    o_stream << "endfacet" << std::endl;
    o_stream << std::endl;
    }
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Model3D Get3DModelFromObj(std::istream& i_stream)
  {
  std::vector<Vec3> vertices;
  std::vector<Face> faces;
  while(!i_stream.eof())
    {
    std::string line;
    std::getline(i_stream, line);
    std::istringstream str_stream(line);
    std::string type;
    str_stream >> type;
    if(type == "v")
      {
      vertices.push_back(GetVertex(str_stream));
      }
    else if(type == "f")
      {
      faces.push_back(GetFace(str_stream));
      }
    }

  Model3D model_3d;
  for(auto& f : faces)
    {
    std::vector<Triangle> temp_triangles = Triangulate(vertices, f);
    model_3d.insert(model_3d.end(), temp_triangles.begin(), temp_triangles.end());
    }
  return model_3d;
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<Triangle> Triangulate(const std::vector<Vec3>& vertices, const Face& face)
  {
  if(face.size() == 3)
    {
    return{ Triangle(vertices[face[0]], vertices[face[1]], vertices[face[2]]) };
    }

  std::vector<Triangle> triangulated;
  for(auto i = 1; i <= face.size() - 2; ++i)
    {
    triangulated.push_back(Triangle{ vertices[face[0]], vertices[face[i]], vertices[face[i + 1]] });
    }
  return triangulated;
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Vec3 GetVertex(std::istringstream& str_stream)
  {
  Vec3 vertex;
  std::string temp_str;

  str_stream >> temp_str;
  vertex.x = std::stod(temp_str);
  str_stream >> temp_str;
  vertex.y = std::stod(temp_str);
  str_stream >> temp_str;
  vertex.z = std::stod(temp_str);

  return vertex;
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Face GetFace(std::istringstream& str_stream)
  {
  Face face;
  std::string temp_str;
  while(!str_stream.eof())
    {
    str_stream >> temp_str;
    std::replace(temp_str.begin(), temp_str.end(), '/', ' ');
    face.push_back(std::stoi(temp_str) - 1);
    }
  return face;
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}