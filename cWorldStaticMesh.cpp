#include "cWorldStaticMesh.h"

void cWorldStaticMesh::SetData(sVertex* VertexData, unsigned int VertexCount, unsigned int* IndexData, unsigned int IndexCount)
{
		if(VertexData != NULL && IndexData != NULL)
		{
			mVertexCount = VertexCount;
			mVertexData = new sVertex[VertexCount];
			memcpy_s(mVertexData,VertexCount*sizeof(sVertex), VertexData,VertexCount*sizeof(sVertex));
	
			mIndexCount = IndexCount;
			mIndexData = new unsigned int[IndexCount];
			memcpy_s(mIndexData,IndexCount*sizeof(unsigned int), IndexData, IndexCount*sizeof(unsigned int));
			this->CreateVBOs();
		}

};


sVertex* cWorldStaticMesh::GetVertexData()
{
	return mVertexData;
}

unsigned int* cWorldStaticMesh::GetIndexData()
{
	return mIndexData;
}


unsigned int cWorldStaticMesh::GetVertexCount()
{
	return mVertexCount;
}

unsigned int cWorldStaticMesh::GetIndexCount()
{
	return mIndexCount;
}

unsigned int cWorldStaticMesh::GetVBOIDVertex()
{
	return mVBOIDVertex;
}

unsigned int cWorldStaticMesh::GetVBOIDIndex()
{
	return mVBOIDIndex;
}

void cWorldStaticMesh::CreateVBOs()
{
	if(mVertexData && mIndexData && mVertexCount>0  && mIndexCount>0)
	{
		

		glGenBuffers(1, &mVBOIDVertex);
		glBindBuffer(GL_ARRAY_BUFFER, mVBOIDVertex);
		glBufferData(GL_ARRAY_BUFFER, mVertexCount*sizeof(sVertex), mVertexData, GL_STATIC_DRAW);
	
		glGenBuffers(1, &mVBOIDIndex);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVBOIDIndex);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndexCount*sizeof(unsigned int), mIndexData, GL_STATIC_DRAW);
		//NON ELIMINA VERTICI DALLA RAM
	}
}


void cWorldStaticMesh::Draw()
{
	
	glBindBuffer(GL_ARRAY_BUFFER, mVBOIDVertex);        
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVBOIDIndex); 

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	
	glVertexPointer(3, GL_FLOAT, sizeof(sVertex), 0);
	glNormalPointer(GL_FLOAT, sizeof(sVertex), (char*)NULL+12);
	glTexCoordPointer(2, GL_FLOAT, sizeof(sVertex), (char*)NULL+24);
	
	glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_INT, 0);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


}