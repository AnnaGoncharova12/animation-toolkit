#include "atkui/framework.h"
#include "atkui/skeleton_drawer.h"
#include "atk/toolkit.h"
#include <iostream>
#include <cmath>

using namespace glm;
using namespace std;
using namespace atk;

class WASDSimple : public atkui::Framework
{
public:
  WASDSimple() : atkui::Framework(atkui::Perspective) {}

  virtual void setup()
  {
    BVHReader reader;
    reader.load("../motions/Beta/walking.bvh", _skeleton, _walk);
    _drawer.showAxes = true;
  }

  virtual void scene()
  {
    update();
    _drawer.draw(_skeleton, *this);

    // draw heading
    vec3 p = _skeleton.getRoot()->getGlobalTranslation();
    p[1] = 10; // set height close above the floor

    setColor(vec3(0, 1, 1));
    push();
    translate(p);
    rotate(_heading, vec3(0, 1, 0));
    translate(vec3(0,0,25));
    scale(vec3(10, 10, 50));
    drawCylinder(vec3(0), 1.0f);
    pop();
  }

  virtual void update()
  {
    _walk.update(_skeleton, elapsedTime());

    // TODO: Your code here
 //step 2 doesnt work??
 /*
    Pose pose = _walk.getKey(0);
      quat curr = pose.jointRots[0];
       std::cout << _heading << std::endl;
      //use angleAxis, instead of constructor
      quat desired = glm::angleAxis (_heading, vec3(0, 1, 0));
      quat deltaR = (inverse(curr))*desired;
      //identity quat and reverse translation vec3 to move root to the origin
      Transform one = Transform(quat(0, vec3(1, 0, 0)), vec3(-pose.rootPos.x, -pose.rootPos.y, -pose.rootPos.z));
      Transform desiredTr = Transform(desired, vec3(0, 0, 0));
      Transform orig = Transform(curr, pose.rootPos);
      Transform offset = desiredTr*(orig.inverse());
      //get first frame root transfrom
      Transform intermediate = orig * one;
      Transform newTr = intermediate * desiredTr;
      //vec3 oldRoot = pose.rootPos;
      pose.rootPos = newTr.t();
      pose.jointRots[0] = newTr.r();
     _walk.editKey(0, pose);


      int numKeys = _walk.getNumKeys();
      for(int i=1;i<numKeys;i++){
          Pose pose = _walk.getKey(i);
          //calculate the transfrom for frame i
          Transform currTransform = Transform(pose.jointRots[0], pose.rootPos);
          Transform currOffset = offset * currTransform;
          pose.rootPos = currOffset.t();
          pose.jointRots[0] = currOffset.r();
          _walk.editKey(i, pose);
      }
*/


    //step1
    for(int i=1;i<_walk.getNumKeys();i++){
            Pose pose = _walk.getKey(i);
            pose.rootPos = _walk.getKey(0).rootPos;
            pose.jointRots[0] = _walk.getKey(0).jointRots[0];
            _walk.editKey(i, pose);
    }
 //setp 2
 turn();

    // TODO: Override the default camera to follow the character
    // lookAt(pos, look, vec3(0, 1, 0));

    // update heading when key is down
    if (keyIsDown('D')) _heading -= 0.05;
    if (keyIsDown('A')) _heading += 0.05;
  }
  
void turn(){

     Pose pose = _walk.getKey(0);
      quat curr = pose.jointRots[0];
      //use angleAxis, instead of constructor
      quat desired = glm::angleAxis (_heading, vec3(0, 1, 0));
      quat deltaR = (inverse(curr))*desired;
      //use vec3(0, 0, 0) for transalation becaus we don't need to move the character yet
      Transform one = Transform(quat(0, vec3(1, 0, 0)), vec3(0, 0, 0));
      Transform desiredTr = Transform(desired, vec3(0, 0, 0));
      Transform orig = Transform(curr, pose.rootPos);
      Transform offset = desiredTr*(orig.inverse());
      //get first frame root transfrom
      Transform intermediate = orig*one;
      Transform newTr = intermediate * desiredTr;
      //vec3 oldRoot = pose.rootPos;
      pose.rootPos = newTr.t();
      pose.jointRots[0] = newTr.r();
      _walk.editKey(0, pose);
      /*
        for(int i=1;i<_walk.getNumKeys();i++){
          
            Pose pose = _walk.getKey(i);
            
           
          //calculate the transfrom for frame i
          Transform currTransform = Transform(pose.jointRots[0], pose.rootPos);
          Transform currOffset = offset * currTransform;
          pose.rootPos = currOffset.t();
          pose.jointRots[0] = currOffset.r();
            _walk.editKey(i, pose);
    }
    */
    for(int i=1;i<_walk.getNumKeys();i++){
            Pose pose = _walk.getKey(i);
            pose.rootPos = _walk.getKey(0).rootPos;
            pose.jointRots[0] = _walk.getKey(0).jointRots[0];
            _walk.editKey(i, pose);
    }

      
}

protected:
  float _heading;

  Motion _walk;
  Skeleton _skeleton;
  atkui::SkeletonDrawer _drawer;
};

int main(int argc, char **argv)
{
  WASDSimple viewer;
  viewer.run();
}
