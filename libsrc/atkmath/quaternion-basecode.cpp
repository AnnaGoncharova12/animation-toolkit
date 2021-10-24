#include "atkmath/quaternion.h"
#include "atkmath/matrix3.h"
#include "atkmath/vector3.h"
#include <math.h>
#include <algorithm>

namespace atkmath {

Quaternion Quaternion::Slerp(const Quaternion& q0, const Quaternion& q1, double t)
{
	// TODO
	return Quaternion(1,0,0,0);
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
	Matrix3 toReturn = Matrix3(1-2*(y*y+z*z), 2*(x*y-w*z), 2*(x*z+w*y),
							   2*(x*y+w*z), 1-2*(x*x+z*z), 2*(y*z-w*x),
							   2*(x*z-w*y), 2*(y*z+w*x), 1-2*(y*y+x*x));
	return toReturn;
}

void Quaternion::fromMatrix(const Matrix3& rot)
{
	/*
	double w = 0.0;
	double x = 0.0;
	double y = 0.0;
	double z = 0.0;

	double wSquared = (rot->m11+rot->m22+rot->m33+1)/4.0;
	double xSquared = (rot->m11-rot->m22-rot->m33+1)/4.0;
	double ySquared = (-rot->m11+rot->m22-rot->m33+1)/4.0;
	double zSquared = (-rot->m11-rot->m22-rot->m33+1)/4.0;

	double max = max(max(wSquared, zSquared), max(xSquared, ySquared));
    if(max == wSquared){
		w = sqrt(wSquared);
		x = ((rot->m32-rot->m23)/4.0)/w;
		y = ((rot->m13-rot->m31)/4.0)/w;
		z = ((rot->m21-rot->m12)/4.0)/w;
	}
	else if(max == xSquared){
		x = sqrt(xSquared);
		w = ((rot->m32-rot->m23)/4.0)/x;
		y = ((rot->m21+rot->m12)/4.0)/x;
		z = ((rot->m13+rot->m31)/4.0)/x;
	}
	else if( max == ySquared){
		y = sqrt(ySquared);
		w = ((rot->m13-rot->m31)/4.0)/y;
		x = ((rot->m21+rot->m12)/4.0)/y;
		z = ((rot->m23+rot->m32)/4.0)/y;
	}
	else{
		z = sqrt(zSquared);
		w = ((rot->m21-rot->m12)/4.0)/z;
		y = ((rot->m23+rot->m32)/4.0)/z;
		x = ((rot->m13+rot->m31)/4.0)/z;

	}
	*/
	Vector3 axis = Vector3();
	double angle = 0.0;
	rot.toAxisAngle(axis, angle);
	mX=axis.x();
	mY=axis.y();
	mZ=axis.z();
	mW=angle;
	normalize();
}

}