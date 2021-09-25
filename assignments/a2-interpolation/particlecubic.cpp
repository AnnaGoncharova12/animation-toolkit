#include "atkui/framework.h"
using namespace glm;
using namespace std;
class ParticleCubic : public atkui::Framework {
 public:
  ParticleCubic() : atkui::Framework(atkui::Orthographic) {
  }

  void setup() {
    timeToTravel=5.0;
  }

  void scene() {
    setColor(vec3(1,1,0));
    //draw the curve
    for(float t=0;t<=1;t+=0.01){
          vec3 p=((float)pow(1-t, 3.0))*B0+3*t*((float)pow(1-t, 2.0))*B1+3*((float)pow(t, 2.0))*(1-t)*B2+((float)pow(t, 3.0))*B3;
         
          drawLine(currPos, p);
          currPos=p;
      }
    currPos = B0;
    //draw the sphere
    setColor(vec3(1));
    //t that wraps up
    float t = fmod(elapsedTime(), timeToTravel)/timeToTravel;
    vec3 p=((float)pow(1-t, 3.0))*B0+3*t*((float)pow(1-t, 2.0))*B1+3*((float)pow(t, 2.0))*(1-t)*B2+((float)pow(t, 3.0))*B3;
    drawSphere(p, 10);
  }
  private:
  vec3 B0 = vec3(100,  50, 0);
  vec3 B1 = vec3(150, 200, 0);
  vec3 B2 = vec3(250, 100, 0);
  vec3 B3 = vec3(300, 300, 0);
  vec3 currPos = B0;
  vec3 dotPos = B0;
  float timeToTravel;
};

int main(int argc, char** argv) {
  ParticleCubic viewer;
  viewer.run();
}

