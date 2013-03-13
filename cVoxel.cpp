#pragma once
#include "cVoxel.h"

void cUnpackedVoxel::FromVoxel(cVoxel voxel)
{
	short data = voxel.getData();
	Alpha = (data & 0x8000)>>15; //Maschera per il segno
	Red = (data & 0x7C00)>>10;   //Maschera per i 5 bit rossi
	Green = (data & 0x3E0)>>5;  //Maschera per i 5 bit verdi
	Blue = data & 0x1F;	   //Maschera per i 5 bit blu
}

//########################################################
//class cVoxelChunk

void cVoxelChunk::setSlices(cVoxelSlice* slices)
{
	//if(!WritingIsLocked)
		//Slice = slices;
}
	
void cVoxelChunk::setVoxel(short x, short y, short z, cVoxel voxel)
{
		Slice[y].data[x][z] = voxel;
}

cVoxel cVoxelChunk::getVoxel(short x, short y, short z)
{
	return Slice[y].data[x][z];
}

/*
Cerca il voxel alle coordinate x y z 
Aggiunge ai vettori il quad del voxel che ha come normale cVec3(xNor,yNor,zNor);
									    Y
	O-------------O			0  1		A
	| 		    . |			2  3		|
	|		  .	  |						O-->X
	|	   . 	  |						
	|	.	 	  |						
	| .			  |						
	O-------------O

	trovare num di vertici già presenti = mVertexDataVector.size()
	inserire vertice 0
	inserire vertice 1
	inserire vertice 2
	inserire vertice 3

	inserire indici 0 1 2  + mVertexDataVector.size()
	inserire indici 1 2 3  + mVertexDataVector.size()
	*/
void cVoxelChunk::AddQuad(short x, short y, short z, 
			     short xNor, short yNor, short zNor,
				 std::vector<sColorVertex> & VertexVector,
				 std::vector<unsigned int> & IndexVector)
{
	sColorVertex TempVertex;
	cUnpackedVoxel TempVoxel;

	TempVoxel.FromVoxel(Slice[y].data[x][z]);
	//Proprietà in comune tra i vertici
	TempVertex.Nor = cVec3((float)xNor,(float)yNor,(float)zNor);
	TempVertex.Nor.Normalize();
	TempVertex.Col = cVec3(TempVoxel.Red, TempVoxel.Green, TempVoxel.Blue);
	TempVertex.Col.Normalize();
	unsigned int nVertici = VertexVector.size();
	if(xNor)
	{
		//V0
		TempVertex.Pos = cVec3(x+(float)xNor/2, y+0.5f, z+0.5f);
		VertexVector.push_back(TempVertex);
		//V1
		TempVertex.Pos = cVec3(x+(float)xNor/2, y+0.5f, z-0.5f);
		VertexVector.push_back(TempVertex);
		//V2
		TempVertex.Pos = cVec3(x+(float)xNor/2, y-0.5f, z+0.5f);
		VertexVector.push_back(TempVertex);
		//V3
		TempVertex.Pos = cVec3(x+(float)xNor/2, y-0.5f, z-0.5f);
		VertexVector.push_back(TempVertex);
		if(xNor>0)
		{
			IndexVector.push_back(nVertici+1);
			IndexVector.push_back(nVertici);
			IndexVector.push_back(nVertici+2);
			
			IndexVector.push_back(nVertici+1);
			IndexVector.push_back(nVertici+2);
			IndexVector.push_back(nVertici+3);
		}
		else
		{
			IndexVector.push_back(nVertici+2);
			IndexVector.push_back(nVertici);
			IndexVector.push_back(nVertici+1);
	
			IndexVector.push_back(nVertici+3);
			IndexVector.push_back(nVertici+2);
			IndexVector.push_back(nVertici+1);
		}
	}
	else if(yNor)
	{
		//V0
		TempVertex.Pos = cVec3(x-0.5f, y+(float)yNor/2 , z+0.5f);
		VertexVector.push_back(TempVertex);
		//V1
		TempVertex.Pos = cVec3(x-0.5f, y+(float)yNor/2 , z-0.5f);
		VertexVector.push_back(TempVertex);
		//V2
		TempVertex.Pos = cVec3(x+0.5f, y+(float)yNor/2 , z+0.5f);
		VertexVector.push_back(TempVertex);
		//V3
		TempVertex.Pos = cVec3(x+0.5f, y+(float)yNor/2 , z-0.5f);
		VertexVector.push_back(TempVertex);
		if(yNor>0)
		{
			IndexVector.push_back(nVertici+1);
			IndexVector.push_back(nVertici);
			IndexVector.push_back(nVertici+2);
			
			IndexVector.push_back(nVertici+1);
			IndexVector.push_back(nVertici+2);
			IndexVector.push_back(nVertici+3);
		}
		else
		{
			IndexVector.push_back(nVertici+2);
			IndexVector.push_back(nVertici);
			IndexVector.push_back(nVertici+1);
	
			IndexVector.push_back(nVertici+3);
			IndexVector.push_back(nVertici+2);
			IndexVector.push_back(nVertici+1);
		}
	}
	else if(zNor)
	{
		//V0
		TempVertex.Pos = cVec3(x-0.5f, y+0.5f , z+(float)zNor/2);
		VertexVector.push_back(TempVertex);
		//V1
		TempVertex.Pos = cVec3(x+0.5f, y+0.5f , z+(float)zNor/2);
		VertexVector.push_back(TempVertex);
		//V2
		TempVertex.Pos = cVec3(x-0.5f, y-0.5f , z+(float)zNor/2);
		VertexVector.push_back(TempVertex);
		//V3
		TempVertex.Pos = cVec3(x+0.5f, y-0.5f , z+(float)zNor/2);
		VertexVector.push_back(TempVertex);
		if(zNor>0)
		{
			IndexVector.push_back(nVertici+1);
			IndexVector.push_back(nVertici);
			IndexVector.push_back(nVertici+2);
			
			IndexVector.push_back(nVertici+1);
			IndexVector.push_back(nVertici+2);
			IndexVector.push_back(nVertici+3);
		}
		else
		{
			IndexVector.push_back(nVertici+2);
			IndexVector.push_back(nVertici);
			IndexVector.push_back(nVertici+1);
	
			IndexVector.push_back(nVertici+3);
			IndexVector.push_back(nVertici+2);
			IndexVector.push_back(nVertici+1);
		}
	}
	

}

