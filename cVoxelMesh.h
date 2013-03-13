//##############################
//Triangle Mesh per voxel
//Da sostituire con una template class cStaticMesh
/* Es:
  cStaticMesh<sVertex>			MeshNormale;
  cStaticMesh<sColorVertex>		MeshVoxel;

*/
#pragma once

#include "main.h"
#include "sVertex-sTexCoord.h"
#include "cQuaternion.h"
#include "cMatrix4.h"
#include "cTexture.h"
#include "cEntity-cResource.h"

class cVoxelMesh:
	public cResource
{
protected:
	sColorVertex*	mVertexData;
	unsigned int*	mIndexData;
	GLuint			mVBOIDVertex;
	GLuint			mVBOIDIndex;
	
public:
	cVoxelMesh()
	{
		mResourceType = "VoxelMesh";
		mVertexData = NULL;
		mIndexData = NULL;
		mVertexCount = 0;
		mIndexCount = 0;
	}

	~cVoxelMesh()
	{
		glDeleteBuffers(1,&mVBOIDVertex);
		glDeleteBuffers(1,&mVBOIDIndex);
	}

	unsigned int	mVertexCount;
	unsigned int	mIndexCount;

	void			SetData(sColorVertex* VertexData, unsigned int VertexCount, unsigned int* IndexData, unsigned int IndexCount);
	sColorVertex*	GetVertexData();
	unsigned int*	GetIndexData();
	unsigned int	GetVertexCount();
	unsigned int	GetIndexCount();
	void			CreateVBOs();
	GLuint			GetVBOIDVertex();
	GLuint			GetVBOIDIndex();
	
	virtual void	Draw();
};
