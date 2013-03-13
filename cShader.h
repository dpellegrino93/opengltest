#include "main.h"
#include "cEntity-cResource.h"
#ifndef CSHADER_H
#define CSHADER_H

using namespace std;

class cShader:
	public cResource
{
private:
	unsigned int mShaderID;
	unsigned int mShaderVP;
	unsigned int mShaderFP;

public:
	

	cShader()
	{
		mResourceType = "Shader";
	};

	cShader(const char* fileVP, const char* fileFP)
	{
		mResourceType = "Shader";
		Init(fileVP, fileFP);
	}

	~cShader()
	{
		glDetachShader(mShaderID, mShaderFP);
		glDetachShader(mShaderID, mShaderVP);
    
		glDeleteShader(mShaderFP);
		glDeleteShader(mShaderVP);
		glDeleteProgram(mShaderID);
	}


	void Init(const char* fileVP, const char* fileFP);
	void Bind();
	void Unbind();

	unsigned int GetID();
};


#endif