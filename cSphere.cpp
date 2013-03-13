#include "cSphere.h"
#include "hMath.h"

cVec3 cSphere::getCenter()
{
	return Center;
}

float cSphere::getRadius()
{
	return Radius;
}

void cSphere::setCenter(cVec3 center)
{
	Center = center;
}

void cSphere::setCenter(float x, float y, float z)
{
	Center = cVec3(x,y,z);
}
	
void cSphere::setRadius(float radius)
{
	Radius = radius;
}

bool cSphere::TestPoint(cVec3 &point)
{
	return (Center-point).Length() <= Radius;
}

bool cSphere::TestSphere(cSphere &sphere)
{
	return (Center-sphere.getCenter()).Length() <= (Radius+sphere.getRadius());
}

bool  cSphere::TestAABox(cAABox &aabox){return false;};

bool  cSphere::TestFrustum(cFrustum &frustum){return false;};