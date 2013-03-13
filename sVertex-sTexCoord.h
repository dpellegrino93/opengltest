#include "main.h"
#include "cVec3.h"

#ifndef DEF_H
#define DEF_H

struct sTexCoord
{
	float U;
	float V;
	sTexCoord(){};
	sTexCoord(float u, float v)
	{
		U=u;
		V=v;
	};

	inline bool operator==(const sTexCoord B)
	{
		return(U==B.U && V==B.U);
	}
	inline bool operator!=(const sTexCoord B)
	{
		return(U!=B.U || V!=B.U);
	}


};



struct sVertex
{
	cVec3 Pos;
	cVec3 Nor;
	sTexCoord UV;

	sVertex(){};
	sVertex(cVec3 inPosition)
	{
		Pos = inPosition;
		Nor = cVec3(0,0,0);
	}

	sVertex(cVec3 inPosition, cVec3 normal, sTexCoord uv)
	{
		Pos = inPosition;
		Nor = normal;
		UV = uv;
	}

	inline bool operator==(const sVertex B)
	{
		return(Pos == B.Pos && Nor == B.Nor && UV == B.UV);
	}

	inline bool operator!=(const sVertex B)
	{
		return(Pos != B.Pos || Nor != B.Nor || UV != B.UV);
	}

	//Operatore per ordinamento mappa in cTerrain
	inline bool operator<(const sVertex that) const
	{
        return memcmp((void*)this, (void*)&that, sizeof(sVertex))>0;
    };

};

struct sAnimatedVertex
{
	cVec3 Pos;
	cVec3 Nor;
	sTexCoord UV;
	float w1, w2;
	short int b1, b2;
	//TODO...
};

struct sColorVertex
{
	cVec3 Pos;
	cVec3 Nor;
	cVec3 Col;

	sColorVertex(){};
	sColorVertex(cVec3 inPosition)
	{
		Pos = inPosition;
		Nor = cVec3(0,0,0);
		Col = cVec3(1,1,1);
	}

	sColorVertex(cVec3 position, cVec3 normal, cVec3 color)
	{
		Pos = position;
		Nor = normal;
		Col = color;
	}
};

#endif