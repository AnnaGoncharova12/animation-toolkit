#include "atkui/framework.h"

using glm::vec3;

class Sphere3D : public atkui::Framework {
 public:
  Sphere3D() : atkui::Framework(atkui::Perspective) {
  }
  virtual void setup(){
    currentPos= vec3(0, 0, 0);
    velocity = vec3(0, 0, 0);
  }

  virtual void scene() {
    // colors are RGB triplets in range [0,1]
    setColor(vec3(0,1,0));
    currentPos = currentPos + velocity * dt();
    // draw a sphere at center of the world
    float radius = 50.0;
    drawSphere(currentPos, radius);
  }
  virtual void keyUp(int key, int mods){
     if(key == GLFW_KEY_SPACE){
        velocity=25.0f * agl::randomUnitVector();
     }
     else if(key == GLFW_KEY_R){
        currentPos= vec3(0, 0, 0);
        velocity = vec3(0, 0, 0);
     }
  }
  private:
   vec3 currentPos;
   vec3 velocity;
};

int main(int argc, char** argv)
{
  Sphere3D viewer;
  viewer.run();
  return 0;
}
