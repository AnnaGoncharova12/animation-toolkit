#include "atk/toolkit.h"
#include "atkui/framework.h"
#include "cyclops.h"
#include <algorithm>
#include <string>

using namespace atk;
using namespace glm;
using namespace std;

class ALooker : public atkui::Framework {
public:
   ALooker() : atkui::Framework(atkui::Perspective) {}
   virtual ~ALooker() {}

   void setup() {
      Motion motion;
      BVHReader reader;
      reader.load("../motions/Beta/idle.bvh", _skeleton, motion);
      motion.update(_skeleton, 0);

      _drawer.color = vec3(1,0,0);
      _head = _skeleton.getByName("Beta:Head");
   }

   void reset(Joint* head) {
      head->setLocalRotation(IdentityQ);
      head->fk();
   }

   void lookAtTarget(Joint* head, const vec3& target) {
      // TODO: Your code here
      //float prevAng = atan2((float)prev.y, (float)prev.x);
      //step1 convert target to local coordinates of the head
      /*
      for(int i =0;i<_skeleton.getNumJoints();i++){
         std::cout<<i<<" "<<_skeleton.getByID(i)->getName()<<std::endl;
      }
      */
      /*
      std::vector<Transform> list;
      
      Joint* currJoint = head;
      //Joint* currJoint = head->getParent();
      while(currJoint!=NULL){
         Transform t = currJoint->getLocal2Parent();
         list.push_back(t);
         currJoint = currJoint->getParent();
      }
      //vec3 targetInLocal = target;
      vec3 targetInLocal = target;
      for(int i =list.size()-1;i--;i>=0){
         Transform inv = list[i].inverse();
          targetInLocal = inv.transformPoint(targetInLocal);
      }
      //setp 2 calculate deisred angle of rotation around z using atan2
      float curr = atan2((float)targetInLocal.y, (float)targetInLocal.x);
      //float heading = curr - prevAng; 
      //std::cout<<heading<<std::endl;
      //prev = vec3(target.x, target.y, target.z);
      quat newDir = glm::angleAxis (curr, vec3(0, 0, 1));
      head->setLocalRotation(newDir);
      head->fk();
      */

      /*
      vec3 curr = head->getGlobalTranslation();
      vec3 dir = glm::normalize(target - curr);
      */
      /*
     std::vector<Transform> list;
      
      Joint* currJoint = head;
      //Joint* currJoint = head->getParent();
      while(currJoint!=NULL){
         Transform t = currJoint->getLocal2Parent();
         list.push_back(t);
         currJoint = currJoint->getParent();
      }
      
      vec3 targetInLocal = target;
      for(int i =list.size()-1;i--;i>=0){
         Transform inv = list[i].inverse();
          targetInLocal = inv.transformPoint(targetInLocal);
      }

      vec3 parent = (head->getLocal2Parent().inverse()) * (head->getParent)
      */
      vec3 targetLocal = ((head->getLocal2Global()).inverse()).transformPoint(target);
      vec3 r = vec3(0, 0, 1);
      vec3 e = (targetLocal - r);
      float tanPhi = length(cross(r, e))/(dot(r, e) + dot(r, r));
      float phi = atan(tanPhi);
  
      vec3 axis = cross(r, e) / length(cross(r, e));
      std::cout<<axis<<std::endl;
      head->setLocalRotation(glm::angleAxis(phi, axis));
      head->fk();
   }

   void scene() {  
      float r = 100;
      float angle = elapsedTime();
      _target = vec3(r * cos(angle), r * sin(angle) + r, 150);

      reset(_head);
      lookAtTarget(_head, _target);
      _drawer.draw(_skeleton, *this);

      vec3 globalHeadPos = _head->getGlobalTranslation();
      vec3 globalForward = _head->getGlobalRotation() * vec3(0,0,1);

      setColor(vec3(0,0,1));
      drawLine(globalHeadPos, globalHeadPos + 200.0f*globalForward);
      drawSphere(_target, 5);
   }

   Cyclops _drawer;
   Skeleton _skeleton;
   Joint* _head;
   vec3 _target;
   vec3 prev = vec3(0, 0, 0);
};

int main(int argc, char** argv) {
   ALooker viewer;
   viewer.run();
   return 0;
}

