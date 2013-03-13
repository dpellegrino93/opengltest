#ifndef CQUATERNION_H
#define CQUATERNION_H

#include "main.h"
#include "cVec3.h"
#include "cMatrix4.h"

class cQuaternion
{
public:
	float W;
	float X;
	float Y;
	float Z;
	
	cQuaternion()
	{
		W=1;
		X = Y = Z = 0;
	};

	cQuaternion(float w, float x, float y, float z)
	{
		W=w;
		X=x;
		Y=y;
		Z=z;
	}

	cQuaternion(float wxyz[4])
	{
		W=wxyz[0];
		X=wxyz[1];
		Y=wxyz[2];
		Z=wxyz[3];
	}

	cQuaternion(float w, cVec3 xyz)
	{
		W=W;
		X=xyz.X;
		Y=xyz.Y;
		Z=xyz.Z;
	}

	void Normalize()
	{
		static float len = sqrt(W * W + X * X + Y * Y + Z * Z);
		W /= len;
		X /= len;
		Y /= len;
		Z /= len;
	}
	
	cQuaternion GetConjugate()
	{
		return cQuaternion(W,-X,-Y,-Z);
	}

	inline cQuaternion operator* (const cQuaternion B) const
	{

		return cQuaternion(W*B.W - X*B.X - Y*B.Y - Z*B.Z
						  ,W*B.X + X*B.W + Y*B.Z - Z*B.Y
						  ,W*B.Y + Y*B.W + Z*B.X - X*B.Z
						  ,W*B.Z + Z*B.W + X*B.Y - Y*B.X);

	}

	inline cVec3 operator* (const cVec3 &B) const
	{
		cVec3 Vec = cVec3(B);
		Vec.Normalize();
 
		cQuaternion VecQuat, ResQuat;
		VecQuat.X = Vec.X;
		VecQuat.Y = Vec.Y;
		VecQuat.Z = Vec.Z;
		VecQuat.W = 0.0f;
 
		ResQuat = VecQuat * cQuaternion(W,-X,-Y,-Z);
		ResQuat = *this * ResQuat;
 
		return (cVec3(ResQuat.X, ResQuat.Y, ResQuat.Z));
	}

	void FromEuler(float pitch, float yaw, float roll)
	{
		static float p,y,r;
		p = pitch * (float)PId180 / 2.0f;
		y = yaw * (float)PId180 / 2.0f;
		r = roll * (float)PId180 / 2.0f;
		static float sinp, siny, sinr, cosp, cosy, cosr;
		sinp = sin(p);
		siny = sin(y);
		sinr = sin(r);
		cosp = cos(p);
		cosy = cos(y);
		cosr = cos(r);
		
		W = cosr * cosp * cosy + sinr * sinp * siny;

		X = sinr * cosp * cosy - cosr * sinp * siny;
		Y = cosr * sinp * cosy + sinr * cosp * siny;
		Z = cosr * cosp * siny - sinr * sinp * cosy;
 
		Normalize();
	}
	
	cMatrix4 GetMatrix()
	{
		static float x2,y2,z2,xy,xz,yz,wx,wy,wz;
		x2 = X * X;
		y2 = Y * Y;
		z2 = Z * Z;
		xy = X * Y;
		xz = X * Z;
		yz = Y * Z;
		wx = W * X;
		wy = W * Y;
		wz = W * Z;
 
		return cMatrix4( 1.0f - 2.0f * (y2 + z2), 2.0f * (xy - wz), 2.0f * (xz + wy), 0.0f,
				2.0f * (xy + wz), 1.0f - 2.0f * (x2 + z2), 2.0f * (yz - wx), 0.0f,
				2.0f * (xz - wy), 2.0f * (yz + wx), 1.0f - 2.0f * (x2 + y2), 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f);
	}

	float* GetFloatMatrix()
	{
		static float x2,y2,z2,xy,xz,yz,wx,wy,wz;
		x2 = X * X;
		y2 = Y * Y;
		z2 = Z * Z;
		xy = X * Y;
		xz = X * Z;
		yz = Y * Z;
		wx = W * X;
		wy = W * Y;
		wz = W * Z;
 
		return cMatrix4( 1.0f - 2.0f * (y2 + z2), 2.0f * (xy - wz), 2.0f * (xz + wy), 0.0f,
				2.0f * (xy + wz), 1.0f - 2.0f * (x2 + z2), 2.0f * (yz - wx), 0.0f,
				2.0f * (xz - wy), 2.0f * (yz + wx), 1.0f - 2.0f * (x2 + y2), 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f).M;
	}

};


#endif