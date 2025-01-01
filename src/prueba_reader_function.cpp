#include "../header/model.h"

int main() {
  Model model("blender_default_cube.obj");
  std::cout << "Los vertices son :" << "\n";
  int contador = 0;
  for (auto num : model.vertices_vec) {
    std::cout << num << " ";
    if (contador == 2) {
      std::cout << "\n";
      contador = 0;
    } else {
      contador++;
    }
  }
  contador = 0;
  std::cout << "\n" << "Los indices son:" << "\n";
  for (auto num : model.indices_vec) {
    std::cout << num << " ";
    if (contador == 3) {
      std::cout << "\n";
      contador = 0;
    } else {
      contador++;
    }
  }
  contador = 0;
  std::cout << "\n" << "Las normales son:" << "\n";
  for (auto num : model.normales_vec) {
    std::cout << num << " ";
    if (contador == 2) {
      std::cout << "\n";
      contador = 0;
    } else {
      contador++;
    }
  }
}
