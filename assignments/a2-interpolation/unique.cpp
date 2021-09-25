#include "atkui/framework.h"
using namespace glm;

class Unique : public atkui::Framework {
  /*
  struct Curve{
  vec3 color;
  vec3 cpts [4] = {};
};
*/
 public:
  Unique() : atkui::Framework(atkui::Orthographic) {
  }

  void setup() {
     //set up 6 color sectors of curves(7 boundaries)
     for(int i=0;i<7;i++){
        cpts[i][0]=vec3(60*(i+1), 10, 0);
        cpts[i][1]=vec3(60*(i+1)-60*0, 150, 0);
        cpts[i][2]=vec3(60*(i+1)+60*0, 310, 0);
        cpts[i][3]=vec3(60*(i+1), 510, 0);
     }
  }
  void scene() {

     //we want range for 2nd cpt[60*(i+1)-60, 60*(i+1)+60 ]
      for(int j=0;j<7;j++){
       
      cpts[j][1]=vec3(60*(j+1)-60*sin(elapsedTime()*2), 110, 0);
      cpts[j][2]=vec3(60*(j+1)+60*sin(elapsedTime()*2), 110, 0);
      }
     for(int j=0;j<6;j++){
        setColor(colors[j]);
      vec3 currPos=cpts[j][0];
      //starting control points
      vec3 arr[4]={};
      for(int k=0;k<4;k++){
         arr[k]=cpts[j][k];
      }
      float t=0;
      //add curves for each sector
         while(t<1&&arr[1].x<cpts[j+1][1].x&&arr[2].x<cpts[j+1][2].x){
            for(float i = 0;i<=1;i+=0.01){
               vec3 p=((float)pow(1-i, 3.0))*arr[0]+3*i*((float)pow(1-i, 2.0))*arr[1]+3*((float)pow(i, 2.0))*(1-i)*arr[2]+((float)pow(i, 3.0))*arr[3];
          
               drawLine(currPos, p);
               currPos=p;
         }
         t+=0.1;
         //lerp between different color sectors
         for(int k=0;k<4;k++){
         arr[k]=LERP(cpts[j][k], cpts[j+1][k], t);
       }
      }
     }
  }
  vec3 LERP(vec3 p1, vec3 p2, float t){
   vec3 res=p1*(1-t)+p2*t;
   return res;
  }
  private:
  vec3 colors [7]={
   vec3(1, 0, 0),
   vec3(1, 0.5, 0),
   vec3(1, 1, 0),
   vec3(0,1, 0),
   vec3(0, 0, 1),
   vec3(0.3, 0, 0.5),
   vec3(0.5, 0, 1)};
  vec3 cpts [7][4]={};
};
int main(int argc, char** argv) {
  Unique viewer;
  viewer.run();
}
