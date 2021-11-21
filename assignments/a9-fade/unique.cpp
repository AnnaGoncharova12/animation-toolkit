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


      return result;
   }

   void scene()
   {  
      _splice.update(_skeleton, elapsedTime() * 0.5);
      SkeletonDrawer drawer;
      drawer.draw(_skeleton, *this);
     
      Joint* root = _skeleton.getRoot();
      setColor(vec3(1, 0, 0));
     drawSphere(_skeleton.getByID(6)->getGlobalTranslation(), 60);
    
     //drawLine(_skeleton.getByID(6)->getGlobalTranslation()+vec3(0, 60, 0),_skeleton.getByID(6)->getGlobalTranslation()+vec3(0, 70, 0) );
     drawCylinder(_skeleton.getByID(6)->getGlobalTranslation()+vec3(0, 40, 0), 40);

      
      /*
      //add particles trace
      for(int i=0;i<50;i++){
          setColor(agl::randomUnitVector());
         drawSphere(vec3(location.x-25-rand()%10*i, location.y+50+rand()%10*i, location.z), 5);
      }
     */
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
   float offset = 0;
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



