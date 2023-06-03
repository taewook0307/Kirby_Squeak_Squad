#include "ResourcesManager.h"
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineBase/GameEngineString.h>
#include "GameEngineSprite.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineDirectory.h>

ResourcesManager ResourcesManager::Inst;

// 포인터 
// ResourcesManager* ResourcesManager::Inst = new ResourcesManager();
// ResourcesManager* ResourcesManager::Inst;


bool ResourcesManager::IsLoadTexture(const std::string& _Name)
{
	return FindTexture(_Name) != nullptr;
}

ResourcesManager::ResourcesManager()
{
}

ResourcesManager::~ResourcesManager()
{
	for (const std::pair<std::string, GameEngineWindowTexture*>& Pair : AllTexture)
	{
		GameEngineWindowTexture* Texture = Pair.second;

		if (nullptr != Texture)
		{
			delete Texture;
			Texture = nullptr;
		}
	}

	for (const std::pair<std::string, GameEngineSprite*>& Pair : AllSprite)
	{
		GameEngineSprite* Sprite = Pair.second;

		if (nullptr != Sprite)
		{
			delete Sprite;
			Sprite = nullptr;
		}
	}

}

GameEngineWindowTexture* ResourcesManager::FindTexture(const std::string& _Name)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);


	std::map<std::string, GameEngineWindowTexture*>::iterator FindIter = AllTexture.find(UpperName);

	if (FindIter == AllTexture.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

GameEngineWindowTexture* ResourcesManager::TextureCreate(const std::string& _Name, float4 _Scale)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);

	if (AllTexture.find(UpperName) != AllTexture.end())
	{
		MsgBoxAssert("같은 이름의 텍스처가 이미 존재합니다.");
		return nullptr;
	}

	// 동적 바인딩이라고 합니다.
	GameEngineWindowTexture* CreateTexture = new GameEngineWindowTexture();

	CreateTexture->ResCreate(_Scale);

	AllTexture.insert(std::make_pair(UpperName, CreateTexture));

	return CreateTexture;

}

GameEngineWindowTexture* ResourcesManager::TextureLoad(const std::string& _Name, const std::string& _Path)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);

	if (AllTexture.find(UpperName) != AllTexture.end())
	{
		MsgBoxAssert("같은 이름의 텍스처가 이미 존재합니다.");
		return nullptr;
	}

	// 동적 바인딩이라고 합니다.
	GameEngineWindowTexture* LoadTexture = new GameEngineWindowTexture();

	LoadTexture->ResLoad(_Path);

	AllTexture.insert(std::make_pair(UpperName, LoadTexture));

	return LoadTexture;
}

GameEngineSprite* ResourcesManager::FindSprite(const std::string& _Name)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);

	std::map<std::string, GameEngineSprite*>::iterator FindIter = AllSprite.find(UpperName);

	if (FindIter == AllSprite.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

GameEngineSprite* ResourcesManager::CreateSpriteSheet(const std::string& _SpriteName
	, const std::string& _TexturePath
	, int _XCount
	, int _YCount)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_SpriteName);

	if (nullptr != FindSprite(UpperName))
	{
		MsgBoxAssert("이미 로드한 스프라이트를 또 로드하려고 했습니다.");
	}

	GameEnginePath Path = _TexturePath;

	GameEngineWindowTexture* Texture = ResourcesManager::FindTexture(Path.GetFileName());

	if (nullptr == Texture)
	{
		Texture = ResourcesManager::TextureLoad(_TexturePath);
	}

	float4 Scale = Texture->GetScale();

	GameEngineSprite* NewSprite = new GameEngineSprite();

	NewSprite->CreateSpriteSheet(Texture, _XCount, _YCount);

	AllSprite.insert(std::make_pair(UpperName, NewSprite));

	return NewSprite;
}

GameEngineSprite* ResourcesManager::CreateSpriteFolder(const std::string& _SpriteName, const std::string& _Path)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_SpriteName);

	if (nullptr != FindSprite(UpperName))
	{
		MsgBoxAssert("이미 로드한 스프라이트를 또 로드하려고 했습니다.");
	}

	GameEngineSprite* NewSprite = new GameEngineSprite();

	NewSprite->CreateSpriteFolder(_Path);

	AllSprite.insert(std::make_pair(UpperName, NewSprite));

	return NewSprite;
}

void ResourcesManager::TextureFileLoad(const std::string& _FileName, const std::string& _Path)
{
	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();

		std::string ParentPath = GameEnginePath::GetParentString(_Path);
		FilePath.MoveParentToExistsChild(ParentPath);
		FilePath.MoveChild(_Path + _FileName);
		TextureLoad(FilePath.GetStringPath());
	}
}

void ResourcesManager::SpriteFileLoad(const std::string& _FileName, const std::string& _Path, int _XCount, int _YCount)
{
	if (true == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		return;
	}

	GameEnginePath FilePath;

	// _Path
	// "BBB\\CCC\\DDD"
	// "BBB\\CCC\\DDD\\FFF"
	std::string ParentPath = GameEnginePath::GetParentString(_Path);
	// ParentPath
	// "BBB"

	FilePath.MoveParentToExistsChild(ParentPath);
	FilePath.MoveChild(_Path);

	ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath(_FileName), _XCount, _YCount);
}