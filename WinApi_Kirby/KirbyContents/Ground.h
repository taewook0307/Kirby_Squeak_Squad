#pragma once

#include <string>
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSprite;
class GameEngineRenderer;
class GameEngineWindowTexture;
class Ground : public GameEngineActor
{
public:
	// constrcuter destructer
	Ground();
	~Ground();

	// delete Function
	Ground(const Ground& _Other) = delete;
	Ground(Ground&& _Other) noexcept = delete;
	Ground& operator=(const Ground& _Other) = delete;
	Ground& operator=(Ground&& _Other) noexcept = delete;

	GameEngineRenderer* MainRenderer = nullptr;
	GameEngineRenderer* DebugRenderer = nullptr;

	void GroundInit(const std::string& _PathName, const std::string& _BitMapFIleName);

	void SwitchRender();
protected:

private:
	std::string PathName = "";
	std::string DebugBitMapName = "";

	GameEngineSprite* MainSprite = nullptr;
	GameEngineWindowTexture* DebugTexture = nullptr;

	bool SwitchRenderValue = true;
};