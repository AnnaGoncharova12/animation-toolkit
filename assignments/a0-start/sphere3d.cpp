#include "atkui/framework.h"

using glm::vec3;

class Sphere3D : public atkui::Framework {
 public:
  Sphere3D() : atkui::Framework(atkui::Perspective) {
  }
  virtual void setup(){
     //starting position of the sphere is at origin and not moving
    currentPos = vec3(0, 0, 0);
    velocity = vec3(0, 0, 0);
  }

  virtual void scene() {
    // colors are RGB triplets in range [0,1]
    setColor(vec3(0,1,0));
    //calculate next position
    currentPos = currentPos + velocity * dt();
    // draw a sphere at center of the world
    float radius = 50.0;
    drawSphere(currentPos, radius);
  }
  virtual void keyUp(int key, int mods){
     if(key == GLFW_KEY_SPACE){
        //update speed to a random value
        velocity = agl::randomUnitVector();
        velocity = velocity*50.0f;
     }
     else if(key == GLFW_KEY_R){
        //reverse to starting position
        currentPos = vec3(0, 0, 0);
        velocity = vec3(0, 0, 0);
     }
  }
  private:
  //position and velocity variables
   vec3 currentPos;
   vec3 velocity;
};

int main(int argc, char** argv)
{
  Sphere3D viewer;
  viewer.run();
  return 0;
}
