#include <iostream>
#include "atkui/framework.h"
using namespace glm;
using namespace std;
class Gradient : public atkui::Framework {
 public:
  Gradient() : atkui::Framework(atkui::Orthographic) {
  }
    virtual void setup() {
      x=width();
      y=height();
      N=30;
      rows=y/N;
      cols=x/N;

    }
  virtual void scene() {
    for(int i=0;i<rows;i++){
      int posY=(i)*N;
      for(int j=0;j<cols;j++){
        //first round interpolation
        float tX=((float)(j*N)/(float)x);
        vec3 Cx0=NW*(1-tX)+NE*tX;
        vec3 Cx1=SW*(1-tX)+SE*tX;
        //second round interpolation
       
        float tY=((float)(i*N)/(float)y);
        
        vec3 C=Cx1*(1-tY)+Cx0*tY;
        
        
        setColor(C);
        drawCube(vec3(j*N, posY, 0),vec3(N, N, 0) );
        //drawSphere(vec3(j*N, posY, 0), 4);

      }
    }

  }
  private:
  vec3 NW = vec3(1,1,0);
  vec3 NE = vec3(0,1,1);
  vec3 SW = vec3(1, 0, 0);
  vec3 SE = vec3(1, 0, 1);
  int x;
  int y;
  int N;
  int rows;
  int cols;

};

int main(int argc, char **argv) {
  Gradient viewer;
  viewer.run();
}
