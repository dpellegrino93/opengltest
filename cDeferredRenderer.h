#ifndef CDEFERRED_H
#define CDEFERRED_H

#include "main.h"
#include "cGBuffer.h"
#include "cShader.h"
#include "cLight.h"

class cDeferredRenderer
{
private:
	
	
	cGBuffer*	mFBORenderTexture;

	GLuint				mDiffuseID; 
	GLuint				mPositionID; 
	GLuint				mNormalsID; 


	GLuint				mLightPositionID;
	GLuint				mLightColorID;
	GLuint				mLightAttID;

public:
	unsigned int mWidth, mHeight;
	cShader*	 mShader;

	cDeferredRenderer()
	{
		mFBORenderTexture = 0;
		mShader = 0;
	}

	cDeferredRenderer(unsigned int width, unsigned int height, cGBuffer* rendertexture);
	void Render();
	void Begin();
	void DrawPointLight(cLight* Light);
	void End();
};


#endif