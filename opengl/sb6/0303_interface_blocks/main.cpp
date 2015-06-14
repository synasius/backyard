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
    "// 'offset' and 'color' are input             \n"
    "// vertex attributes                          \n"
    "layout (location = 0) in vec4 offset;         \n"
    "layout (location = 1) in vec4 color;          \n"
    "                                              \n"
    "// Declare VS_OUT as output interface block   \n"
    "out VS_OUT                                    \n"
    "{                                             \n"
    "  vec4 color;                                 \n"
    "} vs_out;                                     \n"
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
    "                                              \n"
    "  // Output a fixed value for vs_color        \n"
    "  vs_out.color = color;                       \n"
    "}                                             \n"
  };

  // fragment shader source code
  static const GLchar* fragment_shader_source[] =
  {
    "#version 430 core                             \n"
    "                                              \n"
    "// Declare VS_OUT as input interface block    \n"
    "in VS_OUT                                     \n"
    "{                                             \n"
    "  vec4 color;                                 \n"
    "} fs_in;                                      \n"
    "                                              \n"
    "// output to the framebuffer                  \n"
    "out vec4 color;                               \n"
    "                                              \n"
    "void main(void)                               \n"
    "{                                             \n"
    "  // assign the color from the vs to output   \n"
    "  color = fs_in.color;                        \n"
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
    static const GLfloat backgroundColor[] = {0.5f, 0.0f, 0.0f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, backgroundColor);

    // Use the program object we created earlier for rendering;
    glUseProgram(rendering_program);

    float t = static_cast<float>(currentTime);
    GLfloat offset[] = {std::sin(t) * 0.5f, std::cos(t) * 0.6f, 0.0f, 0.0f};
    GLfloat color[] = {std::sin(t) * 0.5f, std::cos(t) * 0.5f, 0.0f, 1.0f};

    // Update the value of input attributes
    glVertexAttrib4fv(0, offset);
    glVertexAttrib4fv(1, color);

    // Draw one triangle
    glDrawArrays(GL_TRIANGLES, 0, 3);
  }

private:
  GLuint rendering_program;
  GLuint vertex_array_object;

};

DECLARE_MAIN(my_application)
