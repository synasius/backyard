#include <cmath>
#include <iostream>
#include <fstream>
#include "sb6.h"

std::string read_file(const char *filePath) {
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if(!fileStream.is_open()) {
        std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

GLuint compile_shaders(void) {
  GLuint vertex_shader;
  GLuint fragment_shader;
  GLuint control_shader;
  GLuint evaluation_shader;
  GLuint program;

  // vertex shader source code
  std::string vs_source = read_file("shader.vs");
  const GLchar* vertex_shader_source = vs_source.c_str();

  std::string fs_source = read_file("shader.fs");
  const GLchar* fragment_shader_source = fs_source.c_str();

  std::string tcs_source = read_file("control_shader.txt");
  const GLchar* control_shader_source = tcs_source.c_str();

  std::string tes_source = read_file("evaluation_shader.txt");
  const GLchar* evaluation_shader_source = tes_source.c_str();

  //std::cerr << control_shader_source << std::endl;
  // Create and compile vertex shader
  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
  glCompileShader(vertex_shader);

  // Create and compile fragment shader
  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
  glCompileShader(fragment_shader);

  // Create and compile tessellation control shader
  control_shader = glCreateShader(GL_TESS_CONTROL_SHADER);
  glShaderSource(control_shader, 1, &control_shader_source, NULL);
  glCompileShader(control_shader);

  evaluation_shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
  glShaderSource(evaluation_shader, 1, &evaluation_shader_source, NULL);
  glCompileShader(evaluation_shader);

  // Create a program, attach shaders to it, and link it
  program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, control_shader);
  glAttachShader(program, evaluation_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);

  // Delete the shaders as the program has them now
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
  glDeleteShader(control_shader);
  glDeleteShader(evaluation_shader);

  return program;
}

class my_application: public sb6::application
{
public:
  void startup()
  {
    rendering_program = compile_shaders();

    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }

  void shutdown()
  {
    glDeleteVertexArrays(1, &vertex_array_object);
    glDeleteProgram(rendering_program);
  }

  void render(double currentTime)
  {
    static const GLfloat backgroundColor[] = {0.0f, 0.25f, 0.0f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, backgroundColor);

    // Use the program object we created earlier for rendering;
    glUseProgram(rendering_program);
    glDrawArrays(GL_PATCHES, 0, 3);
  }

private:
  GLuint rendering_program;
  GLuint vertex_array_object;

};

DECLARE_MAIN(my_application)
