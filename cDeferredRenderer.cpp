#include "cDeferredRenderer.h"

cDeferredRenderer::cDeferredRenderer(unsigned int width, unsigned int height, cGBuffer* RenderTexture)
{
	mShader = new cShader("deferredRendering.vert","deferredRendering.frag");
	mWidth = width;
	mHeight = height;
	mFBORenderTexture = RenderTexture;
	//Carica id variabili da shader
	mDiffuseID = glGetUniformLocationARB(mShader->GetID(),"tDiffuse");
	mPositionID = glGetUniformLocationARB(mShader->GetID(),"tPosition");
	mNormalsID = glGetUniformLocationARB(mShader->GetID(),"tNormals");

	mLightPositionID = glGetUniformLocationARB(mShader->GetID(),"lightPosition");
	mLightColorID = glGetUniformLocationARB(mShader->GetID(),"lightColor");
	mLightAttID = glGetUniformLocationARB(mShader->GetID(),"lightAtt");
}


void cDeferredRenderer::Begin()
{
	//LightPass.Begin()
	glEnable(GL_BLEND);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0,mWidth,0,mHeight,0.1f,2);	

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	
	glUseProgramObjectARB(mShader->GetID());

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glBindTexture(GL_TEXTURE_2D, mFBORenderTexture->GetDiffuseTexture());
	glUniform1iARB ( mDiffuseID, 0 );
	
	glActiveTextureARB(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D, mFBORenderTexture->GetPositionTexture());
	glUniform1iARB ( mPositionID, 1 );
	
	glActiveTextureARB(GL_TEXTURE2_ARB);
	glBindTexture(GL_TEXTURE_2D, mFBORenderTexture->GetNormalsTexture());
	glUniform1iARB ( mNormalsID, 2 );


	glLoadIdentity();
	glTranslatef(0,0,-1);


}

void cDeferredRenderer::DrawPointLight(cLight* Light)
{
	GLfloat Pos[3];
	Pos[0] = Light->GetPosition().X;
	Pos[1] = Light->GetPosition().Y;
	Pos[2] = Light->GetPosition().Z;
	glUniform3fv(mLightPositionID, 1, Pos);

	GLfloat Col[3];
	Col[0] = Light->GetColor().X;
	Col[1] = Light->GetColor().Y;
	Col[2] = Light->GetColor().Z;
	glUniform3fv(mLightColorID, 1, Col);

	GLfloat Att[3];
	Att[0] = Light->GetFalloff().X;
	Att[1] = Light->GetFalloff().Y;
	Att[2] = Light->GetFalloff().Z;
	glUniform3fv(mLightAttID, 1, Att);

	glBegin(GL_QUADS);
	glTexCoord2f( 0, 0 );
	glVertex3f(    0.0f, 0.0f, 0.0f);
	glTexCoord2f( 1, 0 );
	glVertex3f(   (float) mWidth, 0.0f, 0.0f);
	glTexCoord2f( 1, 1 );
	glVertex3f(   (float) mWidth, (float) mHeight, 0.0f);
	glTexCoord2f( 0, 1 );
	glVertex3f(    0.0f,  (float) mHeight, 0.0f);
	glEnd();
}

void cDeferredRenderer::End()
{
	
	glActiveTextureARB(GL_TEXTURE3_ARB);
	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTextureARB(GL_TEXTURE2_ARB);
	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D, 0);

	glUseProgramObjectARB(0);
	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}