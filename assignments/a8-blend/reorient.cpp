#include "atk/toolkit.h"
#include "atkui/framework.h"
#include "atkui/skeleton_drawer.h"
#include <algorithm>
#include <cmath>
#include <string>

using namespace glm;
using namespace atk;
using namespace atkui;

class AReorient : public atkui::Framework
{
public:
   AReorient() : atkui::Framework(atkui::Perspective) {}
   virtual ~AReorient() {}

   void setup()
   {
      BVHReader reader;
      reader.load("../motions/Beta/walking.bvh", _skeleton, _motion);

      _heading = 0;
      _offset = vec3(0);
      _offset[1] = _motion.getKey(0).rootPos[1];
      _time = 0;

      _reoriented = reorient(_motion, _offset, _heading);
   }

   Motion reorient(const Motion& motion, const vec3& pos, float heading)
   {
      Motion result;
      result.setFramerate(motion.getFramerate());

      // todo: your code here
      

      Pose pose = motion.getKey(0);
      quat curr = pose.jointRots[0];
      //use angleAxis, instead of constructor
      quat desired = glm::angleAxis (heading, vec3(0, 1, 0));
      quat deltaR = (inverse(curr))*desired;
      //identity quat and reverse translation vec3 to move root to the origin
      Transform one = Transform(quat(0, vec3(1, 0, 0)), vec3(-pose.rootPos.x, -pose.rootPos.y, -pose.rootPos.z));
      Transform desiredTr = Transform(desired, pos);
      Transform orig = Transform(curr, pose.rootPos);
      Transform offset = desiredTr*(orig.inverse());
      //get first frame root transfrom
      Transform intermediate = orig * one;
      Transform newTr = intermediate * desiredTr;
      //vec3 oldRoot = pose.rootPos;
      pose.rootPos = newTr.t();
      pose.jointRots[0] = newTr.r();
      result.appendKey(pose);
      

      int numKeys = motion.getNumKeys();
      for(int i=1;i<numKeys;i++){
          Pose pose = motion.getKey(i);
          //calculate the transfrom for frame i
          Transform currTransform = Transform(pose.jointRots[0], pose.rootPos);
          Transform currOffset = offset * currTransform;
          pose.rootPos = currOffset.t();
          pose.jointRots[0] = currOffset.r();
          result.appendKey(pose);
      }

      
      
      return result;
   }

   void update()
   {
      _time += dt() * 0.5;
      _reoriented.update(_skeleton, _time);
   }

   void scene()
   {  
      update();
      SkeletonDrawer drawer;
      drawer.draw(_skeleton, *this);
   }

   void keyUp(int key, int mods) 
   {
      if (key == GLFW_KEY_LEFT)
      {
         _heading += M_PI/8;
         _reoriented = reorient(_motion, _offset, _heading);
         _time = 0;
      }
      else if (key == GLFW_KEY_RIGHT)
      {
         _heading -= M_PI/8;
         _reoriented = reorient(_motion, _offset, _heading);
         _time = 0;
      }

      if (key == 'W')
      {
         _offset[2] += 25;
         _reoriented = reorient(_motion, _offset, _heading);
         std::cout << _offset << std::endl;
         _time = 0;
      }
      else if (key == 'S')
      {
         _offset[2] -= 25;
         _reoriented = reorient(_motion, _offset, _heading);
         _time = 0;
         std::cout << _offset << std::endl;
      }
      else if (key == 'A')
      {
         _offset[0] += 25;
         _reoriented = reorient(_motion, _offset, _heading);
         _time = 0;
         std::cout << _offset << std::endl;
      }
      else if (key == 'D')
      {
         _offset[0] -= 25;
         _reoriented = reorient(_motion, _offset, _heading);
         _time = 0;
         std::cout << _offset << std::endl;
      }
   }

   Skeleton _skeleton;
   Motion _motion;
   Motion _reoriented;
   vec3 _offset;
   float _heading;
   float _time;
};

int main(int argc, char** argv)
{
   AReorient viewer;
   viewer.run();
   return 0;
}

