#ifndef cCamera_H
#define cCamera_H

#include "cEntity-cResource.h"
#include "cTimer.h"
#include "cMatrix4.h"
#include "cQuaternion.h"
#include "cVec3.h"


#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.01745329251994329576923690768489

class cCamera:
	public cEntity
{
protected:
	cMatrix4 CameraTrasform;
public:
	cQuaternion Rotation;

	int mSpeed;
	float vFOV;

	cCamera()
	{
		mEntityType = "Camera";
		Rotation = cQuaternion();
		mSpeed = 100;
		float vFOV = 80;
		
	};


	void SetPosition(cVec3 Pos);
	void SetPosition(float x, float y, float z);
	cVec3 GetPosition();
	void Traslate(cVec3 Vec);
	void Traslate(float x, float y, float z);
	void SetRotationEuler(float pitch, float roll, float yaw);
	void RotateEuler(float pitch, float roll, float yaw);
	float* GetMatrix();
	float* GetMatrixInverse();

	void SetProjection();
	void Update(double GameTime);
	void UpdateNoclip(double GameTime);
	void Draw();
};

#endif