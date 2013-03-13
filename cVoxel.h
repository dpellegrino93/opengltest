#pragma once
#include "main.h"
#include <vector>
#include "cVoxelMesh.h"


/*
Struttura voxel:
	-1 bit Alpha (segno)
	-5 bit Red
	-5 bit Green
	-5 bit Blue

Numeri magici:

	- 0x8000  = 1000 0000 0000 0000			bit più significativo
	- 0x7C00  = 0111 1100 0000 0000			5 bit rossi
	- 0x3E0   = 0000 0011 1110 0000			5 bit verdi
	- 0x1F	  = 0000 0000 0001 1111			5 bit blu  /  troncare a 5 bit 
*/
#define CHUNK_HEIGHT 128
#define CHUNK_SIZE   128
typedef float VoxelColor;

class cVoxel;
//Struttura dove tenere i dati del voxel
class cUnpackedVoxel
{
public:
	short Alpha;
	short Red;
	short Green;
	short Blue;

	void FromVoxel(cVoxel voxel);
};


class cVoxel
{
private:
	unsigned short data;
public:
	cVoxel()
	{
		data = 0;
	}
	inline void setData(short Data)
	{
		data = Data;
	}

	inline void setVoxel(cUnpackedVoxel voxel)
	{
		data = (voxel.Alpha&0x1)<<15 | (voxel.Red&0x1F)<<10 | (voxel.Green&0x1F)<<5 | (voxel.Blue&0x1F);
	}

	inline void setColorS(short r,short g, short b, short a)
	{
		//Unsafe: prende per certo che i valori siano <= 5 bit (1 bit per alpha)
		//data = a<<15 | r<<10 | g<<5 | b;
		
		//Safe: tronca i valori a 5 bit
		data = (a&0x1)<<15 | (r&0x1F)<<10 | (g&0x1F)<<5 | (b&0x1F);
	}

	inline void setColorF(float r, float g, float b, short a)
	{
		data = (a&0x1)<<15 | ((short)(r)&0x1F)<<10 | ((short)(g)&0x1F)<<5 | ((short)(b)&0x1F);
	}

	inline void setColorVec3(cVec3 col, short a)
	{
		data = (a&0x1)<<15 | ((short)(col.X)&0x1F)<<10 | ((short)(col.Y)&0x1F)<<5 | ((short)(col.Z)&0x1F);
	}

	inline short getData()
	{
		return data;
	}

	inline short getAlpha()
	{
		return data & 0x8000;
	}

};



class cVoxelSlice
{
	public:
	cVoxel **data;
	
	cVoxelSlice()
	{
		data = new cVoxel*[CHUNK_SIZE];
		for(int i = 0;i<CHUNK_SIZE;i++)
			data[i] = new cVoxel[CHUNK_SIZE];
	}

	void FreeAll()
	{
		for(int i = 0;i<CHUNK_SIZE;i++)
			free(data[i]);
		free(data);
		data = NULL;
	}

	void MemZero()
	{
		for(int i = 0;i<CHUNK_SIZE;i++)
			memset(data[i],0,CHUNK_SIZE*sizeof(cVoxel));
	}
};

class cVoxelChunk
{
private:
	/* X Y Z
		  O - - - O
		  | \       \ 
		  |   O - - - O
		  |   |-------|
		  |   |-------|
		  |   |-------|
		  |   |-------| CHUNK_HEIGHT
		  |   |-------|
		  O   |-------|         Y
		    \ |-------|		  	|
			  O	- - - O         O - X
			  CHUNK_SIZE	     \
								   Z
	*/		
	cVoxelSlice			*Slice;
	cVoxelMesh			*Mesh;
	//cAABox			BoundingBox;
	bool				WritingIsLocked;
	void AddQuad(short x, short y, short z, 
			     short xNor, short yNor, short zNor,
				 std::vector<sColorVertex> & VertexVector,
				 std::vector<unsigned int> & IndexVector);
public:
	cVoxelChunk()
	{
		WritingIsLocked = false;
		Slice = new cVoxelSlice[CHUNK_HEIGHT];
		Mesh = 0;
	}

	void				setSlices(cVoxelSlice* slices);
	
	void				setVoxel(short x, short y, short z, cVoxel voxel);

	cVoxel				getVoxel(short x, short y, short z);
	//UpdateMesh() blocca l'accesso esterno ai voxel
	//Se è necessario ricreare la mesh lo fa
	void				Update();
	void				MemZero();
	//Draw una volta finito sblocca l'accesso ai voxel
	void				Draw();
	/*
		TODO:
	bool				TestIntersection(cFrustum frustum);
	bool				TestIntersection(cSphere sphere);
	bool				TestIntersection(cRay ray);

	cVoxel				getTargetedVoxel(cRay ray); 
	*/
};

