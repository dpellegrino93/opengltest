#pragma once
#include "main.h"
#include "cEntity-cResource.h"
#include "cStaticMesh.h"
#include "cMaterial.h"
#include "cTexture.h"
#include "cShader.h"
#include "cPosition.h"

class cModel :
	public cPosition,
	public cEntity
{
public:
	cStaticMesh*	mMesh;
	cMaterial*		mMaterial;
	bool isVisible;
	cModel()
	{
		isLocked = false;
		mEntityType = "Model";
		mMesh = new cStaticMesh();
		mMaterial = 0;
	};


	void			SetMaterial(cMaterial* Material);
	cMaterial*		GetMaterial();

	void			SetMesh(cStaticMesh* Mesh);
	cStaticMesh*	GetMesh();

	void	Update(double GameTime);
	void	Draw();

};