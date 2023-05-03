#pragma once
#include <string>

/*
싱글톤
생성자를 private로 시키고
내부에 static이든 참조형이든 자기자신의 객체 하나를 자신이 들고 있는 디자인 패턴
*/

class GameEngineTexture;
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

	void TextureLoad(const std::string& _Path)
	{

	}

	void TextureLoad(const std::string& _Name, const std::string& _Path)
	{

	}

	GameEngineTexture* FindTexture(const std::string& _Image);

	bool IsLoadTexture(const std::string& _Image);

protected:

private:
	static ResourcesManager Inst;

	/*
	static ResourcesManager* Inst;
	*/

	// constrcuter destructer
	ResourcesManager();
	~ResourcesManager();
};