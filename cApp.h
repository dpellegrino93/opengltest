#ifndef cApp_H
#define cApp_H

#include "main.h"

#include "sVertex-sTexCoord.h"
#include "cEngine.h"


extern bool keyStates[256];



class cApp
{
private:
	static cApp*			pInstance;
	static cEngine*			pEngine;


	cApp()
	{
		pEngine = pEngine->GetInstance();
		
	};
public:
	static cApp* GetInstance();
	static void Display();
	static void Resize(int Width, int Height);
	static void Idle();
	static void keyPressed(unsigned char key, int x, int y);
	static void keyUp(unsigned char key, int x, int y);
	static void keySpecial(int key, int x, int y);
	static void keySpecialUp(int key, int x, int y);


	void MainLoop();
	void MainLoopEvent();

	int argc; char **argv;
	unsigned int displayMode;	
	int wWidth, wHeight;
	int wPosX, wPosY;
	char* wName;

	void Init(int argc, char **argv,
		    unsigned int displayMode,
		    int wWidth, int wHeight, 
		    int wPosX, int wPosY,
		    char* wName);
};

#endif