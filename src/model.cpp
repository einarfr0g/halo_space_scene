#include "../header/model.h"
#include "../header/shader.h"
#include "../header/stb_image.h"
#include "../src/OBJ_reader_function.cpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>

void fil_model_with_textures(obj *modelo, Model *model) {

  uint i = 0;
  for (auto e : modelo->indices) {
    model->buffer[i++] = modelo->points[e.index1.v - 1].x;
    model->buffer[i++] = modelo->points[e.index1.v - 1].y;
    model->buffer[i++] = modelo->points[e.index1.v - 1].z;
    model->buffer[i++] = modelo->normals[e.index1.vn - 1].x;
    model->buffer[i++] = modelo->normals[e.index1.vn - 1].y;
    model->buffer[i++] = modelo->normals[e.index1.vn - 1].z;
    model->buffer[i++] = modelo->textures[e.index1.vt - 1].x;
    model->buffer[i++] = modelo->textures[e.index1.vt - 1].y;
    model->buffer[i++] = modelo->points[e.index2.v - 1].x;
    model->buffer[i++] = modelo->points[e.index2.v - 1].y;
    model->buffer[i++] = modelo->points[e.index2.v - 1].z;
    model->buffer[i++] = modelo->normals[e.index2.vn - 1].x;
    model->buffer[i++] = modelo->normals[e.index2.vn - 1].y;
    model->buffer[i++] = modelo->normals[e.index2.vn - 1].z;
    model->buffer[i++] = modelo->textures[e.index2.vt - 1].x;
    model->buffer[i++] = modelo->textures[e.index2.vt - 1].y;
    model->buffer[i++] = modelo->points[e.index3.v - 1].x;
    model->buffer[i++] = modelo->points[e.index3.v - 1].y;
    model->buffer[i++] = modelo->points[e.index3.v - 1].z;
    model->buffer[i++] = modelo->normals[e.index3.vn - 1].x;
    model->buffer[i++] = modelo->normals[e.index3.vn - 1].y;
    model->buffer[i++] = modelo->normals[e.index3.vn - 1].z;
    model->buffer[i++] = modelo->textures[e.index3.vt - 1].x;
    model->buffer[i++] = modelo->textures[e.index3.vt - 1].y;
  }
}
void fil_model_without_textures(obj *modelo, Model *model) {

  uint i = 0;
  for (auto e : modelo->indices) {
    model->buffer[i++] = modelo->points[e.index1.v - 1].x;
    model->buffer[i++] = modelo->points[e.index1.v - 1].y;
    model->buffer[i++] = modelo->points[e.index1.v - 1].z;
    model->buffer[i++] = modelo->normals[e.index1.vn - 1].x;
    model->buffer[i++] = modelo->normals[e.index1.vn - 1].y;
    model->buffer[i++] = modelo->normals[e.index1.vn - 1].z;
    model->buffer[i++] = 0;
    model->buffer[i++] = 0;
    model->buffer[i++] = modelo->points[e.index2.v - 1].x;
    model->buffer[i++] = modelo->points[e.index2.v - 1].y;
    model->buffer[i++] = modelo->points[e.index2.v - 1].z;
    model->buffer[i++] = modelo->normals[e.index2.vn - 1].x;
    model->buffer[i++] = modelo->normals[e.index2.vn - 1].y;
    model->buffer[i++] = modelo->normals[e.index2.vn - 1].z;
    model->buffer[i++] = 0;
    model->buffer[i++] = 0;
    model->buffer[i++] = modelo->points[e.index3.v - 1].x;
    model->buffer[i++] = modelo->points[e.index3.v - 1].y;
    model->buffer[i++] = modelo->points[e.index3.v - 1].z;
    model->buffer[i++] = modelo->normals[e.index3.vn - 1].x;
    model->buffer[i++] = modelo->normals[e.index3.vn - 1].y;
    model->buffer[i++] = modelo->normals[e.index3.vn - 1].z;
    model->buffer[i++] = 0;
    model->buffer[i++] = 0;
  }
}
Model::Model(std::string OBJ_dir) {
  obj *modelo = read_obj(OBJ_dir);
  this->buffer = new GLfloat[modelo->indices.size() * 3 * 8];
  numero_triangulos = modelo->indices.size();
  has_textures = modelo->are_textures;
  if (has_textures) {
    fil_model_with_textures(modelo, this);
  } else {
    fil_model_without_textures(modelo, this);
  }
  textura = nullptr;

  delete modelo;
}

void Model::initModel() {

  modelmat = glm::mat4(1.0f);
  if (this->has_textures) {
    shader = new Shader("./shader/cubo_shade_textures.vert",
                        "./shader/cubo_shade_textures.frag");
    std::cout << "si entro \n";
  } else {
    shader = new Shader("./shader/cubo_shade.vert", "./shader/cubo_shade.frag");
  }
  // Crear y enlazar el VAO y VBO

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, numero_triangulos * 24 * sizeof(GLfloat),
               buffer, GL_STATIC_DRAW);

  // Especificar el layout del vertex shader
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                        (GLvoid *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                        (GLvoid *)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                        (GLvoid *)(6 * sizeof(GLfloat)));
  glEnableVertexAttribArray(2);
}

void Model::set_textura(const std::string &rutaArchivo) {
  this->textura = new Textura(rutaArchivo);
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
  if (this->has_textures)
    // textura->activar(GL_TEXTURE0, this->shader->ID);
    glDrawArrays(GL_TRIANGLES, 0, numero_triangulos * 24);
  // glDrawElements(GL_TRIANGLES, indices_vec.size(), GL_UNSIGNED_INT, 0);
}
void Model::finish() {

  shader->terminate();
  delete (shader);

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
}
