#pragma once
#include "main.h"
#include "hMathRef.h"

class cAABox
{
private:
	cVec3 Min;
	cVec3 Max;

public:
	cVec3 getMin();
	cVec3 getMax();

	void setMin(cVec3 min);
	void setMin(float x, float y, float z);

	void setMax(cVec3 max);
	void setMax(float x, float y, float z);
	
	bool TestPoint(cVec3 &point);
	bool TestSphere(cSphere &sphere);
	bool TestAABox(cAABox &aabox);
	bool TestFrustum(cFrustum &frustum);
};