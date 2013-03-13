#include "cLight.h"


void cLight::SetColor(cVec3 color)
{
	mColor = color;
}

void cLight::SetColor(float r, float g, float b)
{
	mColor.X = r;
	mColor.Y = g;
	mColor.Z = b;
}

cVec3 cLight::GetColor()
{
	return mColor;
}

void  cLight::SetRadius(float radius)
{
	mRadius = radius;
}

void cLight::SetFalloff(cVec3 falloff)
{
	mFalloff = falloff;
}

void cLight::SetFalloff(float Constant, float Linear, float Quadratic)
{
	mFalloff.X = Constant;
	mFalloff.Y = Linear;
	mFalloff.Z = Quadratic;
}

cVec3 cLight::GetFalloff()
{
	return mFalloff;
}