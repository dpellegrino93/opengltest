#pragma once
#include "main.h"
#include "hMathRef.h"

class cSphere
{
private:
	cVec3 Center;
	float Radius;

public:
	cVec3 getCenter();
	float getRadius();

	void setCenter(cVec3 center);
	void setCenter(float x, float y, float z);
	
	void setRadius(float radius);

	bool TestPoint(cVec3 &point);
	bool TestSphere(cSphere &sphere);
	bool TestAABox(cAABox &aabox);
	bool TestFrustum(cFrustum &frustum);
};