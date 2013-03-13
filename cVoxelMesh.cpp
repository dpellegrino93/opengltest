#include "cVoxelMesh.h"

void cVoxelMesh::SetData(sColorVertex* VertexData, unsigned int VertexCount, unsigned int* IndexData, unsigned int IndexCount)
{

			free(mVertexData);
			mVertexCount = VertexCount;
			mVertexData = new sColorVertex[VertexCount];
			memcpy_s(mVertexData,VertexCount*sizeof(sColorVertex), VertexData,VertexCount*sizeof(sColorVertex));

			free(mIndexData);
			mIndexCount = IndexCount;
			mIndexData = new unsigned int[IndexCount];
			memcpy_s(mIndexData,IndexCount*sizeof(unsigned int), IndexData, IndexCount*sizeof(unsigned int));
			CreateVBOs();

};


sColorVertex* cVoxelMesh::GetVertexData()
{
	return mVertexData;
}

unsigned int* cVoxelMesh::GetIndexData()
{
	return mIndexData;
}


unsigned int cVoxelMesh::GetVertexCount()
{
	return mVertexCount;
}

unsigned int cVoxelMesh::GetIndexCount()
{
	return mIndexCount;
}

unsigned int cVoxelMesh::GetVBOIDVertex()
{
	return mVBOIDVertex;
}

unsigned int cVoxelMesh::GetVBOIDIndex()
{
	return mVBOIDIndex;
}

void cVoxelMesh::CreateVBOs()
{
	if(mVertexData && mIndexData && mVertexCount>0  && mIndexCount>0)
	{
		
		glGenBuffers(1, &mVBOIDVertex);
		glBindBuffer(GL_ARRAY_BUFFER, mVBOIDVertex);
		glBufferData(GL_ARRAY_BUFFER, mVertexCount*sizeof(sColorVertex), mVertexData, GL_STATIC_DRAW);
	
		glGenBuffers(1, &mVBOIDIndex);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVBOIDIndex);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndexCount*sizeof(unsigned int), mIndexData, GL_STATIC_DRAW);

		delete[] mVertexData;
		delete[] mIndexData;
	}
}


void cVoxelMesh::Draw()
{
	
	glBindBuffer(GL_ARRAY_BUFFER, mVBOIDVertex);        
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVBOIDIndex); 

	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	
	glVertexPointer(3, GL_FLOAT, sizeof(sColorVertex), 0);
	glNormalPointer(GL_FLOAT, sizeof(sColorVertex), (char*)NULL+12);
	glColorPointer(3, GL_FLOAT, sizeof(sColorVertex), (char*)NULL+24);
	
	glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_INT, 0);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}