#include "atk/toolkit.h"
#include "atkui/framework.h"
#include "atkui/skeleton_drawer.h"
#include <algorithm>
#include <string>

using namespace glm;
using namespace atk;
using namespace atkui;

class AZombieArms : public atkui::Framework {
public:
   AZombieArms() : atkui::Framework(atkui::Perspective) {}
   virtual ~AZombieArms() {}

   void setup() {
      BVHReader reader;
      reader.load("../motions/Beta/walking.bvh", _skeleton, _original);

      _zombieFreeze = ComputeArmFreeze(_original);
      _zombieOffset = ComputeArmOffset(_original);
   }

   Motion ComputeArmOffset(const Motion& motion) {
      quat leftLocalRot = eulerAngleRO(XYZ, radians(vec3(-53, -88, -33)));
      quat rightLocalRot = eulerAngleRO(XYZ, radians(vec3(14, 88, -33)));
      quat elbowLocalRot = eulerAngleRO(XYZ, radians(vec3(0, 23, 0)));

      Joint* leftArm = _skeleton.getByName("Beta:LeftArm");
      Joint* rightArm = _skeleton.getByName("Beta:RightArm");

      Joint* leftElbow = _skeleton.getByName("Beta:LeftForeArm");
      Joint* rightElbow = _skeleton.getByName("Beta:RightForeArm");

      Motion result;
      result.setFramerate(motion.getFramerate());
      Transform t = rightArm->getLocal2Parent().inverse();
      quat Rij = t.r();
      quat offsetRight = rightLocalRot * Rij;

      t = leftArm->getLocal2Parent().inverse();
      Rij = t.r();
      quat offsetLeft = leftLocalRot * Rij;
      // todo: your code here
      int numKeys=motion.getNumKeys();
      for(int i=0;i<numKeys;i++){
         Pose pose = motion.getKey(i);
         //update joint rotations in the pose
         pose.jointRots[rightArm->getID()] = pose.jointRots[rightArm->getID()] * offsetRight ;
         pose.jointRots[leftArm->getID()] = pose.jointRots[leftArm->getID()] *offsetLeft;
         pose.jointRots[leftElbow->getID()] = elbowLocalRot;
         pose.jointRots[rightElbow->getID()] = elbowLocalRot;
         
         result.appendKey(pose);
      }
   

      return result;
   }

   Motion ComputeArmFreeze(const Motion& motion) {
      quat leftRot = eulerAngleRO(XYZ, radians(vec3(-53, -88, -33)));
      quat rightRot = eulerAngleRO(XYZ, radians(vec3(14, 88, -33)));
      quat elbowRot = eulerAngleRO(XYZ, radians(vec3(0, 23, 0)));

      Joint* leftArm = _skeleton.getByName("Beta:LeftArm");
      Joint* rightArm = _skeleton.getByName("Beta:RightArm");

      Joint* leftElbow = _skeleton.getByName("Beta:LeftForeArm");
      Joint* rightElbow = _skeleton.getByName("Beta:RightForeArm");

      Motion result;
      result.setFramerate(motion.getFramerate());
      // todo: your code here
      /*
      leftArm.setLocalRotation(leftRot);
      rightArm.setLocalRotation(rightRot);
      leftElbow.setLocalRotation(elbowRot);
      rightElbow.setLocalRotation(elbowRot);
      */
      int numKeys=motion.getNumKeys();
      for(int i=0;i<numKeys;i++){
         Pose pose = motion.getKey(i);
         //update joint rotations in the pose
         pose.jointRots[leftArm->getID()] = leftRot;
         pose.jointRots[leftElbow->getID()] = elbowRot;
         pose.jointRots[rightElbow->getID()] = elbowRot;
         pose.jointRots[rightArm->getID()] = rightRot;
         result.appendKey(pose);
      }
     

      return result;
   }

   void update() {
      double t =  elapsedTime() * 0.5;
      if (_currentMotion == 1) {
         _zombieFreeze.update(_skeleton, t);
         drawText("Joint edit type: freeze", 10, 15);

      } else if (_currentMotion == 2) {
         _zombieOffset.update(_skeleton, t);
         drawText("Joint edit type: offset", 10, 15);

      } else {
         _original.update(_skeleton, t);
         drawText("Joint edit type: none", 10, 15);
      }
   }

   void scene() {  
      update();
      _drawer.draw(_skeleton, *this);
   }

   void keyUp(int key, int mods) {
      if (key == '1') {
          _currentMotion = 1;
      } else if (key == '2') {
          _currentMotion = 2;
      } else if (key == '0') {
          _currentMotion = 0;
      }
   }

   SkeletonDrawer _drawer;
   Skeleton _skeleton;
   Motion _original;
   Motion _zombieFreeze;
   Motion _zombieOffset;
   int _currentMotion = 0;
};

int main(int argc, char** argv) {
   AZombieArms viewer;
   viewer.run();
   return 0;
}

