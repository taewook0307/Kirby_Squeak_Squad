#pragma once
#include <string>
#include <GameEngineCore/GameEngineActor.h>

class GameEngineWindowTexture;
class GameEngineRenderer;
class Map;
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

	void BackGroundInit(const std::string& _FileName, const std::string& _MapFileName = "");

protected:

private:
	std::string FileName = "";
	float4 Scale = float4::ZERO;
	GameEngineWindowTexture* MainTexture = nullptr;
	GameEngineRenderer* MainRenderer = nullptr;

	GameEngineWindowTexture* MapTexture = nullptr;

	void Update(float _Delta) override;
};