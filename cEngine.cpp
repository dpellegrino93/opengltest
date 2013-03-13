#include "cEngine.h"


cEngine* cEngine::pInstance = NULL;

cEngine* cEngine::GetInstance()
{
	if(pInstance == NULL)
		pInstance = new cEngine();
	return pInstance;
}


void cEngine::Setup()
{

	cModel*				Garrus = new cModel();
	cTexture*			GarrusTex = new cTexture();
	cTexture*			GarrusTexN = new cTexture();
	cMaterial*			GarrusMat = new cMaterial();

	cTerrain*			Terreno = new cTerrain(1024, 512);
	cTexture*			TerrenoTex  = new cTexture();
	cCamera*			Cam = new cCamera();
	GameTimer.Inizio();
	srand(GameTimer.t1.LowPart);
	cVoxel tvox;
	cVoxelSlice fette[CHUNK_HEIGHT];
	
	/*for(int y=0 ; y<CHUNK_HEIGHT ; y++)			//Y = altezza
	{
		for(int x=0 ; x<CHUNK_SIZE ; x++)		//X = Larghezza
		{
			for(int z=0 ; z<CHUNK_SIZE ; z++)	//Z = Profondit�
			{
				tvox.setColorS(x,y,z,0);
				TestChunk.setVoxel(x,y,z,tvox);
			}
		}
	}*/
	
	/*
	for(int x=0 ; x<CHUNK_SIZE ; x++)		//X = Larghezza
		{
			for(int z=0 ; z<CHUNK_SIZE ; z++)	//Z = Profondit�
			{
				double tx = (double)(CHUNK_SIZE/2-x)/20;
				double tz = (double)(CHUNK_SIZE/2-z)/20;
				double ty = sin(tx)*sin(tz);
				int y = ty*(CHUNK_HEIGHT/2-1)+CHUNK_HEIGHT/2;
				if(y>=CHUNK_HEIGHT)
					y=CHUNK_HEIGHT-1;
				else if(y<0)
					y=0;
				for(int fy=0;fy<y;fy++)
				{
					tvox.setColorF(tx,ty,tz,1);
					TestChunk.setVoxel(x,fy,z,tvox);
				}
			}
		}
	*/
	//TestChunk.Update();
	cout<<"Tempo per costruire voxel: "<<GameTimer.SecondiPassati()<<endl;
	Facce = 0;
	//########################################################
	//Terreno
	
	Facce += Terreno->LoadHeightmapRAW16I("heigthmap.raw");
	//32 bit float
	//Facce += Terreno->LoadHeightmapRAW32F("heigthmap.r32");
	Terreno->Smooth(0.4f);
	Terreno->CreateVBOs();

	TerrenoTex->CreateFromPPM("texturefinal.ppm");
	Terreno->SetTexture(TerrenoTex);
	
	//########################################################
	//Garrus
	
	OBJModel* modello;
	modello = new OBJModel();

	modello->LoadOBJ("garrus.obj");
	
	Facce+= modello->SetToMesh(Garrus->mMesh);

	GarrusTex->CreateFromPPM("garrus.ppm");
	//GarrusTexN->CreateFromPPM("garrusnorm.ppm");

	GarrusMat->SetDiffuse(GarrusTex);
	//GarrusMat->SetNormal(GarrusTexN);

	Garrus->SetMaterial(GarrusMat);

	Garrus->SetPosition(0,55,0);
		
	//########################################################
	//Camera
	Cam->mSpeed = 30;
	Cam->vFOV = 60;
	Cam->SetPosition(0,100,200);
	Cam->SetRotationEuler(0,0,0);

	ActiveCamera = Cam;

	//########################################################
	//Deferred rendering
	
	int intens = 15;
	Luce.SetColor(intens*1,intens*1,intens*1);
	Luce.SetPosition(-30,-30,-10);
	Luce.SetFalloff(0,8,4);

	Luce1.SetColor(intens*1,intens*1,intens*1);
	Luce1.SetPosition(30,-30,-10);
	Luce1.SetFalloff(0,8,4);

	Luce2.SetColor(intens*1,intens*1,intens*1);
	Luce2.SetPosition(-30,30,-10);
	Luce2.SetFalloff(0,8,4);

	Luce3.SetColor(intens*1,intens*1,intens*1);
	Luce3.SetPosition(30,30,-10);
	Luce3.SetFalloff(0,8,4);

	GBuffer = new cGBuffer(mWidth, mHeight);
	LightPass = new cDeferredRenderer(mWidth, mHeight, GBuffer);
	GeometryPassShader = new cShader("deferredShading.vert","deferredShading.frag");

	cout<<GameTimer.SecondiPassati();
	

	GameWorld->AddEntity(Garrus, "Garrus");
	GameWorld->AddEntity(Terreno, "Terreno");
	GameWorld->AddEntity(Cam, "Camera1");

	GameWorld->AddResource(GarrusTex, "Garrus Texture");
	//GameWorld->AddResource(GarrusTexN, "Garrus Texture Normal");
	GameWorld->AddResource(GarrusMat, "Garrus Material");
	GameWorld->AddResource(TerrenoTex, "Texture Terreno");


};

