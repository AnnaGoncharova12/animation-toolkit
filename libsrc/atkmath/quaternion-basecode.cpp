#include "atkmath/quaternion.h"
#include "atkmath/matrix3.h"
#include "atkmath/vector3.h"
#include <math.h>
#include <algorithm>

namespace atkmath {

Quaternion Quaternion::Slerp(const Quaternion& q0, const Quaternion& q1, double t)
{
    double dot = Dot(q0, q1);
    if(dot<0){
		Quaternion q2 = operator- (q1);
		double dot = Dot(q0, q2);
	}
	float omega = acos(dot);
	   std::cout << omega << std::endl; 
	   //check for edge cases
    if(omega==0.0||t==0.0){
        return q0;
    }
    if(t==1.0){
        return q1;
    }
    //std::cout << omega;

    double a =(sin(omega*(1-t))/sin(omega));
    double b = (sin(omega*t)/sin(omega));
    Quaternion toReturn = operator+ ( operator* (a, q0), operator* (b, q1));
	return toReturn;
}

void Quaternion::toAxisAngle (Vector3& axis, double& angleRad) const
{
	//normalize();
	angleRad=acos(this->mW);
	axis = Vector3((this->mX)/sin(angleRad),(this->mY)/sin(angleRad), (this->mZ)/sin(angleRad));
	angleRad*=2;
}

void Quaternion::fromAxisAngle (const Vector3& axis, double angleRad)
{
	double halved = angleRad/2.0;
	double mySin = sin(halved);
    mX=axis.x()*mySin;
	mY=axis.y()*mySin;
	mZ=axis.z()*mySin;
	mW=cos(halved);
	normalize();
	
	
}

Matrix3 Quaternion::toMatrix () const
{
	//normalize();
	double y = this->mY;
	double x = this->mX;
	double z = this->mZ;
	double w = this->mW;
	//use matrix given in the assignment
	Matrix3 toReturn = Matrix3(1-2*(y*y+z*z), 2*(x*y-w*z), 2*(x*z+w*y),
							   2*(x*y+w*z), 1-2*(x*x+z*z), 2*(y*z-w*x),
							   2*(x*z-w*y), 2*(y*z+w*x), 1-2*(y*y+x*x));
	return toReturn;
}

void Quaternion::fromMatrix(const Matrix3& rot)
{
	Vector3 axis = Vector3();
	double angle = 0.0;
	//call matrix helper function
	rot.toAxisAngle(axis, angle);
	mX=axis.x();
	mY=axis.y();
	mZ=axis.z();
	mW=angle;
	normalize();
}

}

