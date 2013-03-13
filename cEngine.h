#ifndef CENGINE_H
#define CENGINE_H
#include "main.h"
#include "cVec3.h"
#include "cTimer.h"
#include "cWorld.h"
#include "cShader.h"
#include "OBJ.h"
#include "sVertex-sTexCoord.h"
#include "cModel.h"
#include "cGBuffer.h"
#include "cDeferredRenderer.h"
#include "cTerrain.h"
#include "cCamera.h"
#include "cVoxel.h"
extern bool keyStates[256];


class cEngine
{
private:
	cEngine()
	{
		GameWorld = new cWorld();
	};
	static cEngine* pInstance;
public:
	cTimer				GameTimer;
	double				GameTime;
	cWorld*				GameWorld;
	cCamera*			ActiveCamera;

	cLight				Luce;
	cLight				Luce1;
	cLight				Luce2;
	cLight				Luce3;

	//#######################################à
	//Deferred rendering
	cGBuffer*			GBuffer;
	cDeferredRenderer*	LightPass;
	cShader*			GeometryPassShader;
	cShader*			DefRendShader;
	cVoxelChunk			TestChunk;
	int Facce;
	int mWidth, mHeight;

public:

	static cEngine* GetInstance();

	~cEngine()
	{

		if(GameWorld)
			free(GameWorld);
		if(ActiveCamera)
			free(ActiveCamera);
		if(GBuffer)
			free(GBuffer);
		if(LightPass)
			free(LightPass);
		if(GeometryPassShader)
			free(GeometryPassShader);
		if(DefRendShader)
			free(DefRendShader);


	}

	void Setup();

	void Resize(int Width, int Height);

	void Update(double GameTime); //SECONDI
	void Draw();

	void SetCameraProj();
	void UpdateCamera();
	void NoclipCamera();

};


#endif