#define STB_IMAGE_IMPLEMENTATION
#include "./header/model.h"
#include "./header/ventana.h"

Ventana *ventana;
Model *model;

void finish() {
  glfwTerminate();
  delete (model);
  delete (ventana);
}

void init() {
  ventana = new Ventana(600, 600);
  // Inicializar GLFW
  ventana->initGLFW();
  // Inicializar GLEW
  ventana->initGLEW();
  std::string OBJ_dir;
  // std::cout << "ingresa el la dirección del OBJ" << "\n";
  // std::cin >> OBJ_dir;
  model = new Model("jupiter.obj");
  model->set_textura("Jupiter.jpg");
  std::cout << "textura? " << model->has_textures << "\n";
  ventana->initModels(model);
  ventana->initViewProyection();
}

int main() {

  init();
  ventana->render();
  finish();

  return 0;
}
