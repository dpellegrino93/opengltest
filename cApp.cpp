#include "cApp.h"

cApp* cApp::pInstance = NULL;
cEngine* cApp::pEngine = NULL;

cApp* cApp::GetInstance()
{
	if(pInstance == NULL)
		pInstance = new cApp();
	return pInstance;
}

void cApp::Init(int argc, char **argv,
		    unsigned int displayMode,
		    int wWidth, int wHeight, 
		    int wPosX, int wPosY,
		    char* wName) 
	{
		pEngine->mHeight = wHeight;
		pEngine->mWidth = wWidth;
		glutInit(&argc,argv);
		glutInitDisplayMode(displayMode);
		glutInitWindowSize(wWidth,wHeight);
		glutInitWindowPosition(wPosX,wPosY);
		glutCreateWindow(wName);

		//Imposta funzioni callback grafiche
		glutDisplayFunc(Display);
		glutReshapeFunc(Resize);
		glutIdleFunc(Idle);

		//Imposta funzioni callback input
		glutKeyboardFunc(keyPressed);
		glutKeyboardUpFunc(keyUp);
		glutSpecialFunc(keySpecial);
		glutSpecialUpFunc(keySpecial);

		glewInit(); 

		cout<<"Versione OpenGL: "<<glGetString(GL_VERSION)<<endl;
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		
		glDepthFunc(GL_LEQUAL);
		//glEnable(GL_LIGHTING);
		//glEnable(GL_LIGHT0);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBlendFunc(GL_ONE,GL_ONE);

}


void cApp::MainLoop()
{
	pEngine->GameTimer.Inizio();
	glutMainLoop();
}

void cApp::MainLoopEvent()
{
	glutMainLoopEvent();
}



double Time = 0;
void cApp::Display()
{

	Time = pEngine->GameTimer.SecondiPassati();
	pEngine->GameTimer.Inizio();

	pEngine->Update(Time);
	pEngine->Draw();
	
}

void cApp::Resize(int Width, int Height)
{
	pEngine->Resize(Width,Height);
}

void cApp::Idle()
{
	glutPostRedisplay();
}


void cApp::keyPressed (unsigned char key, int x, int y) 
{
	if(glutGetModifiers())
		keyStates[key] = false;
	else
		keyStates[key] = true;
}


void cApp::keyUp (unsigned char key, int x, int y) 
{ 
	keyStates[key] = false;
}


void cApp::keySpecial(int key, int x, int y) 
{
	keyStates[key] = true;
}

void cApp::keySpecialUp (int key, int x, int y) 
{  
	keyStates[key] = false;
}
