#pragma once
#include "model.h"

class Model_with_texture : public Model {
  void load_texture(std::string texture_dir);
  void send_loaded_texture();
  Model_with_texture(std::string obj_dir);
  void initModel();
};