void cVoxelChunk::Update()
{
	WritingIsLocked = true;
	//Crea mesh...
	if(Mesh!=NULL)
	{
		Mesh->~cVoxelMesh();
		free(Mesh);
	}

	Mesh = new cVoxelMesh();

	static std::vector<sColorVertex>		mVertexDataVector;
	static std::vector<unsigned int>		mIndexDataVector;
	
	//std::cout<<"*Costruzione chunk voxel...\n";
	for(int y=0;y<CHUNK_HEIGHT;y++)			//Y = altezza
		for(int x=0;x<CHUNK_SIZE;x++)		//X = Larghezza
			for(int z=0;z<CHUNK_SIZE;z++)	//Z = Profondità
			{
				if(Slice[y].data[x][z].getData()<0)
				{
					//################################################
					//Valuta X
					if(x==0)
					{
						AddQuad(x,y,z,
								-1,0,0, 
								mVertexDataVector, 
								mIndexDataVector);
					}
					else if(Slice[y].data[x-1][z].getData()>=0)
					{
						AddQuad(x,y,z,
								-1,0,0, 
								mVertexDataVector, 
								mIndexDataVector);
					}
					if(x==CHUNK_SIZE-1)
					{
						AddQuad(x,y,z,
								1,0,0, 
								mVertexDataVector, 
								mIndexDataVector);
					}
					else if(Slice[y].data[x+1][z].getData()>=0)
					{
						AddQuad(x,y,z,
								1,0,0, 
								mVertexDataVector, 
								mIndexDataVector);
					}
					

					//################################################
					//Valuta Y
					if(y==0)
					{
						/*AddQuad(x,y,z,
								0,-1,0, 
								mVertexDataVector, 
								mIndexDataVector);*/
					}
					else if(Slice[y-1].data[x][z].getData()>=0)
					{
						AddQuad(x,y,z,
								0,-1,0, 
								mVertexDataVector, 
								mIndexDataVector);
					}

					if(y==CHUNK_HEIGHT-1)
					{
						AddQuad(x,y,z,
								0,1,0, 
								mVertexDataVector, 
								mIndexDataVector);
					}
					else if(Slice[y+1].data[x][z].getData()>=0)
					{
						AddQuad(x,y,z,
								0,1,0, 
								mVertexDataVector, 
								mIndexDataVector);
					}
					
			

					//################################################
					//Valuta Z
					if(z==0)
					{
						AddQuad(x,y,z,
								0,0,-1, 
								mVertexDataVector, 
								mIndexDataVector);
					}
					else if(Slice[y].data[x][z-1].getData()>=0)
					{
						AddQuad(x,y,z,
								0,0,-1, 
								mVertexDataVector, 
								mIndexDataVector);
					}

					if(z==CHUNK_SIZE-1)
					{
						AddQuad(x,y,z,
								0,0,1, 
								mVertexDataVector, 
								mIndexDataVector);
					}
					else if(Slice[y].data[x][z+1].getData()>=0)
					{
						AddQuad(x,y,z,
								0,0,1, 
								mVertexDataVector, 
								mIndexDataVector);
					}
					
				}
				

			}

	int nVertici = mVertexDataVector.size();
	int nIndici = mIndexDataVector.size();
	//std::cout<<"\t-Vertici: "<<nVertici<<std::endl;
	//std::cout<<"\t-Indici: "<<nIndici<<std::endl;
	//std::cout<<"\t-Facce: "<<nIndici/3<<std::endl;
	Mesh->SetData(mVertexDataVector.data(), nVertici,
				  mIndexDataVector.data(), nIndici  );
	mVertexDataVector.clear();
	mIndexDataVector.clear();
	
}

void cVoxelChunk::MemZero()
{
	for(int i =0 ;i<CHUNK_HEIGHT;i++)
		Slice[i].MemZero();
}

void cVoxelChunk::Draw()
{
		Mesh->Draw();
	WritingIsLocked = false;
}

/*
	TODO:
bool cVoxelChunk::TestIntersection(cFrustum frustum);
bool cVoxelChunk::TestIntersection(cSphere sphere);
bool cVoxelChunk::TestIntersection(cRay ray);

cVoxel cVoxelChunk::getTargetedVoxel(cRay ray); 
*/

