#include "atkui/framework.h"
#include "atk/toolkit.h"
#include "atkmath/quaternion.h"
#include "atkmath/vector3.h"
using namespace atk;
using namespace atkmath;
using atkmath::Quaternion;
using atkmath::Vector3;
using glm::vec3;

class Tentacle : public atkui::Framework {
public:
   Tentacle() : atkui::Framework(atkui::Perspective) {}
   virtual ~Tentacle() {}

   virtual void setup() {
      lookAt(vec3(200), vec3(0));

      Joint* root  = new Joint("root");
      root->setLocalTranslation(vec3(0,0,0));
      _tentacle.addJoint(root);

      Joint* joint1  = new Joint("joint1");
      joint1->setLocalTranslation(vec3(0,50,0));
      _tentacle.addJoint(joint1, root);
      Joint* prev = joint1;
      // todo: add more joints
      for(int i=2;i<6;i++){
         //create joint and add it to the skeleton
         Joint* joint  = new Joint("joint"+i);
         joint->setLocalTranslation(vec3(0,50,0));
        _tentacle.addJoint(joint, prev);
         prev=joint;

      }


      _tentacle.fk(); // compute local2global transforms
   }

   virtual void scene()
   {
      // todo animate joints
      // hint: use glm::angleAxis(...) to compute quaternions for each joint
      _tentacle.fk(); // computes local2global transforms
      setColor(vec3(0,1,0));
      float angle = sin(elapsedTime()/3.0f);
      for(int i=0;i<6;i++){
         //set local rotation
         glm::quat q = glm::angleAxis(angle, vec3(0, 0, 1) );
         Joint * joint = _tentacle.getByID(i);
         joint->setLocalRotation(q);
      }
      // todo: loop over all joints and draw
      for(int i=0;i<5;i++){
      //draw the joints
      Joint* parent = _tentacle.getByID(i);
      Joint* child = _tentacle.getByID(i+1);
      vec3 globalParentPos = parent->getGlobalTranslation();
      vec3 globalPos = child->getGlobalTranslation();
      drawEllipsoid(globalParentPos, globalPos, 5);
      }
   }

protected:
   Skeleton _tentacle;
};

int main(int argc, char** argv)
{
   Tentacle viewer;
   viewer.run();
} 

