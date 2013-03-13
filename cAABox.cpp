#include "cAABox.h"

cVec3 cAABox::getMin(){
	return Min;
}

cVec3 cAABox::getMax(){
	return Max;
}

void cAABox::setMin(cVec3 min){
	Min = min;
}

void cAABox::setMin(float x, float y, float z){
	Min = cVec3(x,y,z);
}

void cAABox::setMax(cVec3 max){
	Max = max;
}

void cAABox::setMax(float x, float y, float z){
	Max = cVec3(x,y,z);
}

bool cAABox::TestAABox(cAABox &aabox)
{
	return false;
}