void cEngine::Resize(int Width, int Height)
{
	if(Width <= 0) Width = 1;
	if(Height <= 0) Height = 1;

	mWidth = Width;
	mHeight = Height;
	glViewport(0, 0, (GLsizei)Width, (GLsizei)Height);
	glMatrixMode(GL_PROJECTION);

	GBuffer->~cGBuffer();
	free(GBuffer);
	GBuffer = new cGBuffer(mWidth, mHeight);
	LightPass->mHeight = Height;
	LightPass->mWidth = Width;

	glLoadIdentity();
	gluPerspective(ActiveCamera->vFOV, (GLfloat)Width / (GLfloat)Height, 0.1, 100000.0);
	glMatrixMode(GL_MODELVIEW);

}

char stringa[100];

double B = 0;
double l[4] = {0,0,0,0};
double cT = 0;
int cF =0;


int ind = 0;
bool b = false;
long long int colcount = 0;
void cEngine::Update(double Time)
{
	GameTime = Time;

	cT+=GameTime;
	cF++;
	B+=GameTime;

	if(cT>0.25 )
	{
		sprintf_s(stringa,100,"Tempo Frame:  %.2f ms \t\t FPS: %.0f",(cT/(float)cF)*1000,1/(cT/(float)cF));
		cT = 0;
		cF = 0;
		glutSetWindowTitle(stringa);
	}

	if(keyStates['q']) b = true;
	
	if (b && keyStates['q'] == false)
	{
		b= false;
		ind++;
	}

	if(keyStates['f'])
	{
		l[0]+=GameTime*2;
		Luce.SetColor(15*1.0f*sin(l[0])+1+0.1, 15*0.9f*sin(l[0]+l[0]/3)+1+0.1, 15*0.9f*sin(l[0]+(l[0]/3)*2)+1+0.1);
	}

	if(keyStates['g'])
	{
		l[1]+=GameTime*2;
		Luce1.SetColor(3*1.0f*sin(l[1])+1, 3*0.9f*sin(l[1]+l[1]/3)+1, 15*0.9f*sin(l[1]+(l[1]/3)*2)+1);
	}

	if(keyStates['r'])
	{
		l[2]+=GameTime*2;
		Luce2.SetColor(15*1.0f*sin(l[2])+1, 15*0.9f*sin(l[2]+l[2]/3)+1, 15*0.9f*sin(l[2]+(l[2]/3)*2)+1);
	}

	if(keyStates['t'])
	{
		l[3]+=GameTime*2;
		Luce3.SetColor(15*1.0f*sin(l[3])+1, 15*0.9f*sin(l[3]+l[3]/3)+1, 15*0.9f*sin(l[3]+(l[3]/3)*2)+1);
	}
	
	
	GameWorld->Update(Time);
	static float cvox = 0, cvoxdir = 1;

	//cVoxel tvox;
	

	//if(cvox<=-1) cvoxdir = 1;
	//else if(cvox>=1) cvoxdir = -1;

	cvox-=Time*3;
	//bounce = sin(cvox);
	//TestChunk.Update();
}

void cEngine::Draw()
{

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	if(ActiveCamera)
	{
		//SetCameraProj();
		NoclipCamera();
		UpdateCamera();
	}

	GBuffer->Bind();
	GeometryPassShader->Bind();

		GameWorld->Draw();
		//TestChunk.Draw();
	GeometryPassShader->Unbind();
	GBuffer->Unbind();
	
	LightPass->Begin();

		LightPass->DrawPointLight(&Luce);
		LightPass->DrawPointLight(&Luce1);
		LightPass->DrawPointLight(&Luce2);
		LightPass->DrawPointLight(&Luce3);
		
	LightPass->End();
	

	
	if(ind >= 4 || ind < 0) ind = 0;
	GBuffer->ShowTexture(ind, mWidth, mHeight,0,0);
	
	
	glFlush();
	//glutSwapBuffers();
}




void cEngine::SetCameraProj()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(ActiveCamera->vFOV, (GLfloat)mWidth / (GLfloat)mHeight, 1, 100000.0);
	glMatrixMode(GL_MODELVIEW);
}

void cEngine::UpdateCamera()
{
	glMultMatrixf(ActiveCamera->GetMatrixInverse());	
}

void cEngine::NoclipCamera()
{
	ActiveCamera->RotateEuler( (keyStates['k']-keyStates['i'])*GameTime*100,
								0,
								(keyStates['j']-keyStates['l'])*GameTime*100);

	cVec3 Mov =   cVec3( (float)(keyStates['d']-keyStates['a']),
						 (float)(keyStates[' ']-keyStates['c']),
						 (float)(keyStates['s']-keyStates['w'])  ) ;

	ActiveCamera->Traslate( ActiveCamera->Rotation * Mov * (float)ActiveCamera->mSpeed*(float)GameTime);
	

}
