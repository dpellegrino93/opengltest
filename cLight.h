#pragma once
#include "main.h"
#include "cEntity-cResource.h"
#include "cPosition.h"

class cLight:
	public cEntity,
	public cPosition
{
protected:
	cVec3 mColor;
	float mRadius;
	cVec3 mFalloff;	//Costante-Lineare-Quadratico

public:
	cLight()
	{
		isLocked = false;
		mEntityType = "Light";
	}

	void SetColor(cVec3 color);
	void SetColor(float r, float g, float b);
	cVec3 GetColor();
	void SetRadius(float radius);
	void SetFalloff(cVec3 falloff);
	void SetFalloff(float Constant, float Linear, float Quadratic);
	cVec3 GetFalloff();

};