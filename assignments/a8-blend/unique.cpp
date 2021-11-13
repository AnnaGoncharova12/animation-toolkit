#include "atk/toolkit.h"
#include "atkui/framework.h"
#include "atkui/skeleton_drawer.h"
#include <algorithm>
#include <string>
#include<queue>

using namespace atk;
using namespace atkui;
using namespace glm;
using namespace std;

class Unique : public atkui::Framework
{
public:
   Unique() : atkui::Framework(atkui::Perspective) {}
   virtual ~Unique() {}

   void setup()
   {
      _alpha = 0;

      BVHReader reader;
      reader.load("../motions/Beta/walking.bvh", _skeleton, _lower);
      reader.load("../motions/Beta/gangnam_style.bvh", _skeleton, _upper);
      _splice = spliceUpperBody(_lower, _upper, _alpha);
   }

   Motion spliceUpperBody(const Motion& lower, const Motion& upper, float alpha)
   {
      Motion result = lower;
      result.setFramerate(lower.getFramerate());
      // todo: your code here
      int numKeys = lower.getNumKeys();

/*
      for(int i=0;i<numKeys;i++){
         Pose pose1 = lower.getKey(i);
         Pose pose2 = upper.getKey(i);
         Joint* upperJoint = _skeleton.getByID(2); //Beta:Spine1
         Pose newPose = Pose();
         newPose.rootPos = pose1.rootPos;
         for(int j = 0;j<skelNum;j++){
              if(upperBody[j]){
                 newPose.jointRots.push_back(glm::slerp(pose1.jointRots[j], pose2.jointRots[j], alpha));
              }
              else{
                 newPose.jointRots.push_back(pose1.jointRots[j]);
              }
         }
         //how to use the joint in its descendants in lerp
         
         result.appendKey(newPose); 
      }
      */
      return result;
   }

   void scene()
   {  
      _splice.update(_skeleton, elapsedTime() * 0.5);
      SkeletonDrawer drawer;
      drawer.draw(_skeleton, *this);
     
      Joint* root = _skeleton.getRoot();
      vec3 location = root->getLocalTranslation();
      //add particles trace
      for(int i=0;i<50;i++){
          setColor(agl::randomUnitVector());
         drawSphere(vec3(location.x-25-rand()%10*i, location.y+50+rand()%10*i, location.z), 5);
      }
     
      //drawText("alpha: "+std::to_string(_alpha), 10, 15);
   }

   void keyUp(int key, int mods) 
   {
      if (key == GLFW_KEY_UP)
      {
         _alpha = std::min(_alpha+0.05, 1.0);
         _splice = spliceUpperBody(_lower, _upper, _alpha);
      }
      else if (key == GLFW_KEY_DOWN)
      {
         _alpha = std::max(_alpha-0.05, 0.0);
         _splice = spliceUpperBody(_lower, _upper, _alpha);
      }
   }

   Skeleton _skeleton;
   Motion _upper;
   Motion _lower;
   Motion _splice;
   float _alpha;
};

int main(int argc, char** argv)
{
   Unique viewer;
   viewer.run();
   return 0;
}


