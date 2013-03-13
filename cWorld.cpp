#include "cWorld.h"

void cWorld::AddEntity(cEntity* Entity, char* Name)
{
	WorldEntities.insert(tEntityMap::value_type(std::string(Name),Entity));
}

void cWorld::AddResource(cResource* Resource, char* Name)
{
	WorldResources.insert(tResourceMap::value_type(std::string(Name),Resource));
}

void cWorld::DeleteEntity(char* Name)
{
	WorldEntities.erase(std::string(Name));
}

void cWorld::DeleteResource(char* Name)
{
	WorldResources.erase(std::string(Name));
}

cEntity* cWorld::GetEntity(char* Name)
{
	return WorldEntities[std::string(Name)];
}

cResource* cWorld::GetResource(char* Name)
{
	return WorldResources[std::string(Name)];
}

void cWorld::LoadWorldFile(char* FileName)
{
	/*TODO: Caricamento di un file (xml?) contentente una lista
	  delle entità e delle risorse 
	*/
}

void cWorld::CreateWorldFile(char* FileName)
{
	/*TODO: Salva in un file (xml?) la lista delle entità e delle
      risorse nel mondo*/
}

void cWorld::Update(double GameTime)
{
	tEntityMap::iterator it;
	for(it = WorldEntities.begin() ; it!= WorldEntities.end() ; it++)
	{
		it->second->Update(GameTime);
	}
}

void cWorld::Draw()
{
	tEntityMap::iterator it;
	for(it = WorldEntities.begin() ; it!= WorldEntities.end() ; it++)
	{
		it->second->Draw();
	}
}