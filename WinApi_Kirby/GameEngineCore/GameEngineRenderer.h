#pragma once
#include "GameEngineObject.h"
#include <string>
#include <GameEngineBase/GameEngineMath.h>

class GameEngineWindowTexture;
class GameEngineCamera;
class GameEngineActor;
class GameEngineRenderer : public GameEngineObject
{
	friend class GameEngineCamera;
	friend class GameEngineActor;
public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	void SetTexture(const std::string& _Name);

	void SetRenderPos(const float4& _Value)
	{
		RenderPos = _Value;
	}

	void SetRenderScale(const float4& _Value)
	{
		RenderScale = _Value;
		ScaleCheck = true;
	}

	void SetCopyPos(const float4& _Value)
	{
		CopyPos = _Value;
	}

	void SetCopyScale(const float4& _Value)
	{
		CopyScale = _Value;
	}

	void SetRenderScaleToTexture();

protected:

private:
	GameEngineWindowTexture* Texture = nullptr;
	GameEngineActor* Master = nullptr;

	float4 RenderPos = float4::ZERO;
	float4 RenderScale = float4::ZERO;

	float4 CopyPos = float4::ZERO;
	float4 CopyScale = float4::ZERO;

	bool ScaleCheck = false;

	void Render(GameEngineCamera* _Camera);
};