#include "cModel.h"
void cModel::Update(double GameTime)
{

}

void cModel::Draw()
{
	if(isVisible && mMesh)
	{
		if(mMaterial)
			mMaterial->Bind();

		glPushMatrix();
		glMultMatrixf(ModelTrasform.M);	
		mMesh->Draw();
		glPopMatrix();
		mMaterial->Unbind();
	}

}

void cModel::SetMaterial(cMaterial* Material)
{
	mMaterial = Material;
}

cMaterial*	cModel::GetMaterial()
{
	return mMaterial;
}

void cModel::SetMesh(cStaticMesh* Mesh)
{
	mMesh = Mesh;
}

cStaticMesh*	cModel::GetMesh()
{
	return mMesh;
}