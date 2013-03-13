#pragma once
#include "main.h"
#include "cEntity-cResource.h"

typedef std::unordered_map<std::string, cEntity*>   tEntityMap;
typedef std::unordered_map<std::string, cResource*>	tResourceMap;

class cWorld
{
public:
	tEntityMap		WorldEntities;
	tResourceMap	WorldResources;

	void			AddEntity(cEntity* Entity, char* Name);
	void			AddResource(cResource* Resource, char* Name);

	void			DeleteEntity(char* Name);
	void			DeleteResource(char* Name);

	cEntity*		GetEntity(char* Name);
	cResource*		GetResource(char* Name);

	void			LoadWorldFile(char* FileName);
	void			CreateWorldFile(char* FileName);

	void			Update(double GameTime);
	void			Draw();
};
