#pragma once
#include "../header/shader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class Model {
public:
  Shader *shader;
  GLfloat *buffer = nullptr;
  unsigned long long numero_triangulos = 0;
  float angle;
  glm::mat4 modelmat;
  GLuint VAO, VBO, EBO, NVBO;

  Model(std::string OBJ_dir);
  // Model(GLfloat* vertices, GLuint indices);

  void initModel();
  void renderModel(glm::mat4 view, glm::mat4 projection);
  void updateModel(float timeValue);
  void finish();
};
