#include "cTerrain.h"
#define LINE 256


//carica RAW 16 bit INT grayscale formato ibm pc
int cTerrain::LoadHeightmapRAW16I(char* Filename)
{

	unsigned short* RAWData;
	int Count;
    printf("- Caricamento file heightmap INT16 '%s' ...\n", Filename); 
	FILE *file = fopen(Filename, "rb");
	if (file==NULL)
	{
		printf("\t*File '%s' non trovato.\n", Filename);
		Visible = false;
		return 0;
	}
    RAWData = (unsigned short*)malloc(sizeof(unsigned short) * mResolution*mResolution);
    Count = fread(RAWData, sizeof(unsigned short), mResolution*mResolution, file);
    fclose(file);
	
	//Calcolo vertici
	printf("\t*Calcolo vertici...\n");
	for( int y = 0 ; y < mResolution ; y++ )
		for( int x = 0 ; x < mResolution ; x++ )
		{
			cVec3 Position = cVec3( (2*mRadius/(float)mResolution)*x-(float)mRadius, ((float)RAWData[mResolution*y+x]/65536)*mRadius/1.4, (2*mRadius/(float)mResolution)*y-(float)mRadius/2 );
			sTexCoord UV = sTexCoord( (float)x/(float)mResolution , (float)y/(float)mResolution );
			mVertexDataVector.push_back( sVertex( Position, cVec3(0,1,0), UV ) );
		}

	//Calcolo indici
	int indice = 0;
	printf("\t*Calcolo indici...\n");
	for( int y=0 ; y<mResolution-1 ; y++)
		for( int x=0 ; x<mResolution-1 ; x++)
		{
			mIndexDataVector.push_back ( (unsigned int)mResolution*y+x );
			mIndexDataVector.push_back ( (unsigned int)mResolution*y+x + mResolution );
			mIndexDataVector.push_back ( (unsigned int)mResolution*y+x + mResolution +1 );
			
			mIndexDataVector.push_back ( (unsigned int)mResolution*y+x + mResolution + 1 );
			mIndexDataVector.push_back ( (unsigned int)mResolution*y+x + 1 );
			mIndexDataVector.push_back ( (unsigned int)mResolution*y+x );
		}

	//Calcolo normali
	printf("\t*Calcolo normali...\n");
	std::vector<cVec3>* mNormalDataVector = new std::vector<cVec3>[mResolution*mResolution];
	int nIndici = mIndexDataVector.size();
	for( int i = 0; i < nIndici; i += 3 )
	{
	  cVec3 p1 = mVertexDataVector[mIndexDataVector[i+0]].Pos;
	  cVec3 p2 = mVertexDataVector[mIndexDataVector[i+1]].Pos;
	  cVec3 p3 = mVertexDataVector[mIndexDataVector[i+2]].Pos;

	  cVec3 v1 = p2 - p1;
	  cVec3 v2 = p3 - p1;
	  cVec3 normal = v1.Cross(v2);

	  normal.Normalize();
	  mNormalDataVector[mIndexDataVector[i+0]].push_back( normal );
	  mNormalDataVector[mIndexDataVector[i+1]].push_back( normal );
	  mNormalDataVector[mIndexDataVector[i+2]].push_back( normal );
	}

	for( int i = 0; i < mResolution*mResolution; ++i )
	{
		mVertexDataVector[i].Nor = cVec3(0,0,0);
		#pragma omp parallel for
		for( int j = 0; j < mNormalDataVector[i].size(); ++j )
			mVertexDataVector[i].Nor = mVertexDataVector[i].Nor + mNormalDataVector[i][j];
  
		mVertexDataVector[i].Nor.Normalize();
	}

	//#################
	mVertexCount = mVertexDataVector.size();
	mIndexCount = mIndexDataVector.size();
	printf("\t*Vertici :\t%d\n", mVertexCount);
	printf("\t*Indici :\t%d\n", mIndexCount);
	printf("\t*Facce :\t%d\n", mIndexCount/3);
	Visible = true;
	free(RAWData);
	return mIndexCount/3;
}

