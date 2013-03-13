#ifndef CFBOTEXTURE_H
#define CFBOTEXTURE_H

#include "main.h"

class cGBuffer
{
private:
	GLuint			mFBO; 
	GLuint			mDiffuseRT; 
	unsigned int	mDiffuseTexture; 
	GLuint			mPositionRT; 
	unsigned int	mPositionTexture; 
	GLuint			mNormalsRT; 
	unsigned int	mNormalsTexture; 
	GLuint			mDepthBuffer; 



public:
	unsigned int	mWidth; 
	unsigned int	mHeight; 
	cGBuffer(int width, int height);
	~cGBuffer();

	void	Bind();
	void	Unbind();
	void	ShowTexture(unsigned int i, float fSizeX , float fSizeY , float x , float y );

	GLuint	GetDiffuseTexture() 
	{ 
		return mDiffuseTexture; 
	}

	GLuint	GetPositionTexture()  
	{ 
		return mPositionTexture; 
	}

	GLuint	GetNormalsTexture()  
	{ 
		return mNormalsTexture; 
	}



};



#endif