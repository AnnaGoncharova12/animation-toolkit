#include "atkmath/matrix3.h"
#include "atkmath/quaternion.h"

namespace atkmath {

Vector3 Matrix3::toEulerAnglesXYZ() const
{
   float angleY=0.0f;
   float angleX=0.0f;
   float angleZ=0.0f;
   float helpTerm=this->m13;
   if(helpTerm==1){
        return Vector3(atan2(this->m32, this->m22), PI/2, 0);
   }
   else if(helpTerm==-1){
      return Vector3(atan2(this->m32, this->m22), -PI/2, 0);
   }
   else{
      angleY=asin(helpTerm);
      angleX=atan2(-(this->m23), this->m33);
      angleZ=atan2(-(this->m12), this->m11);
      return Vector3(angleX, angleY, angleZ);
   }
  
}

Vector3 Matrix3::toEulerAnglesXZY() const
{
   float angleY=0.0f;
   float angleX=0.0f;
   float angleZ=0.0f;
   float helpTerm=-(this->m12);
   if(helpTerm==1){
        return Vector3(0.0f,atan2(this->m23, this->m33), PI/2);
   }
   else if(helpTerm==-1){
      return Vector3(0.0f,atan2(-(this->m23), this->m33), -PI/2);
   }
   else{
      angleZ=asin(helpTerm);
      angleY=atan2(this->m13, this->m11);
      angleX=atan2(this->m32, this->m22);
      return Vector3(angleX, angleY, angleZ);
   }
}


Vector3 Matrix3::toEulerAnglesYXZ() const
{
   float angleY=0.0f;
   float angleX=0.0f;
   float angleZ=0.0f;
   float helpTerm=(this->m23);
   if(helpTerm==-1){
      return  Vector3(PI/2, 0.0f,atan2(this->m31, this->m32));
   }
   else if(helpTerm==1){
      return Vector3(-PI/2,atan2(-(this->m31),-(this->m32)),0.0f);
   }
   else{
      angleX=asin(-helpTerm);
      angleY=atan2(this->m13, this->m33);
      angleZ=atan2(this->m21, this->m22);
      return Vector3(angleX, angleY, angleZ);
   
   }
}

Vector3 Matrix3::toEulerAnglesYZX() const
{
   float angleY=0.0f;
   float angleX=0.0f;
   float angleZ=0.0f;
   float helpTerm=(this->m21);
   if(helpTerm==1){
      return Vector3(atan2(this->m13, this->m33),0.0f,PI/2);
   }
   else if(helpTerm==-1){
      return Vector3(atan2(this->m32, this->m12), 0.0f, -PI/2);
   }
   else{
      angleX=atan2(-(this->m23), this->m22);
      angleY=atan2(-(this->m31), this->m11);
      angleZ=asin(helpTerm);
      return Vector3(angleX, angleY, angleZ);
   
   }
}

Vector3 Matrix3::toEulerAnglesZXY() const
{
    float helpTerm=(this->m32);
    float angleX=asin(helpTerm);
    float angleY=atan2(-(this->m31), this->m33);
    float angleZ=atan2(-(this->m12), this->m22);
    if(helpTerm==1){
       return Vector3(PI/2,atan2(this->m13, -(this->m23)), 0.0f);
    }
    else if(helpTerm==-1){
       return Vector3(-PI/2, 0.0f, atan2(this->m21, this->m11));
    }
    else{
       
         return Vector3(angleX, angleY, angleZ);
    }
}

Vector3 Matrix3::toEulerAnglesZYX() const
{
   float helpTerm=(this->m31);
   float angleY=asin(-helpTerm);
   float angleZ=atan2(this->m21, this->m11);
   float angleX=atan2(this->m32, this->m33);
   if(helpTerm==-1){
      return Vector3(atan2(this->m12, this->m22), PI/2, 0.0f);
   }
   else if(helpTerm==1){
       return Vector3(atan2(-(this->m12), -(this->m13)), -PI/2,0.0f);
   }
   else{
        return Vector3(angleX, angleY, angleZ);
   }
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