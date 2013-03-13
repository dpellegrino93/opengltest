#include "cGBuffer.h"

cGBuffer::cGBuffer(int Width, int Height)
{	
	mWidth  = Width;
	mHeight = Height;

	glGenFramebuffersEXT(1, &mFBO);
	glGenRenderbuffersEXT(1, &mDiffuseRT);
	glGenRenderbuffersEXT(1, &mPositionRT);
	glGenRenderbuffersEXT(1, &mNormalsRT);
	glGenRenderbuffersEXT(1, &mDepthBuffer);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, mFBO);

	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, mDiffuseRT);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_RGBA, mWidth, mHeight);
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_RENDERBUFFER_EXT, mDiffuseRT);

	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, mPositionRT);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_RGBA16F, mWidth, mHeight);
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT1_EXT, GL_RENDERBUFFER_EXT, mPositionRT);

	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, mNormalsRT);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_RGBA16F, mWidth, mHeight);
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT2_EXT, GL_RENDERBUFFER_EXT, mNormalsRT);

	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, mDepthBuffer);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, mWidth, mHeight);
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, mDepthBuffer);

	glGenTextures(1, &mDiffuseTexture);
	glBindTexture(GL_TEXTURE_2D, mDiffuseTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, mDiffuseTexture, 0);

	glGenTextures(1, &mPositionTexture);
	glBindTexture(GL_TEXTURE_2D, mPositionTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, mWidth, mHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT1_EXT, GL_TEXTURE_2D, mPositionTexture, 0);

	glGenTextures(1, &mNormalsTexture);
	glBindTexture(GL_TEXTURE_2D, mNormalsTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, mWidth, mHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT2_EXT, GL_TEXTURE_2D, mNormalsTexture, 0);

	GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);

	if( status != GL_FRAMEBUFFER_COMPLETE_EXT)
	{
		std::cout<<"\n### Errore "<<status<<" nella creazione del GBuffer ###\n\n";
		return;
	}

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

cGBuffer::~cGBuffer()
{
	glDeleteTextures(1, &mNormalsTexture);
	glDeleteTextures(1, &mPositionTexture);
	glDeleteTextures(1, &mDiffuseTexture);
	glDeleteFramebuffersEXT(1, &mFBO);
	glDeleteRenderbuffersEXT(1, &mDiffuseRT);
	glDeleteRenderbuffersEXT(1, &mPositionRT);
	glDeleteRenderbuffersEXT(1, &mNormalsRT);
	glDeleteRenderbuffersEXT(1, &mDepthBuffer);
}


void cGBuffer::Bind()
{
	glDisable(GL_BLEND);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, mFBO);
	glPushAttrib(GL_VIEWPORT_BIT);
	glViewport(0,0,mWidth, mHeight);

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glActiveTextureARB(GL_TEXTURE0_ARB);

	GLenum buffers[] = { GL_COLOR_ATTACHMENT0_EXT, 
						 GL_COLOR_ATTACHMENT1_EXT, 
						 GL_COLOR_ATTACHMENT2_EXT };
	glDrawBuffers(3, buffers);
}

void cGBuffer::Unbind()
{	
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glPopAttrib();
}

void cGBuffer::ShowTexture(unsigned int i, float SizeX, float SizeY, float x, float y) 
{
	GLuint texture = mDiffuseTexture;
	if(i == 1) 
		texture = mPositionTexture;
	else if(i == 2) 
		texture = mNormalsTexture;
	else if (i == 3)
		return;

	glDisable(GL_BLEND);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0,mWidth,0,mHeight,0.1f,2);	

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glLoadIdentity();
	glTranslatef(x,-y,-1.0);

	glBegin(GL_QUADS);
	glTexCoord2f( 0, 1 );
	glVertex3f(    0.0f,  (float) mHeight, 0.0f);
	glTexCoord2f( 0, 0 );
	glVertex3f(    0.0f,   mHeight-SizeY, 0.0f);
	glTexCoord2f( 1, 0 );
	glVertex3f(   SizeX,  mHeight-SizeY, 0.0f);
	glTexCoord2f( 1, 1 );
	glVertex3f(   SizeX, (float) mHeight, 0.0f);
	glEnd();
	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}