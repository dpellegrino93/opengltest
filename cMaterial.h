#pragma once
#include "main.h"
#include "cTexture.h"
#include "cShader.h"
#include "cEntity-cResource.h"
class cMaterial:
	public cResource
{
protected:
	cTexture* mDiffuseTex;
	//Da implementare
	//---------------------
	cTexture* mNormalTex;
	cTexture* mSpecularTex;
	cTexture* mBumpTex;
	//----------------------

	float mDiffuseAmount;
	float mSpecularAmount;

public:
	cMaterial()
	{
		mResourceType = "Material";
		mDiffuseTex = 0;
		mNormalTex = 0;
		mSpecularTex = 0;
		mBumpTex = 0;
	}

	cTexture* GetDiffuse();
	void SetDiffuse(cTexture* DiffuseTex);

	cTexture* GetNormal();
	void SetNormal(cTexture* NormalTex);

	cTexture* GetSpecular();
	void SetSpecular(cTexture* SpecularTex);

	cTexture* GetBump();
	void SetBump(cTexture* BumpTex);

	void Bind();
	void Unbind();
};