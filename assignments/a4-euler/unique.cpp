#include "atkui/framework.h"
#include "atkmath/matrix3.h"
#include "atkmath/vector3.h"
using namespace atkmath;
using namespace glm;

class Unique : public atkui::Framework {
 
public:
//a struct that holds all the necessary information to draw a moving particle
   struct Cone{
   vec3 color;
   vec3 currPos;
   float theta;
   float size;//radius 
   };
   Unique() : atkui::Framework(atkui::Orthographic) {
   }
    virtual void setup() {/* 	
      //initialize colors
      //https://www.color-hex.com/color-palette/113884
      colorPalette[0]=vec3(244,176,162)/255.0f;
      colorPalette[1]=vec3(235,118,139)/255.0f;
      colorPalette[2]=vec3(232,58,89)/255.0f;
      colorPalette[3]=vec3(197,90,140)/255.0f;
      colorPalette[4]=vec3(135,67,109)/255.0f;

      float size=40;//distance between each circle as well as the first cirlce and the center
      float spacing=0;//30 degrees=0.525 radians
      for(int i=0;i<N;i++){
         vec3 color=colorPalette[i];
         for(int j=0;j<12;j++){
            arr[i][j]={color, vec3(size*cos(spacing)+250, size*sin(spacing)+250, 0), spacing,  size };
            spacing+=0.525;
         }
         size+=40;  
      }
      */
   }
   virtual void scene() {
      
      float angle = elapsedTime()/10.0;
      Matrix3 m = Matrix3();
      m.Matrix3::fromEulerAnglesXYZ(Vector3(angle, angle, angle));
      currPos= operator * ( m, currPos);
      setColor(vec3(1, 0, 0));
      drawTeapot(vec3(currPos.x(), currPos.y(), currPos.z()), 100.0);

      /*
       for(int i=0;i<N;i++){
         for(int j=0;j<12;j++){
            //update angle 
            arr[i][j].theta += (thetaRate) * dt();
            //update particle location
            arr[i][j].currPos.x=arr[i][j].size*cos(arr[i][j].theta)+250;
            arr[i][j].currPos.y=arr[i][j].size*sin(arr[i][j].theta)+250;
            //draw the particle
            setColor(arr[i][j].color);
            drawCube(arr[i][j].currPos, vec3((float)i*10,(float)i*10, (float)i*10));
         }
       }
       */
   }

private:
Vector3 currPos=Vector3(250, 250, 250);
vec3 size=vec3(100.0f, 150.0f, 50.0f);
int N = 4;
Cone arr[4][12] = {};
float thetaRate = 0.1;
float timeToTravel=5.0;
vec3 colorPalette[5] = {};
};
int main(int argc, char** argv) {
  Unique viewer;
  viewer.run();
  return 0;
}
