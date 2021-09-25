#include "atkui/framework.h"
#include <algorithm>
using namespace glm;
using namespace std;
class Screensaver : public atkui::Framework {
  /*
  struct Curve{
  vec3 color;
  vec3 cpts [4] = {};
};
*/
 public:
  Screensaver() : atkui::Framework(atkui::Orthographic) {
  }

  void setup() {
    /*
    curve1 = vec3((float)(rand()%width(), (float)(rand()%height(), 0);
    curve2= vec3((float)(rand()%width(), (float)(rand()%height(), 0);
    */
    //create randomized control points for curve1 and curve2
    vec3 cpts[4]={};
    for(int i=0;i<4;i++){
      curve1CPTs[i]=vec3(((float)(rand()%(int)width())), ((float)(rand()%(int)height())), 0);
      curve2CPTs[i]=vec3(((float)(rand()%(int)width())), ((float)(rand()%(int)height())), 0);
      cpts[i]=curve1CPTs[i];
      trail[0][i]=curve1CPTs[i];
      curr[i]=curve1CPTs[i];
    }
    color=agl::randomUnitVector();
    //trail[0]={color, cpts};
    
  }

  void scene() {
      setColor(color);
      //calculate t
       t += (dt()/5.0);
       //generate a new target curve
      if(t>1){
        t = 0;
        for(int i=0;i<4;i++){
          curve1CPTs[i]=curr[i];
          curve2CPTs[i]=vec3(((float)(rand()%(int)width())), ((float)(rand()%(int)height())), 0);
        }
        color=agl::randomUnitVector();
        setColor(color);
      }
      vec3 currPos=curr[0];
      //draw curve at time t
      for(float i = 0;i<=1;i+=0.01){
          vec3 p=((float)pow(1-i, 3.0))*curr[0]+3*i*((float)pow(1-i, 2.0))*curr[1]+3*((float)pow(i, 2.0))*(1-i)*curr[2]+((float)pow(i, 3.0))*curr[3];
          //cout << i;
          drawLine(currPos, p);
          currPos=p;
      }
      //check if need to add a new curve
      if(elapsedTime()-X>=lastTime){
       
        lastTime=elapsedTime();
        count++;
        vec3 cpts [4] = {};
        for(int i=0;i<4;i++){
          trail[count%50][i]=curr[i];
         
        }
         //trail[count%50]={color, cpts};
        
      }
      //draw at most 50 trailing curves
      int stop=std::min(count+1, 50);
        for(int j=0;j<stop;j++){
           vec3 currPosTrail=trail[j][0];
          for(float i = 0;i<=1;i+=0.01){
            vec3 p=((float)pow(1-i, 3.0))*trail[j][0]+3*i*((float)pow(1-i, 2.0))*trail[j][1]+3*((float)pow(i, 2.0))*(1-i)*trail[j][2]+((float)pow(i, 3.0))*trail[j][3];
          
            drawLine(currPosTrail, p);
            currPosTrail=p;
         }
        }
        //computer control points for the next frame
      for(int i=0;i<4;i++){
        curr[i]=LERP(curve1CPTs[i], curve2CPTs[i], t);
        //cout << curr[i];
        
      }
      //cout << "----";
      
}
  vec3 LERP(vec3 p1, vec3 p2, float t){
   vec3 res=p1*(1-t)+p2*t;
   return res;
  }

  private:
  vec3 curve1CPTs [4]={};
  vec3 curve2CPTs [4]={};
  vec3 curr [4] ={};
  vec3 curve1;
  vec3 curve2;
  vec3 current;
  vec3 color;
  //Curve trail [50] = {};
  //trailing curves
  vec3 trail [50][4] ={};
  float t =0;
  float lastTime = 0.0;
  float X = 0.1;
  int count = 0;
};

int main(int argc, char** argv) {
  Screensaver viewer;
  viewer.run();
}

