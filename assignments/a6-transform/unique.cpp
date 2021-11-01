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
    //set up joints
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
      //set up rotating parts
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
   
     for(int i=0;i<2;i++){
      //draw vertical joints
      Joint* parent = _tentacle.getByID(i);
      Joint* child = _tentacle.getByID(i+1);
      vec3 globalParentPos = parent->getGlobalTranslation();
      vec3 globalPos = child->getGlobalTranslation();
      drawEllipsoid(globalParentPos, globalPos, 5);
      }
      //draw horisontal joints
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

