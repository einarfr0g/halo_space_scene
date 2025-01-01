#include "../header/model.h"
#include "../header/shader.h"
#include "../src/OBJ_reader_function.cpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>

Model::Model(std::string OBJ_dir) {
  obj *modelo = new obj;
  this->buffer = new GLfloat[modelo->indices.size() * 3 * 3];
  uint i = 0;
  numero_triangulos = modelo->indices.size();
  for (auto e : modelo->indices) {
    buffer[i++] = e.index1.v;
    buffer[i++] = e.index1.vt;
    buffer[i++] = e.index1.vn;
    buffer[i++] = e.index2.v;
    buffer[i++] = e.index2.vt;
    buffer[i++] = e.index2.vn;
    buffer[i++] = e.index3.v;
    buffer[i++] = e.index3.vt;
    buffer[i] = e.index3.vn;
  }
  delete modelo;
}

// Model::Model(GLfloat* vertices, GLuint indices){}

void Model::initModel() {

  modelmat = glm::mat4(1.0f);
  shader = new Shader("./shader/cubo_shade.vert", "./shader/cubo_shade.frag");
  // Crear y enlazar el VAO y VBO

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, numero_triangulos * 3 * 3 * sizeof(GLfloat),
               buffer, GL_STATIC_DRAW);

  // Especificar el layout del vertex shader
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                        (GLvoid *)0);

  glEnableVertexAttribArray(0);
}

void Model::updateModel(float timeValue) {
  angle = timeValue * glm::radians(50.0f); // 50 grados por segundo

  modelmat = glm::rotate(
      glm::mat4(1.0), angle,
      glm::vec3(0.0f, 1.0f, 0.0f)); // Rotar alrededor de (0.5, 1.0, 0.0)
}

void Model::renderModel(glm::mat4 view, glm::mat4 projection) {

  shader->use();

  // Enviar las matrices al shader
  shader->setVec3("posCam", glm::vec3(0.0f, 0.0f, -10.0f));
  shader->setMat4x4("model", modelmat);
  shader->setMat4x4("view",
                    glm::lookAt(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0),
                                glm::vec3(0.0, 1.0, 0.0)));
  shader->setMat4x4("projection", projection);

  // Dibujar el cubo
  glBindVertexArray(VAO);
  // glDrawElements(GL_TRIANGLES, indices_vec.size(), GL_UNSIGNED_INT, 0);
}
void Model::finish() {

  shader->terminate();
  delete (shader);

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
}
