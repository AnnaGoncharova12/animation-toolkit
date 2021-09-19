#include "atkui/framework.h"

using namespace glm;

class Look : public atkui::Framework {
 public:
  Look() : atkui::Framework(atkui::Orthographic) {
  }

  virtual void setup() {
    //set up sphere coordinates and base radius
    _mouseX = width() * 0.5;
    _mouseY = height() * 0.5;
    x1 = 110 ;
    x2 = 250;
    y = height() * 0.5;
    radius = 10;
  }

  virtual void scene() {
    //update mouse location
      if(mouseIsDown(GLFW_MOUSE_BUTTON_LEFT)){
        mouseMove(mousePosition().x, mousePosition().y);
      }
      //draw target
      vec3 target = vec3(_mouseX, _mouseY, 0);
      setColor(vec3(1,0,0));
      drawSphere(target, 5);

      //rotate left pupil
      vec3 pivot = vec3(x1, y, 0);
      vec3 pPrime = target-pivot;
      float theta = atan2(pPrime.y, pPrime.x);
      vec3 pDoublePrime = vec3(cos(theta), sin(theta), 0);
      pDoublePrime *= radius*4;
      vec3 eyePos = pDoublePrime+pivot;
      setColor(vec3(0, 1, 0));
      drawSphere(eyePos, 10);

      //rotate right eye     
      vec3 pivot2 = vec3(x2, y, 0);
      vec3 pPrime2 = target-pivot2;
      float theta2 = atan2(pPrime2.y, pPrime2.x);
      vec3 pDoublePrime2 = vec3(cos(theta2), sin(theta2), 0);
      pDoublePrime2 *= radius*4;
      vec3 eyePos2=pDoublePrime2+pivot2;
      setColor(vec3(0, 1, 0));
      drawSphere(eyePos2, 10);

      //draw eyeballs
      setColor(vec3(1, 1, 1));
      drawSphere(vec3(x1,y,-100), radius*12);
      drawSphere(vec3(x2,y,-100), radius*12);
    }

  void mouseMove(int x, int y) {
    
    _mouseX = x;
    _mouseY = height() - y;
  }

 private:
  int _mouseX;
  int _mouseY;
  double x1;
  double x2;
  double y;
  double radius;
};

int main(int argc, char** argv) {
  Look viewer;
  viewer.run();
  return 0;
}
