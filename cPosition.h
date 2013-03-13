#pragma once
#include "main.h"
#include "cQuaternion.h"
#include "cMatrix4.h"

class cPosition
{
protected:
	cMatrix4 ModelTrasform;
	cQuaternion Rotation;
	bool isLocked;
public:
	cPosition()
	{
		isLocked = true;
	};

	void SetPosition(cVec3 Pos);
	void SetPosition(float x, float y, float z);
	cVec3 GetPosition();

	void Traslate(cVec3 Vec);
	void Traslate(float x, float y, float z);

	void SetRotation(cQuaternion rotation);
	void SetRotationEuler(float pitch, float roll, float yaw);

	void LockMovement();
	void UnlockMovement();
	float* GetMatrix();

};