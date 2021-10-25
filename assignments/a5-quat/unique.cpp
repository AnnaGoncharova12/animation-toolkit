#include "atkui/framework.h"
#include "atkmath/constants.h"
#include "atkmath/quaternion.h"
#include "atkmath/vector3.h"
using namespace glm;
using namespace std;
using namespace atkmath;

class Unique : public atkui::Framework {
 public:

  Unique() : atkui::Framework(atkui::Orthographic) {
  }

   
  void setup() {
    
  }

  void scene() {
    //calculate time
    double mod = fmod(elapsedTime(), timeToTravel);
    double t = mod/timeToTravel;
    //nprmalize all quaternions;
    q.normalize();
    q2.normalize();
    q3.normalize();
    q4.normalize();
    //calculate the location of  and draw kettle 1
    Quaternion pPrime = q * p * (q.inverse());
    vec3 point = vec3(pPrime.x(), pPrime.y(), pPrime.z());
    setColor(vec3(1,1,0));
    drawTeapot(point, 100);
    //calculate the location of  and draw kettle 2
    pPrime = q2 * p * (q2.inverse());
    point = vec3(pPrime.x(), pPrime.y(), pPrime.z());
    setColor(vec3(1,0,0));
    drawTeapot(point, 100);
    //calculate the location of  and draw kettle 3
    pPrime = q3 * p * (q3.inverse());
    point = vec3(pPrime.x(), pPrime.y(), pPrime.z());
    setColor(vec3(0,0,1));
    drawTeapot(point, 100);
    //calculate the location of  and draw kettle 4
    pPrime = q4 * p * (q4.inverse());
    point = vec3(pPrime.x(), pPrime.y(), pPrime.z());
    setColor(vec3(0,1,0));
    drawTeapot(point, 100);

    angle = LERP(0.0, end, t);
    if(angle>=2*M_PI){
      angle = 0.0;
    }
    //update quaternions
    q= Quaternion(Vector3(0.5, 0.5, 0.75), angle );
    q2 = Quaternion(Vector3(0.1, 0.25, 0.65), angle);
    q3 = Quaternion(Vector3(0.75, 0.3, 0.4), angle);
    q4 = Quaternion(Vector3(-0.5, 0.64, 0.12), angle);
    //q = Quaternion(Vector3(0.1, 0.5, 0.75), q.w()+dt());

  }
  //linear interpolation used for the angle
  double LERP(double p1, double p2, double t){
    double res=p1*(1-t)+p2*t;
    return res;
  }
  private:
  Quaternion p = Quaternion(250, 250, 250, 0);
  //quaternions with hardcoded rotation axes that could also be randomized if needed
  Quaternion q = Quaternion(Vector3(0.5, 0.5, 0.75), 0.0);
  Quaternion q2 = Quaternion(Vector3(-0.65, 0.25, 0.65), 0.0);
  Quaternion q3 = Quaternion(Vector3(0.75, 0.3, 0.4), 0.0);
  Quaternion q4 = Quaternion(Vector3(-0.5, 0.64, 0.12), 0.0);
  double angle = 0.0;
  double end = 2*M_PI;
  double timeToTravel = 10.0;
};

int main(int argc, char** argv) {
  Unique viewer;
  viewer.run();
}

