#include "ResourcesManager.h"

ResourcesManager ResourcesManager::Inst;

/* 포인터
ResourcesManager ResourcesManager::Inst = new ResourcesManager();
ResourcesManager ResourcesManager::Inst;
*/

bool ResourcesManager::IsLoadTexture(const std::string& _Image)
{
	return false;
}

ResourcesManager::ResourcesManager()
{
}

ResourcesManager::~ResourcesManager()
{
}