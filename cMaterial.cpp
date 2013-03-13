#include "cMaterial.h"

//####################################################################
//Diffuse
cTexture* cMaterial::GetDiffuse()
{
	return mDiffuseTex;
}

void cMaterial::SetDiffuse(cTexture* DiffuseTex)
{
	if(!mDiffuseTex) //Se punta a 0
	{
		mDiffuseTex = new cTexture();
		*mDiffuseTex = *DiffuseTex;
	}
	else
	{
		*mDiffuseTex = *DiffuseTex;
	}
}

//####################################################################
//Normal

cTexture* cMaterial::GetNormal()
{
	return mNormalTex;
}

void cMaterial::SetNormal(cTexture* NormalTex)
{
	if(!mNormalTex) //Se punta a 0
	{
		mNormalTex = new cTexture();
		*mNormalTex = *NormalTex;
	}
	else
	{
		*mNormalTex = *NormalTex;
	}
}

//####################################################################
//Specular

cTexture* cMaterial::GetSpecular()
{
	return mSpecularTex;
}

void cMaterial::SetSpecular(cTexture* SpecularTex)
{
	if(!mSpecularTex) //Se punta a 0
	{
		mSpecularTex = new cTexture();
		*mSpecularTex = *SpecularTex;
	}
	else
	{
		*mSpecularTex = *SpecularTex;
	}
}

//####################################################################
//Bump

cTexture* cMaterial::GetBump()
{
	return mBumpTex;
}

void cMaterial::SetBump(cTexture* BumpTex)
{
	if(!mBumpTex) //Se punta a 0
	{
		mBumpTex = new cTexture();
		*mBumpTex = *BumpTex;
	}
	else
	{
		*mBumpTex = *BumpTex;
	}
}

void cMaterial::Bind()
{
	glActiveTextureARB(GL_TEXTURE0_ARB);
	if(mDiffuseTex)	//Applica texture diffuse se è assegnata
			glBindTexture(GL_TEXTURE_2D, mDiffuseTex->GetID());
	else
			glBindTexture(GL_TEXTURE_2D,0);

	glActiveTextureARB(GL_TEXTURE1_ARB);
	if(mNormalTex)	//Applica texture normali se è assegnata
			glBindTexture(GL_TEXTURE_2D, mNormalTex->GetID());
	else
			glBindTexture(GL_TEXTURE_2D,0);

}

void cMaterial::Unbind()
{
	glActiveTextureARB(GL_TEXTURE2_ARB);
	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glBindTexture(GL_TEXTURE_2D, 0);

}