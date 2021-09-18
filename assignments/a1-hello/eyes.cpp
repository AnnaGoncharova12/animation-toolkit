#include "atkui/framework.h"

using namespace glm;
class Eyes : public atkui::Framework
{
  public:
    Eyes() : atkui::Framework(atkui::Orthographic) {
    }

    virtual void scene() {
      
      double x = 110  ;
      double x1 = 250 ;
      double y = height() * 0.5;
      double radius = 10;
      double xEye=110+(radius*5*sin(elapsedTime()));
      double x1Eye=250+(radius*5*sin(elapsedTime()));
      setColor(vec3(0, 1, 0 ));
      drawSphere(vec3(xEye,y,100), radius*2);
      drawSphere(vec3(x1Eye,y,100), radius*2);
      setColor(vec3(1, 1, 1));
      drawSphere(vec3(x,y,0), radius*12);
      drawSphere(vec3(x1,y,0), radius*12);
      //drawSphere(vec3(x1,y,100), radius);
       



    }
};

int main(int argc, char** argv) {
  Eyes viewer;
  viewer.run();
  return 0;
}
