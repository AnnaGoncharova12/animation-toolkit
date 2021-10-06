#include "atkmath/matrix3.h"
#include "atkmath/quaternion.h"

namespace atkmath {

Vector3 Matrix3::toEulerAnglesXYZ() const
{
   return Vector3();
}

Vector3 Matrix3::toEulerAnglesXZY() const
{
   return Vector3();
}

Vector3 Matrix3::toEulerAnglesYXZ() const
{
   return Vector3();
}

Vector3 Matrix3::toEulerAnglesYZX() const
{
   return Vector3();
}

Vector3 Matrix3::toEulerAnglesZXY() const
{
   return Vector3();
}

Vector3 Matrix3::toEulerAnglesZYX() const
{
   return Vector3();
}

void Matrix3::fromEulerAnglesXYZ(const Vector3& angleRad)
{
   Matrix3 myRz=Rz(angleRad[2]);
   Matrix3 myRy=Ry(angleRad[1]);
   Matrix3 myRx=Rx(angleRad[0]);
   Matrix3 intermediate = operator * (myRx,myRy);
   *this = operator * (intermediate, myRz);
}

void Matrix3::fromEulerAnglesXZY(const Vector3& angleRad)
{
   Matrix3 myRz=Rz(angleRad[2]);
   Matrix3 myRy=Ry(angleRad[1]);
   Matrix3 myRx=Rx(angleRad[0]);
   Matrix3 intermediate = operator * (myRx,myRz);
   *this = operator * (intermediate, myRy);
}

void Matrix3::fromEulerAnglesYXZ(const Vector3& angleRad)
{
   Matrix3 myRz=Rz(angleRad[2]);
   Matrix3 myRy=Ry(angleRad[1]);
   Matrix3 myRx=Rx(angleRad[0]);
   Matrix3 intermediate = operator * (myRy,myRx);
   *this = operator * (intermediate, myRz);
}

void Matrix3::fromEulerAnglesYZX(const Vector3& angleRad)
{
   Matrix3 myRz=Rz(angleRad[2]);
   Matrix3 myRy=Ry(angleRad[1]);
   Matrix3 myRx=Rx(angleRad[0]);
   Matrix3 intermediate = operator * (myRy,myRz);
   *this = operator * (intermediate, myRx);
}

void Matrix3::fromEulerAnglesZXY(const Vector3& angleRad)
{
   Matrix3 myRz=Rz(angleRad[2]);
   Matrix3 myRy=Ry(angleRad[1]);
   Matrix3 myRx=Rx(angleRad[0]);
   Matrix3 intermediate = operator * (myRz,myRx);
   *this = operator * (intermediate, myRy);
}

void Matrix3::fromEulerAnglesZYX(const Vector3& angleRad)
{
   Matrix3 myRz=Rz(angleRad[2]);
   Matrix3 myRy=Ry(angleRad[1]);
   Matrix3 myRx=Rx(angleRad[0]);
   Matrix3 intermediate = operator * (myRz,myRy);
   *this = operator * (intermediate, myRx);
}

void Matrix3::toAxisAngle(Vector3& axis, double& angleRad) const
{
   // TODO
}

void Matrix3::fromAxisAngle(const Vector3& axis, double angleRad)
{
   // TODO
   *this = Identity;
}

Matrix3 Matrix3::Rx(float angle){
   Matrix3 toReturn = Matrix3(1.0, 0.0, 0.0, 0.0, cos(angle), -sin(angle), 0.0, sin(angle), cos(angle) );
   return toReturn;
}
Matrix3 Matrix3::Ry(float angle){
   Matrix3 toReturn = Matrix3(cos(angle), 0.0, sin(angle), 0.0, 1.0, 0.0, -sin(angle), 0.0, cos(angle) );
   return toReturn;
}
Matrix3 Matrix3::Rz(float angle){
   Matrix3 toReturn = Matrix3(cos(angle), -sin(angle), 0.0, sin(angle), cos(angle), 0.0, 0.0, 0.0, 1.0);
   return toReturn;
}

}