#include <cmath>
#include "sb6.h"

GLuint compile_shaders(void) {
  GLuint vertex_shader;
  GLuint fragment_shader;
  GLuint program;

  // vertex shader source code
  static const GLchar* vertex_shader_source[] =
  {
    "#version 430 core                             \n"
    "                                              \n"
    "void main(void)                               \n"
    "{                                             \n"
    "  gl_Position = vec4(0.0, 0.0, 0.5, 1.0);     \n"
    "}                                             \n"
  };

  // fragment shader source code
  static const GLchar* fragment_shader_source[] =
  {
    "#version 430 core                             \n"
    "                                              \n"
    "out vec4 color;                               \n"
    "                                              \n"
    "void main(void)                               \n"
    "{                                             \n"
    "  color = vec4(0.0, 0.8, 1.0, 1.0);           \n"
    "}                                             \n"
  };

  // Create and compile vertex shader
  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
  glCompileShader(vertex_shader);

  // Create and compile fragment shader
  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
  glCompileShader(fragment_shader);

  // Create a program, attach shaders to it, and link it
  program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);

  // Delete the shaders as the program has them now
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

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
  }

  void shutdown()
  {
    glDeleteVertexArrays(1, &vertex_array_object);
    glDeleteProgram(rendering_program);
  }

  void render(double currentTime)
  {
    float t = static_cast<float>(currentTime);
    const GLfloat red[] = {
      std::sin(t) * 0.5f + 0.5f,
      std::cos(t) * 0.5f + 0.5f,
      0.0f, 1.0f
    };
    glClearBufferfv(GL_COLOR, 0, red);

    // Use the program object we created earlier for rendering;
    glUseProgram(rendering_program);

    // Draw one point
    glDrawArrays(GL_POINTS, 0, 1);
    glPointSize(40.0f);
  }

private:
  GLuint rendering_program;
  GLuint vertex_array_object;

};

DECLARE_MAIN(my_application)
