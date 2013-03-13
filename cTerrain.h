
#pragma once
#include "main.h"
#include "sVertex-sTexCoord.h"
#include "cTexture.h"
#include "cEntity-cResource.h"


class cTerrain:
	public cEntity
{
protected:
	std::vector<sVertex>		mVertexDataVector;
	unsigned int				mVertexCount;
	std::vector<unsigned int>   mIndexDataVector;
	unsigned int				mIndexCount;

	GLuint						mVBOIDVertex;
	GLuint						mVBOIDIndex;

	float						mRadius;
	int							mResolution;
	cTexture*					mTexture;
	bool						Visible;

public:
	cTerrain()
	{
		mEntityType = "Terrain";
		mTexture = 0;
		Visible = false;
	};

	cTerrain(int resolution,  float radius )
	{
		mEntityType = "Terrain";
		mTexture = 0;
		mResolution = resolution;
		mRadius = radius;
		Visible = false;
	};

	int LoadHeightmapRAW16I(char* Filename);
	int LoadHeightmapRAW32F(char* Filename);
	void Smooth(float k);
	sVertex* GetVertexData();
	unsigned int* GetIndexData();
	unsigned int GetVertexCount();
	unsigned int GetIndexCount();

	GLuint GetVBOIDVertex();
	GLuint GetVBOIDIndex();

	bool isVisible();
	void setVisible(bool visible);

	void CreateVBOs();

	void			SetTexture(cTexture* Texture);
	cTexture*		GetTexture();

	virtual void	Draw();
};
