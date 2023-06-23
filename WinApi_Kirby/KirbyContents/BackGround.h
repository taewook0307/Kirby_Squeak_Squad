#pragma once
#include <string>
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRenderer;
class BackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	BackGround();
	~BackGround();

	// delete Function
	BackGround(const BackGround& _Other) = delete;
	BackGround(BackGround&& _Other) noexcept = delete;
	BackGround& operator=(const BackGround& _Other) = delete;
	BackGround& operator=(BackGround&& _Other) noexcept = delete;

	static BackGround* GetMainBackGround()
	{
		return MainBackGround;
	}

protected:

private:
	static BackGround* MainBackGround;

	class GameEngineRenderer* MainRenderer = nullptr;
	class GameEngineWindowTexture* MainTexture = nullptr;

	void Start() override;
};