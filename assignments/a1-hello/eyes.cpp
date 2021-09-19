#include "atkui/framework.h"

using namespace glm;
class Eyes : public atkui::Framework
{
  public:
    Eyes() : atkui::Framework(atkui::Orthographic) {
    }
    virtual void setup() {
      //set up sphere coordinates and base radius
      x1 = 110 ;
      x2 = 250;
      y = height() * 0.5;
      radius = 10;
  }
    virtual void scene() {
      //specify eye movement logic
      double x1Eye=110+(radius*5*sin(elapsedTime()));
      double x2Eye=250+(radius*5*sin(elapsedTime()));

      setColor(vec3(0, 1, 0 ));
      drawSphere(vec3(x1Eye,y,100), radius*2);
      drawSphere(vec3(x2Eye,y,100), radius*2);
      setColor(vec3(1, 1, 1));
      drawSphere(vec3(x1,y,0), radius*12);
      drawSphere(vec3(x2,y,0), radius*12);
    }
    private:
      double x1;
      double x2;
      double y;
      double radius;
    };
int main(int argc, char** argv) {
  Eyes viewer;
  viewer.run();
  return 0;
}
