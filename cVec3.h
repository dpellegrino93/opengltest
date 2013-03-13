#ifndef VEC3_H
#define VEC3_H

#include "main.h"


class cVec3
{
public:
	float X, Y, Z;

	cVec3()
	{
		X = 0;
		Y = 0;
		Z = 0;
	};

	cVec3(float vX, float vY, float vZ)
	{
		X=vX;
		Y=vY;
		Z=vZ;
	}

public:
		//####################################################################
	// Operazioni Vettori


	//####################################################################
	//Ritorna lunghezza vettore
	inline float cVec3::Length()
	{
		return sqrt( X*X + Y*Y + Z*Z );
	}


	//####################################################################
	//Normalizza vettore (Length = 1)
	inline void cVec3::Normalize()
	{
		static float length;
		length = Length();
		if(length!=0)
		{
			X /= length;
			Y /= length;
			Z /= length;
		}
	};


	//####################################################################
	//Prodotto scalare
	inline float cVec3::Dot(cVec3 B)
	{
		return X*B.X + Y*B.Y + Z*B.Z;
	}


	//####################################################################
	//Prodotto vettoriale
	inline cVec3 cVec3::Cross(cVec3 B)
	{
		return cVec3(	Y*B.Z - Z*B.Y 
					  , Z*B.X - X*B.Z 
					  , X*B.Y - Y*B.X	);
	}




	//####################################################################
	//Confronto 

	inline bool operator == (cVec3 B)
	{
		return ( X == B.X && Y == B.Y && Z == B.Z );
	}

	inline bool operator != (cVec3 B)
	{
		return ( X != B.X || Y != B.Y || Z != B.Z );
	}

	//####################################################################
	//Moltiplicazione scalare
	inline cVec3 operator*(cVec3 B)
	{
		return cVec3(	X*B.X 
					  , Y*B.X 
					  , Z*B.X 	);
	}

	inline cVec3 operator*(float B)
	{
		return cVec3(	X*B 
					  , Y*B 
					  , Z*B	);
	}


	//####################################################################
	//Somma
	inline cVec3 operator+(cVec3 B)
	{
		return cVec3(	X	+ B.X
					,	Y	+ B.Y
					,	Z	+ B.Z	);
	}

	inline cVec3 operator+(float B)
	{
		return cVec3(	X + B
					,	Y + B
					,	Z + B	);
	}


	//####################################################################
	//Sottrazione
	inline cVec3 operator-(cVec3 B)
	{
		return cVec3(	X	- B.X
					,	Y	- B.Y
					,	Z	- B.Z	);
	}

	inline cVec3 operator-(float B)
	{
		return cVec3(	X - B
					,	Y - B
					,	Z - B	);
	}


	//####################################################################
	//Divisione
	inline cVec3 operator / (cVec3 B)
	{
		return cVec3(	X / B.X
					,	Y / B.Y
					,	Z / B.Z	);
	}

	inline cVec3 operator / (float B)
	{
		return cVec3(	X / B
					,	Y / B
					,	Z / B	);
	}




	};

	#endif
