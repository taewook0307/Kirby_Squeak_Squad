#pragma once
#include <string>
#include <map>
#include <GameEngineBase/GameEnginePath.h>

/*
싱글톤
생성자를 private로 시키고
내부에 static이든 참조형이든 자기자신의 객체 하나를 자신이 들고 있는 디자인 패턴
*/

class GameEngineWindowTexture;
class ResourcesManager
{
public:
	// delete Function
	ResourcesManager(const ResourcesManager& _Other) = delete;
	ResourcesManager(ResourcesManager&& _Other) noexcept = delete;
	ResourcesManager& operator=(const ResourcesManager& _Other) = delete;
	ResourcesManager& operator=(ResourcesManager&& _Other) noexcept = delete;

	static ResourcesManager& GetInst()
	{
		return Inst;
	}

	/*
	포인터를 이용한 싱글톤
	static ResourcesManager* GetInst()
	{
		if (nullptr == Inst)
		{
			Inst = new ResourcesManager();
		}
		return Inst;
	}

	static void Destory()
	{
		if (nullptr != Inst)
		{
			delete Inst;
			Inst = nullptr;
		}
	}

	static void ResetInst()
	{
		if (nullptr != Inst)
		{
			delete Inst;
			Inst = new ResourcesManager();
		}
	}
	*/

	GameEngineWindowTexture* TextureLoad(const std::string& _Path)
	{
		GameEnginePath LoadPath = _Path;
		return TextureLoad(LoadPath.GetFileName(), _Path);
	}

	GameEngineWindowTexture* TextureLoad(const std::string& _Name, const std::string& _Path);

	GameEngineWindowTexture* FindTexture(const std::string& _Name);

	bool IsLoadTexture(const std::string& _Name);

protected:

private:
	static ResourcesManager Inst;

	std::map<std::string, GameEngineWindowTexture*> AllTexture;

	/*
	static ResourcesManager* Inst;
	*/

	// constrcuter destructer
	ResourcesManager();
	~ResourcesManager();
};