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
    "// offset is an input vertext attribute       \n"
    "// location is the index value to use         \n"
    "// in the glVertexAttribr function            \n"
    "layout (location = 0) in vec4 offset;         \n"
    "                                              \n"
    "void main(void)                               \n"
    "{                                             \n"
    "  // Declare a hard-coded array of positions  \n"
    "  const vec4 vertices[3] = vec4[3](           \n"
    "    vec4( 0.25, -0.25, 0.5, 1.0),             \n"
    "    vec4(-0.25, -0.25, 0.5, 1.0),             \n"
    "    vec4( 0.25,  0.25, 0.5, 1.0)              \n"
    "  );                                          \n"
    "                                              \n"
    "  // Index into our array using gl_VertexID   \n"
    "  gl_Position = vertices[gl_VertexID] +       \n"
    "                offset;                       \n"
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
    static const GLfloat color[] = {0.5f, 0.0f, 0.0f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, color);

    // Use the program object we created earlier for rendering;
    glUseProgram(rendering_program);

    float t = static_cast<float>(currentTime);
    GLfloat attrib[] = {std::sin(t) * 0.5f, std::cos(t) * 0.6f, 0.0f, 0.0f};

    // Update the value of input attribute 0
    glVertexAttrib4fv(0, attrib);

    // Draw one triangle
    glDrawArrays(GL_TRIANGLES, 0, 3);
  }

private:
  GLuint rendering_program;
  GLuint vertex_array_object;

};

DECLARE_MAIN(my_application)
