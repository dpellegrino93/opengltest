#include "cCamera.h"


void cCamera::SetPosition(float x, float y, float z)
{
	CameraTrasform.M[12]=x;
	CameraTrasform.M[13]=y;
	CameraTrasform.M[14]=z;
}

void cCamera::SetPosition(cVec3 Pos)
{
	CameraTrasform.M[12]=Pos.X;
	CameraTrasform.M[13]=Pos.Y;
	CameraTrasform.M[14]=Pos.Z;
}

cVec3 cCamera::GetPosition()
{
	return cVec3(CameraTrasform.M[12],
				 CameraTrasform.M[13],
				 CameraTrasform.M[14]);
}

void cCamera::Traslate(cVec3 Vec)
{
	CameraTrasform.M[12]+=Vec.X;
	CameraTrasform.M[13]+=Vec.Y;
	CameraTrasform.M[14]+=Vec.Z;
}

void cCamera::Traslate(float x, float y, float z)
{
	CameraTrasform.M[12]+=x;
	CameraTrasform.M[13]+=y;
	CameraTrasform.M[14]+=z;
}

void cCamera::SetRotationEuler(float pitch, float roll, float yaw)
{
	Rotation.FromEuler(yaw,roll,pitch);
	CameraTrasform.SetRotation(Rotation.GetFloatMatrix());
}

void cCamera::RotateEuler(float pitch, float roll, float yaw)
{
	cQuaternion Rotate;
	Rotate.FromEuler(yaw,roll,pitch);
	Rotation = Rotation * Rotate;
	CameraTrasform.SetRotation(Rotation.GetFloatMatrix());
}

float* cCamera::GetMatrix()
{
	return CameraTrasform.M;
}

float* cCamera::GetMatrixInverse()
{
	return CameraTrasform.Inverse().M;
}


void cCamera::SetProjection()
{

}

void cCamera::Draw()
{
	//glMultMatrixf(CameraTrasform.Inverse().M);	
}
void cCamera::Update(double GameTime)
{
}

void cCamera::UpdateNoclip(double GameTime)
{
	/*
	RotateEuler( (keyStates['k']-keyStates['i'])*GameTime*200,
								0,
								(keyStates['j']-keyStates['l'])*GameTime*200);


	cVec3 Mov =   cVec3( (keyStates['d']-keyStates['a']),
						 (keyStates[' ']-keyStates['c']),
						 (keyStates['s']-keyStates['w'])  ) ;

	Traslate( Rotation * Mov * (float)mSpeed*(float)GameTime);
	*/

}
