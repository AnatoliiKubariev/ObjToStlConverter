#pragma once

#include "Triangle.h"
#include <vector>
#include <istream>

namespace ObjToStl
{
using Model3D = std::vector<Triangle>;

Model3D Get3DModelFromObj(std::istream& i_stream);

void Write3DModelToStl(const Model3D& model_3d, std::ostream& o_stream );
}
