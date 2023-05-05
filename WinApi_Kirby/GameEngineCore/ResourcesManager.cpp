#include "ResourcesManager.h"
#include "GameEngineTexture.h"

#include <GameEngineBase/GameEngineString.h>

ResourcesManager ResourcesManager::Inst;

/* 포인터
ResourcesManager ResourcesManager::Inst = new ResourcesManager();
ResourcesManager ResourcesManager::Inst;
*/

ResourcesManager::ResourcesManager()
{
}

ResourcesManager::~ResourcesManager()
{
	for (const std::pair<std::string, GameEngineTexture*> Pair : AllTexture)
	{
		GameEngineTexture* Texture = Pair.second;

		if (nullptr != Texture)
		{
			delete Texture;
			Texture = nullptr;
		}
	}
}

bool ResourcesManager::IsLoadTexture(const std::string& _Name)
{
	return FindTexture(_Name) != nullptr;
}

void ResourcesManager::TextureLoad(const std::string& _Name, const std::string& _Path)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);

	GameEngineTexture* LoadTexture = new GameEngineTexture();

	LoadTexture->ResLoad(_Path);

	AllTexture.insert(std::make_pair(UpperName, LoadTexture));
}

GameEngineTexture* ResourcesManager::FindTexture(const std::string& _Name)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);

	std::map<std::string, GameEngineTexture*>::iterator FindIter = AllTexture.find(UpperName);

	if (FindIter == AllTexture.end())
	{
		return nullptr;
	}

	return FindIter->second;
}