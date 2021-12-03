#include "ik_controller.h"
#include <cmath>
#include <iostream>

using namespace atk;
using namespace glm;
using namespace std;

bool IKController::solveIKAnalytic(Skeleton& skeleton, 
    int jointid, const vec3& goalPos, float epsilon) {
  if (jointid == -1) return true;

  Joint* ankle = skeleton.getByID(jointid);
  if (!ankle->getParent()) {
    std::cout << "Warning: solveIKAnalytic() needs joint "
      "with parent and grandparent\n";
    return false;
  }

  Joint* knee = ankle->getParent();
  vec3 limbDir = normalize(parentJoint->getLocalTranslation());
  vec3 axisKnee = cross(limbDir, vec3(0,0,-1));
  float angleKnee = 0.0f;
  if (limbDir[1] < 0) axisKnee = cross(limbDir, vec3(0,0,1));
  knee->setLocalRotation(glm::angleAxis(angleKnee, axisKnee));
  knee->fk();
  if (!knee->getParent()) {
    std::cout << "Warning: solveIKAnalytic() needs joint "
      "with parent and grandparent\n";
    return false;
  }

  Joint* hip = knee->getParent();
        vec3 targetLocal = ((hip->getLocal2Global()).inverse()).transformPoint(goalPos);
        vec3 endLocal = ((hip->getLocal2Global()).inverse()).transformPoint(skeleton.getByID(jointid)->getGlobalTranslation());
        vec3 r = vec3(0, 0, 0)- endLocal ;
        vec3 e = (targetLocal - r);
        float tanPhi = length(cross(r, e))/(dot(r, e) + dot(r, r));
        float angle =  atan(tanPhi);
        if(length(cross(r, e))>=epsilon){
        vec3 axis = cross(r, e) / length(cross(r, e));
        hip->setLocalRotation(glm::angleAxis(angle, axis));
      }
        hip->fk();
  // TODO: Your code here
  return true;
}

bool IKController::solveIKCCD(Skeleton& skeleton, int jointid, 
    const vec3& goalPos, const std::vector<Joint*>& chain, 
    float threshold, int maxIters, float nudgeFactor) {
  // There are no joints in the IK chain for manipulation
  if (chain.size() == 0) return true;

  // TODO: Your code here
  //||pd - p||
  float dist = glm::length(goalPos - skeleton.getByID(jointid)->getGlobalTranslation());
  float epsilon = 0.001F;
  int numIters = 0;
  while(dist> threshold && numIters < maxIters){
      for(int i =0;i<chain.size();i++){
        Joint* curr = chain[i];
        vec3 targetLocal = ((curr->getLocal2Global()).inverse()).transformPoint(goalPos);
        vec3 endLocal = ((curr->getLocal2Global()).inverse()).transformPoint(skeleton.getByID(jointid)->getGlobalTranslation());
        vec3 r = vec3(0, 0, 0)- endLocal ;
        vec3 e = (targetLocal - r);
        float tanPhi = length(cross(r, e))/(dot(r, e) + dot(r, r));
        float angle = nudgeFactor * atan(tanPhi);
        if(length(cross(r, e))>=epsilon){
        vec3 axis = cross(r, e) / length(cross(r, e));
        curr->setLocalRotation(glm::angleAxis(angle, axis));
      }
        curr->fk();
      }
      vec3 pos = skeleton.getByID(jointid)->getGlobalTranslation();
      //std::cout<<pos<<std::endl;
       //std::cout<<pos<<std::endl;
      dist = glm::length(goalPos - skeleton.getByID(jointid)->getGlobalTranslation());
      numIters++;
  }
  return false;
}
