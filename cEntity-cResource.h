#pragma once
#include "main.h"



class cEntity
{
protected:
	//Il nome è conservato in cWorld
	std::string mEntityType;
public:
	cEntity()
	{
		mEntityType = "Entity";
	};
	virtual void Update(double GameTime){};
	virtual void Draw(){};
};


class cResource
{
protected:
	std::string mResourceType;
public:
	cResource()
	{
		mResourceType = "Resource";
	};
	
};
