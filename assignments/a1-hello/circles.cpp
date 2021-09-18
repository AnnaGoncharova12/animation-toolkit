#include "atkui/framework.h"

using namespace glm;
class Circles : public atkui::Framework
{
public:
//a struct that holds all the necessary information to draw a moving particle
   struct Particle{
   vec3 color;
   vec3 currPos;
   float theta;
   float circleRad;//radius 
   };
   Circles() : atkui::Framework(atkui::Orthographic) {
   }

   virtual void setup() { 	
      //initialize colors
      //https://www.color-hex.com/color-palette/113884
      colorPalette[0]=vec3(244,176,162)/255.0f;
      colorPalette[1]=vec3(235,118,139)/255.0f;
      colorPalette[2]=vec3(232,58,89)/255.0f;
      colorPalette[3]=vec3(197,90,140)/255.0f;
      colorPalette[4]=vec3(135,67,109)/255.0f;

      float circleRad=40;//distance between each circle as well as the first cirlce and the center
      float spacing=0;//10 degrees=0.175 radians
      for(int i=0;i<N;i++){
         vec3 color=colorPalette[i];
         for(int j=0;j<36;j++){
            arr[i][j]={color, vec3(circleRad*cos(spacing)+250, circleRad*sin(spacing)+250, 0), spacing,  circleRad };
            spacing+=0.175;
         }
         circleRad+=40;   
      }
   }

   virtual void scene() {
       for(int i=0;i<N;i++){
         for(int j=0;j<36;j++){
            //update angle based on the cirlce number parity
            arr[i][j].theta += (i%2==0?thetaRateEven:thetaRateOdd) * dt();
            //update particle location
            arr[i][j].currPos.x=arr[i][j].circleRad*cos(arr[i][j].theta)+250;
            arr[i][j].currPos.y=arr[i][j].circleRad*sin(arr[i][j].theta)+250;
            //draw the particle
            setColor(arr[i][j].color);
            drawSphere(arr[i][j].currPos, 5);
         }
       }
   }
private:
int N = 5;
Particle arr[5][36] = {};
float thetaRateEven = 0.1;
float thetaRateOdd = -0.1;
vec3 colorPalette[5] = {};
};

int main(int argc, char** argv)
{
   Circles viewer;
   viewer.run();
   return 0;
}
