#include "main.h"

#ifndef CMATRIX4_H
#define CMATRIX4_H


class cMatrix4
{
public:
	float M[16];

	cMatrix4()
	{
		M[0]=1;		M[4]=0;		M[8]=0;		M[12]=0;
		M[1]=0;		M[5]=1;		M[9]=0;		M[13]=0;
		M[2]=0;		M[6]=0;		M[10]=1;	M[14]=0;
		M[3]=0;		M[7]=0;		M[11]=0;	M[15]=1;
	};

	cMatrix4(float m[16])
	{
		memcpy(M,m,64);
	}


	cMatrix4(float m0, float m4, float m8, float m12
			,float m1, float m5, float m9, float m13
			,float m2, float m6, float m10, float m14
			,float m3, float m7, float m11, float m15)
	{
		M[0]=m0;		M[4]=m4;		M[8]=m8;		M[12]=m12;
		M[1]=m1;		M[5]=m5;		M[9]=m9;		M[13]=m13;
		M[2]=m2;		M[6]=m6;		M[10]=m10;		M[14]=m14;
		M[3]=m3;		M[7]=m7;		M[11]=m11;		M[15]=m15;
	}


	inline void SetRotation( float m[16] )
	{  //x				//y				//z
		M[0]=m[0];		M[4]=m[4];		M[8]=m[8];	
		M[1]=m[1];		M[5]=m[5];		M[9]=m[9];		
		M[2]=m[2];		M[6]=m[6];		M[10]=m[10];
	}

	inline void Traslate( cVec3 vec )
	{
		M[12] += vec.X;
		M[13] += vec.Y;
		M[14] += vec.Z;
	}

	inline cMatrix4 Inverse()
	{
		static float inv[16], det;
		int i;

		static float m[16];
		memcpy(m,M,64);

		inv[0] =   m[5]*m[10]*m[15] - m[5]*m[11]*m[14] - m[9]*m[6]*m[15] + m[9]*m[7]*m[14] + m[13]*m[6]*m[11] - m[13]*m[7]*m[10];
		inv[4] =  -m[4]*m[10]*m[15] + m[4]*m[11]*m[14] + m[8]*m[6]*m[15] - m[8]*m[7]*m[14] - m[12]*m[6]*m[11] + m[12]*m[7]*m[10];
		inv[8] =   m[4]*m[9]*m[15] - m[4]*m[11]*m[13] - m[8]*m[5]*m[15] + m[8]*m[7]*m[13] + m[12]*m[5]*m[11] - m[12]*m[7]*m[9];
		inv[12] = -m[4]*m[9]*m[14] + m[4]*m[10]*m[13] + m[8]*m[5]*m[14] - m[8]*m[6]*m[13] - m[12]*m[5]*m[10] + m[12]*m[6]*m[9];
		inv[1] =  -m[1]*m[10]*m[15] + m[1]*m[11]*m[14] + m[9]*m[2]*m[15] - m[9]*m[3]*m[14] - m[13]*m[2]*m[11] + m[13]*m[3]*m[10];
		inv[5] =   m[0]*m[10]*m[15] - m[0]*m[11]*m[14] - m[8]*m[2]*m[15] + m[8]*m[3]*m[14] + m[12]*m[2]*m[11] - m[12]*m[3]*m[10];
		inv[9] =  -m[0]*m[9]*m[15] + m[0]*m[11]*m[13] + m[8]*m[1]*m[15] - m[8]*m[3]*m[13] - m[12]*m[1]*m[11] + m[12]*m[3]*m[9];
		inv[13] =  m[0]*m[9]*m[14] - m[0]*m[10]*m[13] - m[8]*m[1]*m[14] + m[8]*m[2]*m[13] + m[12]*m[1]*m[10] - m[12]*m[2]*m[9];

		inv[2] =   m[1]*m[6]*m[15] - m[1]*m[7]*m[14] - m[5]*m[2]*m[15] + m[5]*m[3]*m[14] + m[13]*m[2]*m[7] - m[13]*m[3]*m[6];
		inv[6] =  -m[0]*m[6]*m[15] + m[0]*m[7]*m[14] + m[4]*m[2]*m[15] - m[4]*m[3]*m[14] - m[12]*m[2]*m[7] + m[12]*m[3]*m[6];
		inv[10] =  m[0]*m[5]*m[15] - m[0]*m[7]*m[13] - m[4]*m[1]*m[15] + m[4]*m[3]*m[13] + m[12]*m[1]*m[7] - m[12]*m[3]*m[5];
		inv[14] = -m[0]*m[5]*m[14] + m[0]*m[6]*m[13] + m[4]*m[1]*m[14] - m[4]*m[2]*m[13] - m[12]*m[1]*m[6] + m[12]*m[2]*m[5];
		inv[3] =  -m[1]*m[6]*m[11] + m[1]*m[7]*m[10] + m[5]*m[2]*m[11] - m[5]*m[3]*m[10] - m[9]*m[2]*m[7] + m[9]*m[3]*m[6];
		inv[7] =   m[0]*m[6]*m[11] - m[0]*m[7]*m[10] - m[4]*m[2]*m[11] + m[4]*m[3]*m[10] + m[8]*m[2]*m[7] - m[8]*m[3]*m[6];
		inv[11] = -m[0]*m[5]*m[11] + m[0]*m[7]*m[9] + m[4]*m[1]*m[11] - m[4]*m[3]*m[9] - m[8]*m[1]*m[7] + m[8]*m[3]*m[5];
		inv[15] =  m[0]*m[5]*m[10] - m[0]*m[6]*m[9] - m[4]*m[1]*m[10] + m[4]*m[2]*m[9] + m[8]*m[1]*m[6] - m[8]*m[2]*m[5];

		det = m[0]*inv[0] + m[1]*inv[4] + m[2]*inv[8] + m[3]*inv[12];
		if (det == 0)
				return 0;

		det = 1.0f / det;

		for (i = 0; i < 16; i++)
				inv[i] *= det;

		return cMatrix4(inv);
	}

		
};


#endif