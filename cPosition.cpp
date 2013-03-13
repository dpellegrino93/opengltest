#include "cPosition.h"


void cPosition::SetPosition(float x, float y, float z)
{
	if(!isLocked)
	{
		ModelTrasform.M[12]=x;
		ModelTrasform.M[13]=y;
		ModelTrasform.M[14]=z;
	}
}

void cPosition::SetPosition(cVec3 Pos)
{
	if(!isLocked)
	{
		ModelTrasform.M[12]=Pos.X;
		ModelTrasform.M[13]=Pos.Y;
		ModelTrasform.M[14]=Pos.Z;
	}
}

cVec3 cPosition::GetPosition()
{
	return cVec3(ModelTrasform.M[12],
				 ModelTrasform.M[13],
				 ModelTrasform.M[14]);
}

void cPosition::Traslate(cVec3 Vec)
{
	if(!isLocked)
	{
		ModelTrasform.M[12]+=Vec.X;
		ModelTrasform.M[13]+=Vec.Y;
		ModelTrasform.M[14]+=Vec.Z;
	}
}

void cPosition::Traslate(float x, float y, float z)
{
	if(!isLocked)
	{
		ModelTrasform.M[12]+=x;
		ModelTrasform.M[13]+=y;
		ModelTrasform.M[14]+=z;
	}
}

void cPosition::SetRotation(cQuaternion rotation)
{
	if(!isLocked)
		Rotation = rotation;
	ModelTrasform.SetRotation(Rotation.GetFloatMatrix());
}

void cPosition::SetRotationEuler(float pitch, float roll, float yaw)
{
	if(!isLocked)
		Rotation.FromEuler(yaw,roll,pitch);
	ModelTrasform.SetRotation(Rotation.GetFloatMatrix());
}


float* cPosition::GetMatrix()
{
	return ModelTrasform.M;
}

void cPosition::LockMovement()
{
	isLocked = true;
}

void cPosition::UnlockMovement()
{
	isLocked = false;
}
