#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <array>
#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <map>
#include <vector>

class OBJ_reader {
public:
  std::map<std::string, std::vector<float>> model_buffers;
  int EBO_size;
  int VBO_size;
  OBJ_reader(std::string OBJ_dir);
};
