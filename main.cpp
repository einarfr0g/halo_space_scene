#include "./header/model.h"
#include "./header/ventana.h"
#include <iostream>

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
  std::cout << "ingresa el la dirección del OBJ" << "\n";
  std::cin >> OBJ_dir;
  model = new Model(OBJ_dir);
  ventana->initModels(model);
  ventana->initViewProyection();
}

int main() {

  init();
  ventana->render();
  finish();

  return 0;
}
