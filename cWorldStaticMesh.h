#pragma once

#include "main.h"
#include "sVertex-sTexCoord.h"
#include "cQuaternion.h"
#include "cMatrix4.h"
#include "cTexture.h"
#include "cEntity-cResource.h"

class cWorldStaticMesh:
	public cResource
{
protected:
	sVertex*		mVertexData;
	unsigned int*	mIndexData;
	unsigned int	mVertexCount;
	unsigned int	mIndexCount;
	GLuint			mVBOIDVertex;
	GLuint			mVBOIDIndex;
	
public:
	cWorldStaticMesh()
	{
		mResourceType = "WorldStaticMesh";
		mVertexData = 0;
		mIndexData = 0;
	}

	void			SetData(sVertex* VertexData, unsigned int VertexCount, unsigned int* IndexData, unsigned int IndexCount);
	sVertex*		GetVertexData();
	unsigned int*	GetIndexData();
	unsigned int	GetVertexCount();
	unsigned int	GetIndexCount();
	void			CreateVBOs();
	GLuint			GetVBOIDVertex();
	GLuint			GetVBOIDIndex();
	
	virtual void	Draw();
};
