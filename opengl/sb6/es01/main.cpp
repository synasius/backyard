#include <cmath>
#include "sb6.h"

class my_application: public sb6::application
{
public:
  void render(double currentTime)
  {
    float t = static_cast<float>(currentTime);
    const GLfloat red[] = {
      std::sin(t) * 0.5f + 0.5f,
      std::cos(t) * 0.5f + 0.5f,
      0.0f, 1.0f
    };
    glClearBufferfv(GL_COLOR, 0, red);
  }
};

DECLARE_MAIN(my_application)
