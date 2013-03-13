#include "main.h"
#include "sVertex-sTexCoord.h"
#include "cEntity-cResource.h"
#ifndef CTEXTURE_H
#define CTEXTURE_H

#define LINE 256


class cTexture:
	public cResource
{
protected:
	unsigned int mTextureID;
	unsigned int Width, Height;
public:

	cTexture()
	{
		mResourceType = "Texture";
	}

	void CreateFromPPM(char* Filename);
	unsigned int GetID();


};


#endif