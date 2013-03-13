#pragma once
#include "main.h"
#include "cEntity-cResource.h"
#include "cStaticMesh.h"
#include "cWorldStaticMesh.h"
#include "cMaterial.h"
#include "cTexture.h"
#include "cShader.h"
#include "cPosition.h"

class cWorldModel :
	public cPosition,
	public cEntity
{
public:
	cStaticMesh*		mVisibleMesh;
	cWorldStaticMesh*	mCollisionMesh;
	cWorldStaticMesh*	mRadiosityMesh;
	bool isVisible;

	cWorldModel()
	{
		isLocked = false;
		mEntityType = "WorldModel";
		mVisibleMesh = NULL;
		mCollisionMesh = NULL;
		mRadiosityMesh = NULL;
	};



	void			SetMesh(cStaticMesh* Mesh);
	cStaticMesh*	GetMesh();

	void	Update(double GameTime);
	void	Draw();

};