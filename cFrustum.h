#pragma once
#include "main.h"
#include "cMatrix4.h"
#include "hMathRef.h"

class cFrustum
{


private:
	cVec3 Planes[6][4];

	enum
	{
		RIGHT	= 0,		
		LEFT	= 1,		
		BOTTOM	= 2,		
		TOP		= 3,		
		BACK	= 4,		
		FRONT	= 5	
	}; 

public:
	//Ricava il frustum dalla matrice di proiezione
	void Build(cMatrix4 matrix);
	//Usato nel tiled deferred rendering
	//Ricava il frustum dalla matrice di proiezione
	//e gli indici della tile da cui ricavarlo
	void BuildTiled(cMatrix4 matrix, 
				    int xNum, int yNum, 
					int xIndex, int yIndex);

	bool TestPoint(cVec3 &point);
	bool TestSphere(cSphere &sphere);
	bool TestAABox(cAABox &aabox);
	bool TestFrustum(cFrustum &frustum);
};