//carica RAW 32 bit float grayscale
int cTerrain::LoadHeightmapRAW32F(char* Filename)
{

	float* RAWData;
	int Count;
    printf("- Caricamento file heightmap 32F '%s' ...\n", Filename); 
	FILE *file = fopen(Filename, "rb");
	if (file==NULL)
	{
		printf("\t*File '%s' non trovato.\n", Filename);
		Visible = false;
		return 0;
	}
    RAWData = (float*)malloc(sizeof(float) * mResolution*mResolution);
    Count = fread(RAWData, sizeof(float), mResolution*mResolution, file);
    fclose(file);

	//Calcolo vertici
	for( int y = 0 ; y < mResolution ; y++ )
		for( int x = 0 ; x < mResolution ; x++ )
		{
			cVec3 Position = cVec3( (2*mRadius/(float)mResolution)*x-(float)mRadius, ((float)RAWData[mResolution*y+x]/65536)*mRadius/1.4, (2*mRadius/(float)mResolution)*y-(float)mRadius/2 );
			sTexCoord UV = sTexCoord( (float)x/(float)mResolution , (float)y/(float)mResolution );
			mVertexDataVector.push_back( sVertex( Position, cVec3(0,1,0), UV ) );
		}

	//Calcolo indici
	int indice = 0;
	for( int y=0 ; y<mResolution-1 ; y++)
		for( int x=0 ; x<mResolution-1 ; x++)
		{
			mIndexDataVector.push_back ( (unsigned int)mResolution*y+x );
			mIndexDataVector.push_back ( (unsigned int)mResolution*y+x + mResolution );
			mIndexDataVector.push_back ( (unsigned int)mResolution*y+x + mResolution +1 );
			
			mIndexDataVector.push_back ( (unsigned int)mResolution*y+x + mResolution + 1 );
			mIndexDataVector.push_back ( (unsigned int)mResolution*y+x + 1 );
			mIndexDataVector.push_back ( (unsigned int)mResolution*y+x );
		}

	//Calcolo normali
	std::vector<cVec3>* mNormalDataVector = new std::vector<cVec3>[mResolution*mResolution];

	int nIndici = mIndexDataVector.size();
	for( int i = 0; i < nIndici; i += 3 )
	{
	  cVec3 p1 = mVertexDataVector[mIndexDataVector[i+0]].Pos;
	  cVec3 p2 = mVertexDataVector[mIndexDataVector[i+1]].Pos;
	  cVec3 p3 = mVertexDataVector[mIndexDataVector[i+2]].Pos;

	  cVec3 v1 = p2 - p1;
	  cVec3 v2 = p3 - p1;
	  cVec3 normal = v1.Cross(v2);

	  normal.Normalize();
	  mNormalDataVector[mIndexDataVector[i+0]].push_back( normal );
	  mNormalDataVector[mIndexDataVector[i+1]].push_back( normal );
	  mNormalDataVector[mIndexDataVector[i+2]].push_back( normal );
	}

	for( int i = 0; i < mResolution*mResolution; ++i )
	{
		mVertexDataVector[i].Nor = cVec3(0,0,0);

		for( int j = 0; j < mNormalDataVector[i].size(); ++j )
			mVertexDataVector[i].Nor = mVertexDataVector[i].Nor + mNormalDataVector[i][j];
  
		mVertexDataVector[i].Nor.Normalize();
	}

	//#################
	mVertexCount = mVertexDataVector.size();
	mIndexCount = mIndexDataVector.size();

	printf("\t*Vertici :\t%d\n", mVertexCount);
	printf("\t*Indici :\t%d\n", mIndexCount);
	printf("\t*Facce :\t%d\n", mIndexCount/3);
	Visible = true;
	free(RAWData);
	return mIndexCount/3;
}


