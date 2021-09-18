#include "atkui/framework.h"
#include <iostream>

using namespace std;
using namespace glm;

class Particles : public atkui::Framework
{
  struct Particle{
  vec3 color;
  vec3 currPos;
  //vec3 speed;
  float duration;
};
 public:
  Particles() : atkui::Framework(atkui::Orthographic) {
  }

  virtual void setup() {
    //arr= {};
    //p1=agl::randomUnitVector();
    for(int i=0;i<250;i++){
      arr[i]={agl::randomUnitVector(), agl::randomUnitVector(), ((float)(rand()%60+1))};
     
      arr[i].currPos.x=(rand()%200+1)*abs(arr[i].currPos.x);
      arr[i].currPos.y=(rand()%200+1)*abs(arr[i].currPos.y);
      arr[i].currPos.z=0;
       cout << arr[i].currPos ;
      //cout << "Hello";
    }

  }

  virtual void scene() {
    for(int i=0;i<250;i++){
      setColor(arr[i].color);
      float t = elapsedTime()/arr[i].duration;
      if(arr[i].currPos.x>=width()||arr[i].currPos.y>=height()){
           arr[i].currPos=agl::randomUnitVector();
           arr[i].currPos.x=0;
           arr[i].currPos.y=(rand()%200+1)*abs(arr[i].currPos.y);
           arr[i].currPos.z=0;
        }
      
      arr[i].currPos=(1-t) * arr[i].currPos+ t * p1;
      
      drawSphere(arr[i].currPos, 15);
      //setColor(vec3(1, 1, 1));
      //drawSphere(vec3(i, i, i), 1);
    }
     
  }
  private:
  vec3 p1=vec3(500, 250, 0);
  float rad=3;
  Particle arr[250]={};
};

int main(int argc, char** argv) {
  Particles viewer;
  viewer.run();
  return 0;
}
