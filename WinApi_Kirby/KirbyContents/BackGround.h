#pragma once
#include <string>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRenderer;
class GameEngineWindowTexture;
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

	float4 GetMainTextureScale() const
	{
		return MainTexture->GetScale();
	}

protected:

private:
	static BackGround* MainBackGround;

	GameEngineRenderer* MainRenderer = nullptr;
	GameEngineWindowTexture* MainTexture = nullptr;

	void Start() override;
};