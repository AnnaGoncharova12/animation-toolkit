#include "atkui/framework.h"

using namespace glm;

class Unique : public atkui::Framework {
 public:
 struct Bubble{
   vec3 color;
   vec3 currPos;
   float rad;
   float maxRad;
 };
  Unique() : atkui::Framework(atkui::Orthographic) {
  }

  virtual void setup() {
    float colGap=100;
    float start=100;
    for(int i=0;i<4;i++){
      //random size
      float rad =rand()%20+5;
      //space out bubbles
      float gap=2*rad;
      float y=0;
      for(int j=0;j<8;j++){
        gap=max(2*rad, gap);
        y+=gap;
        bubbles[i][j]={agl::randomUnitVector(),vec3(start, y, 0), rad, rad };
        gap=2*rad;
        rad =rand()%20+5;
     }
     start+=colGap;
    }
  }

  virtual void scene() {
    for(int i=0;i<4;i++){
      for(int j=0;j<8;j++){
        //varying the red color component
        bubbles[i][j].color.x+=(sin(elapsedTime())*0.1);
        setColor(bubbles[i][j].color);
        bubbles[i][j].currPos.y+=speed[i];
        //add variation to size
        bubbles[i][j].rad=bubbles[i][j].maxRad-(bubbles[i][j].maxRad*abs(sin(elapsedTime()))*0.5);
        //wrap bubbles around
        if(bubbles[i][j].currPos.y>height()){
          bubbles[i][j].currPos.y=2*bubbles[i][j].maxRad;
        }
        drawSphere(bubbles[i][j].currPos, bubbles[i][j].rad);
     }
    }
  }
  private:
  //4 streams of rising bubbles at different speeds
  Bubble bubbles[4][8]={};
  float speed[4]={rand()%10+1, rand()%10+1, rand()%10+1, rand()%10+1};
};

int main(int argc, char** argv) {
  Unique viewer;
  viewer.run();
  return 0;
}

