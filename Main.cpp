#include "3DModel.h"
#include <fstream>
#include <iostream>

using namespace ObjToStl;

int main(int argc, char* argv[])
  {
  if(argc < 3)
    {
    return -1;
    }

  std::ifstream obj_stream(argv[1]);
  std::ofstream stl_stream(argv[2]);
  const auto model_3d = Get3DModelFromObj(obj_stream);
  Write3DModelToStl(model_3d, stl_stream);

  return 0;
  }