#pragma once
#include <string>
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSprite;
class GameEngineRenderer;
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

	void MapInit(const std::string& _FolderName);
protected:

private:
	std::string FolderName;
	GameEngineSprite* MainTexture = nullptr;

	void Start() override;
};