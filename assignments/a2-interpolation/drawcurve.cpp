#include <iostream>
#include "atkui/framework.h"
using namespace glm;

class DrawCubic : public atkui::Framework
{
 public:
  DrawCubic() : atkui::Framework(atkui::Orthographic, 400, 400) {
  }

  virtual void scene()
  {
    setColor(vec3(0,0,1));
    drawSphere(B0, 10);
    drawSphere(B3, 10);

    setColor(vec3(1,1,0));
    drawSphere(B1, 10);
    drawSphere(B2, 10);

    vec3 blue=vec3(0,0,1);
    setColor(blue);
    //Bezier
    if(state==1){
      float currTime=elapsedTime();
      //float t=currTime/timeToDraw;
     
      for(float t=0;t<=1;t+=0.01){
          vec3 p=((float)pow(1-t, 3.0))*B0+3*t*((float)pow(1-t, 2.0))*B1+3*((float)pow(t, 2.0))*(1-t)*B2+((float)pow(t, 3.0))*B3;
         
          drawLine(currPos, p);
          currPos=p;
      }
      currPos = B0;
      
    }
    //use Castlejau's
    else if(state==2){
      for(float t=0;t<=1;t+=0.01){
        //level 1
        vec3 B01 = LERP(B0, B1, t);
        vec3 B11 = LERP(B1, B2, t);
        vec3 B21 = LERP(B2, B3, t);
        //level2
        vec3 B02 = LERP(B01, B11, t);
        vec3 B12 = LERP(B11, B21, t);
        //level3
        vec3 B03 = LERP(B02, B12, t);
        vec3 p = B03;

        drawLine(currPos, p);
        currPos=p;

      }
      currPos = B0;
    }
  }

  void keyUp(int key, int mod) {
    if (key == GLFW_KEY_1) {
      state=1;
    }
    else if (key == GLFW_KEY_2) {
      // draw Casteljau
      state=2;
    }
  }
  vec3 LERP(vec3 p1, vec3 p2, float t){
   vec3 res=p1*(1-t)+p2*t;
   return res;
  }

 private:
  vec3 B0 = vec3(100,  50, 0);
  vec3 B1 = vec3(150, 200, 0);
  vec3 B2 = vec3(250, 100, 0);
  vec3 B3 = vec3(300, 300, 0);
  vec3 currPos = B0;
  float timeToDraw=1;
  float state=0;
};

int main(int argc, char **argv) {
  DrawCubic viewer;
  viewer.run();
}
