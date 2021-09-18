#include "atkui/framework.h"

using namespace glm;

class Look : public atkui::Framework {
 public:
  Look() : atkui::Framework(atkui::Orthographic) {
  }

  virtual void setup() {
    _mouseX = width() * 0.5;
    _mouseY = height() * 0.5;
  }

  virtual void scene() {
    double x = 110  ;
      double x1 = 250 ;
      double y = height() * 0.5;
      double radius = 10;
      double xEye=110;
      double x1Eye=250;
      setColor(vec3(0, 1, 0 ));
      drawSphere(vec3(xEye,y,100), radius*2);
      drawSphere(vec3(x1Eye,y,100), radius*2);
      setColor(vec3(1, 1, 1));
      drawSphere(vec3(x,y,0), radius*12);
      drawSphere(vec3(x1,y,0), radius*12);

    vec3 target = vec3(_mouseX, _mouseY, 0);
    setColor(vec3(1,0,0));
    drawSphere(target, 5);
  }

  void mouseMove(int x, int y) {
    _mouseX = x;
    _mouseY = height() - y;
  }

 private:
  int _mouseX;
  int _mouseY;
};

int main(int argc, char** argv) {
  Look viewer;
  viewer.run();
  return 0;
}
