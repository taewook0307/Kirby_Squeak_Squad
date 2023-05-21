#pragma once

#include <string>
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSprite;
class GameEngineRenderer;
class GameEngineWindowTexture;
class Map : public GameEngineActor
{
public:
	// constrcuter destructer
	Map();
	~Map();

	// delete Function
	Map(const Map& _Other) = delete;
	Map(Map&& _Other) noexcept = delete;
	Map& operator=(const Map& _Other) = delete;
	Map& operator=(Map&& _Other) noexcept = delete;

	GameEngineRenderer* MainRenderer = nullptr;
	GameEngineRenderer* DebugRenderer = nullptr;

	void MapInit(const std::string& _PathName, const std::string& _BitMapFIleName);

	void SwitchRender();
protected:

private:
	std::string PathName = "";
	std::string DebugBitMapName = "";

	GameEngineSprite* MainSprite = nullptr;
	GameEngineWindowTexture* DebugTexture = nullptr;

	bool SwitchRenderValue = true;
};