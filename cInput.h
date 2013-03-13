#pragma once
#include "main.h"

class cInput
{
protected:
	bool Keys[256];
public:
	cInput()
	{

	};

	bool GetKey(char key); //

};