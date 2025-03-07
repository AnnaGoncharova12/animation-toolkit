#include "atkui/framework.h"
#include "atk/toolkit.h"
#include "atkmath/quaternion.h"
#include "atkmath/vector3.h"
using namespace atk;
using namespace atkmath;
using atkmath::Quaternion;
using atkmath::Vector3;
using glm::vec3;

class Unique : public atkui::Framework {
public:
   Unique() : atkui::Framework(atkui::Perspective) {}
   virtual ~Unique() {}

   virtual void setup() {
      lookAt(vec3(200), vec3(0));

      Joint* root  = new Joint("root");
      root->setLocalTranslation(vec3(0,0,0));
      _tentacle.addJoint(root);

      Joint* joint1  = new Joint("joint1");
      joint1->setLocalTranslation(vec3(0,50,0));
      _tentacle.addJoint(joint1, root);
     

       Joint* joint2  = new Joint("joint2");
      joint2->setLocalTranslation(vec3(0,50,0));
      _tentacle.addJoint(joint2, joint1);
     
       Joint* joint3  = new Joint("joint3");
      joint3->setLocalTranslation(vec3(50,0,0));
      _tentacle.addJoint(joint3, joint1);
     
       Joint* joint4  = new Joint("joint4");
      joint4->setLocalTranslation(vec3(-50,0,0));
      _tentacle.addJoint(joint4, joint1);
      
      Joint* joint5  = new Joint("joint5");
      joint5->setLocalTranslation(vec3(50,0,0));
      _tentacle.addJoint(joint5, joint3);
     
       Joint* joint6  = new Joint("joint6");
      joint6->setLocalTranslation(vec3(50,0,0));
      _tentacle.addJoint(joint6, joint4);

      _tentacle.fk(); // compute local2global transforms
   }

   virtual void scene()
   {
      // todo animate joints
      // hint: use glm::angleAxis(...) to compute quaternions for each joint
      _tentacle.fk(); // computes local2global transforms
      setColor(vec3(1, 0,0));
      float angle = sin(elapsedTime()/2.0f);
      
       glm::quat q = glm::angleAxis(angle, vec3(0, 0, 1) );
       Joint * joint = _tentacle.getByID(1);
        joint->setLocalRotation(q);
        joint = _tentacle.getByID(3);
        joint->setLocalRotation(q);
        joint = _tentacle.getByID(4);
        joint->setLocalRotation(q);
        
      /*
      float angle = sin(elapsedTime()/3.0f);
      for(int i=0;i<6;i++){
         //set local rotation
         glm::quat q = glm::angleAxis(angle, vec3(0, 0, 1) );
         Joint * joint = _tentacle.getByID(i);
         joint->setLocalRotation(q);
      }
      */
      // todo: loop over all joints and draw
     for(int i=0;i<2;i++){
      //draw the joints
      Joint* parent = _tentacle.getByID(i);
      Joint* child = _tentacle.getByID(i+1);
      vec3 globalParentPos = parent->getGlobalTranslation();
      vec3 globalPos = child->getGlobalTranslation();
      drawEllipsoid(globalParentPos, globalPos, 5);
      }
      Joint* parent = _tentacle.getByID(1);
      Joint* child = _tentacle.getByID(3);
      vec3 globalParentPos = parent->getGlobalTranslation();
      vec3 globalPos = child->getGlobalTranslation();
      drawEllipsoid(globalParentPos, globalPos, 5);

      parent = _tentacle.getByID(1);
      child = _tentacle.getByID(4);
       globalParentPos = parent->getGlobalTranslation();
       globalPos = child->getGlobalTranslation();
      drawEllipsoid(globalParentPos, globalPos, 5);
   }

protected:
   Skeleton _tentacle;
};

int main(int argc, char** argv)
{
   Unique viewer;
   viewer.run();
} 





/*
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
*/
