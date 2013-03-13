
#include "main.h"
#include "cEngine.h"
#include "cApp.h"

bool keyStates[256];


//int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
int main(int argc, char *argv[])
{
	cApp*    GL  = GL->GetInstance();
	cEngine* Eng = Eng->GetInstance();
	
	GL->Init(argc, argv,
			 GLUT_SINGLE || GLUT_RGBA ,
			 1400,800,
			 0,0,
			 "Caricamento");


	Eng->Setup();

	GL->MainLoop();

	return 0;
}
