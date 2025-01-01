#pragma once
#include <GL/eglew.h>
#include <fstream>
#include <iostream>
#include <pthread.h>
#include <string>
#include <vector>

// struct para regresar un vector en las funciones
struct vec_float3 {
  GLfloat x;
  GLfloat y;
  GLfloat z;
};

/*funcion para leer una linea de tipo vector
 * @params vector_line linea de el vector
 * @return struct vec_float3 con el vector de GLfloats
 */
vec_float3 read_vec3(std::string vector_line) {

  uint aux_index;

  GLfloat x, y, z;

  aux_index = vector_line.find(" ");

  vector_line.erase(0, aux_index + 1);
  // x
  aux_index = vector_line.find(" ");

  x = stod(vector_line.substr(0, aux_index));

  vector_line.erase(0, aux_index + 1);

  // y
  aux_index = vector_line.find(" ");

  y = stod(vector_line.substr(0, aux_index));

  vector_line.erase(0, aux_index + 1);

  // z
  aux_index = vector_line.find(" ");

  z = stod(vector_line.substr(0, aux_index));

  vec_float3 vec;

  vec.x = x;

  vec.y = y;

  vec.z = z;

  return vec;
}

// struct para regresar un vector de 2 GLfolats (para los vectores de texturas)
struct vec_float2 {
  GLfloat x;
  GLfloat y;
};

/*Función par leer una linea de un vector de dos números floatantes
 *@param std::string vector_line la linea en que se encuentra el vector
 *@return vec_float2 struct de un vector de 2 GLfloats
 */
vec_float2 read_vec2(std::string vector_line) {

  uint aux_index;

  GLfloat x, y;

  aux_index = vector_line.find(" ");

  vector_line.erase(0, aux_index + 1);
  // x
  aux_index = vector_line.find(" ");

  x = stod(vector_line.substr(0, aux_index));

  vector_line.erase(0, aux_index + 1);

  // y
  aux_index = vector_line.find(" ");

  y = stod(vector_line.substr(0, aux_index));

  vector_line.erase(0, aux_index + 1);

  vec_float2 vec;

  vec.x = x;

  vec.y = y;

  return vec;
}

// struct para regresar indices en la funcion read_indices
struct vec_index {
  GLuint v;
  GLuint vt;
  GLuint vn;
  bool there_are_textures = true;
};
// struct para una linea entera de indices
struct vec_indices {
  vec_index index1;
  vec_index index2;
  vec_index index3;
};

/*Función que le una subtring del tipo uint/uint/uint o uint//uint indices de un
 *obj
 *@param std::string index_string substring donde está el indice
 *@return vec_index struct que contiene la información de un indice
 */
vec_index read_index(std::string index_string) {

  std::string::size_type aux_index;

  GLfloat x, y, z;

  vec_index index;

  // x
  aux_index = index_string.find("/");

  if (aux_index == std::string::npos) {
    std::cout << "Modelo contiene indices de tipo no admitido" << "\n";
    return index;
  }

  std::string string_aux;

  aux_index = index_string.find("/");

  string_aux = index_string.substr(0, aux_index);

  x = std::stoul(string_aux);

  // std::cout << "entró v" << "\n";

  // ver si hay vector de texturas
  if (aux_index + 1 == index_string.find("/", aux_index + 1)) {
    // z
    index.there_are_textures = false;

    aux_index += 2;

    string_aux = index_string.substr(aux_index, index_string.size());

    z = std::stoul(string_aux);
  } else {
    // y

    index.there_are_textures = true;

    index_string.erase(0, aux_index + 1);

    aux_index = index_string.find("/");

    string_aux = index_string.substr(0, aux_index);

    y = std::stoul(index_string);

    index_string.erase(0, aux_index + 1);

    // z
    z = std::stoul(index_string);
  }

  index.v = x;
  index.vt = y;
  index.vn = z;

  return index;
}

/*función que lee las lineas de indices y regresar una struct con la información
 *@param std::string indices_line el renglon
 *@retrun vec_index struct con la información
 */
vec_indices read_indices(std::string indices_line) {

  // std::cout << "pasó un indice" << "\n";
  vec_index index_aux;

  std::string aux_string;

  vec_indices result;

  // std::cout << "La linea es " << indices_line << "\n";

  std::string::size_type pivot_index;

  indices_line.erase(0, 2);

  // index1
  pivot_index = indices_line.find(" ");

  aux_string = indices_line.substr(0, pivot_index);

  // std::cout << "La string1 es: " << aux_string << "\n";

  result.index1 = read_index(aux_string);

  indices_line.erase(0, pivot_index + 1);

  // index2
  pivot_index = indices_line.find(" ");

  aux_string = indices_line.substr(0, pivot_index);

  // std::cout << "La string2 es: " << aux_string << "\n";

  result.index2 = read_index(aux_string);

  indices_line.erase(0, pivot_index + 1);

  // index3
  aux_string = indices_line.substr(0, indices_line.size());

  // std::cout << "La string3 es: " << aux_string << "\n";

  result.index3 = read_index(aux_string);

  return result;
}

struct obj {
  std::vector<GLfloat> points;
  std::vector<GLfloat> normals;
  std::vector<GLfloat> textures;
  std::vector<vec_indices> indices;
  bool are_textures;
};

obj read_obj(std::string obj_dir) {
  std::ifstream obj_file(obj_dir);

  if (!obj_file.is_open())
    std::cout << "error al abrir el archivo" << "\n";

  std::string line;
  vec_float2 vec2_aux;
  vec_float3 vec3_aux;
  obj result;
  bool indices_type = false;

  while (!obj_file.eof()) {
    std::getline(obj_file, line);

    if (line == "")
      continue;
    else if (line[0] == 'v' && line[1] == ' ') {
      vec3_aux = read_vec3(line);
      result.points.push_back(vec3_aux.x);
      result.points.push_back(vec3_aux.y);
      result.points.push_back(vec3_aux.z);
    } else if (line[0] == 'v' && line[1] == 'n') {
      vec3_aux = read_vec3(line);
      result.normals.push_back(vec3_aux.x);
      result.normals.push_back(vec3_aux.y);
      result.normals.push_back(vec3_aux.z);
    } else if (line[0] == 'v' && line[1] == 't') {
      vec2_aux = read_vec2(line);
      result.textures.push_back(vec2_aux.y);
      result.textures.push_back(vec2_aux.y);
    } else if (line[0] == 'f') {
      result.indices.push_back(read_indices(line));
      if (indices_type == false) {
        indices_type = true;
        result.are_textures = read_indices(line).index1.there_are_textures;
      }
    }
  }
  return result;
}