void cTerrain::Smooth(float k)
{
	int x,z;
	if(mVertexDataVector.size() == 0) return;
		for(x = 1; x < mResolution; x++)
			#pragma omp parallel for
			for (z = 0;z < mResolution; z++)
			{
				mVertexDataVector[x*mResolution+z].Pos = mVertexDataVector[(x-1)*mResolution+z].Pos * (1-k) + 
						mVertexDataVector[x*mResolution+z].Pos * k;
				mVertexDataVector[x*mResolution+z].Nor = mVertexDataVector[(x-1)*mResolution+z].Nor * (1-k) + 
						mVertexDataVector[x*mResolution+z].Nor * k;
			}

		for(x = mResolution-2; x < -1; x--)
			#pragma omp parallel for
			for (z = 0;z < mResolution; z++)
			{
				mVertexDataVector[x*mResolution+z].Pos = mVertexDataVector[(x+1)*mResolution+z].Pos * (1-k) + 
						mVertexDataVector[x*mResolution+z].Pos * k;
				mVertexDataVector[x*mResolution+z].Nor = mVertexDataVector[(x+1)*mResolution+z].Nor * (1-k) + 
						mVertexDataVector[x*mResolution+z].Nor * k;
			}

		for(x = 0; x < mResolution; x++)
			#pragma omp parallel for
			for (z = 1;z < mResolution; z++)
			{
				mVertexDataVector[x*mResolution+z].Pos = mVertexDataVector[x*mResolution+z-1].Pos * (1-k) + 
						mVertexDataVector[x*mResolution+z].Pos * k;
				mVertexDataVector[x*mResolution+z].Nor = mVertexDataVector[x*mResolution+z-1].Nor * (1-k) + 
						mVertexDataVector[x*mResolution+z].Nor * k;
			}

		for(x = 0; x < mResolution; x++)
			#pragma omp parallel for
			for (z = mResolution; z < -1; z--)
			{
				mVertexDataVector[x*mResolution+z].Pos = mVertexDataVector[x*mResolution+z+1].Pos * (1-k) + 
						mVertexDataVector[x*mResolution+z].Pos * k;
				mVertexDataVector[x*mResolution+z].Nor = mVertexDataVector[x*mResolution+z+1].Nor * (1-k) + 
						mVertexDataVector[x*mResolution+z].Nor * k;
			}


}

sVertex* cTerrain::GetVertexData()
{
	return mVertexDataVector.data();
}

unsigned int* cTerrain::GetIndexData()
{
	return mIndexDataVector.data();
}


unsigned int cTerrain::GetVertexCount()
{
	return mVertexDataVector.size();
}

unsigned int cTerrain::GetIndexCount()
{
	return mIndexDataVector.size();
}

unsigned int cTerrain::GetVBOIDVertex()
{
	return mVBOIDVertex;
}

unsigned int cTerrain::GetVBOIDIndex()
{
	return mVBOIDIndex;
}

void cTerrain::CreateVBOs()
{
	if(Visible)
	{
		glGenBuffers(1, &mVBOIDVertex);
		glBindBuffer(GL_ARRAY_BUFFER, mVBOIDVertex);
		glBufferData(GL_ARRAY_BUFFER, mVertexDataVector.size()*sizeof(sVertex), mVertexDataVector.data(), GL_STATIC_DRAW);
	
		glGenBuffers(1, &mVBOIDIndex);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVBOIDIndex);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndexDataVector.size()*sizeof(unsigned int), mIndexDataVector.data(), GL_STATIC_DRAW);
		// Per adesso il terreno è statico e può essere eliminato
		// In futuro è da basare su vertex shader (con tessellation) e heightmap caricate su glsl 
		free(mIndexDataVector.data());
		free(mVertexDataVector.data());
	}
}

void cTerrain::Draw()
{
	if(Visible)
	{
		glPushMatrix();
		glBindBuffer(GL_ARRAY_BUFFER, mVBOIDVertex);        
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVBOIDIndex); 

		if(mTexture!=NULL)	//Applica texture se è assegnata
			glBindTexture(GL_TEXTURE_2D, mTexture->GetID());
		else
			glBindTexture(GL_TEXTURE_2D,0);

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
		glPopMatrix();
	}

}

void cTerrain::SetTexture(cTexture* Texture)
{
	mTexture = Texture;
}

cTexture*	cTerrain::GetTexture()
{
	return mTexture;
}

bool cTerrain::isVisible()
{
	return Visible;
}

void cTerrain::setVisible(bool visible)
{
	Visible = visible;
}