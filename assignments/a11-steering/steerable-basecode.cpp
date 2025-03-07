#include "steerable.h"
#include "behaviors.h"

using namespace glm;
using namespace atk;
float omegan = 8.0;
float eta = 1.0;
float ASteerable::kVelKv = 10.0; 
float ASteerable::kOriKv =  2.0 * omegan * eta;  
float ASteerable::kOriKp = omegan * omegan;

// Given a desired velocity, veld, and dt, compute a transform holding 
// the new orientation and change in position
//
// rotation control: tau = I * (-Kv1 * thetaDot + Kp1 * (thetaD - theta))
// translation control: f = m * Kv0 * (vd - v)
void ASteerable::senseControlAct(const vec3& veld, float dt)
{
   // Compute _vd and _thetad
    _vd = length(veld);
    _thetad = atan2(veld.x, veld.z);

   // compute _force and _torque
   _force = _mass * kVelKv * (_vd - length(_state[VEL])) ;
   _torque = _inertia * (kOriKp*(_thetad - _state[ORI]) - kOriKv*_state[AVEL]);
   //_torque = 0.0;
   // find derivative
   _derivative[POS] = _state[VEL];
   _derivative[ORI] = _state[AVEL];
   _derivative[AVEL] = _torque/_inertia;
   _derivative[VEL] = _force/_mass;
   // update state
   _state[0]=_state[0] + dt* _derivative[0];
   _state[1]=_state[1] + dt* _derivative[1];
   _state[2]=_state[2] + dt* _derivative[2];
   _state[3]=_state[3] + dt* _derivative[3];
   // compute global position and orientation and update _characterRoot
   quat rot = glm::angleAxis(_state[ORI], vec3(0,1,0));
   vec3 localPos(0,0,_state[POS]);

   _characterRoot.setT(rot * localPos + _characterRoot.t());
   _characterRoot.setR(rot); 
   std::cout << _thetad << " " << _vd << " " << _state[POS]<<std::endl;
}

// randomize the colors, characters, and animation times here
void ASteerable::randomizeAppearance()
{
   // to randomize the walking animations, compute different initial values 
   // for _time
   _time = float(rand()%10)+3;
   // to randomize color, call _drawer.setColor
     _drawer.color = agl::randomUnitVector();
   // to randomize shape, compute random values for _drawer.setJointRadius
   _drawer.jointRadius=float(rand()%10)+10;
   //_drawer.setJointRadius(agl::randomUnitVector()*10);
   // or randomly assign different drawers to have a mix of characters
}

