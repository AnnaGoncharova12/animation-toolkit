#include "atkui/framework.h"

using glm::vec3;

class Sphere2D : public atkui::Framework {
 public:
  Sphere2D() : atkui::Framework(atkui::Orthographic) {
  }

  virtual void scene() {
    // colors are RGB triplets in range [0,1]
    

    // draw a sphere at center of screen
    double x = width() * 0.5;
    double y = height() * 0.5;
    double radius = 100; 

    //draw smaller green sphere with increased z value first   
    setColor(vec3(0,1,0));
    drawSphere(vec3(x,y,100), radius);

    //draw bigger red sphere aftewards with a smaller z value
    setColor(vec3(1,0,0));
    drawSphere(vec3(x,y,0), radius*2);
 
    
  }
};

int main(int argc, char** argv)
{
  Sphere2D viewer;
  viewer.run();
  return 0;
}
