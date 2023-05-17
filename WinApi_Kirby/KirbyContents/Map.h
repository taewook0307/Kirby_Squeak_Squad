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

	void MapAnimation(const std::string& _PathName);
protected:

private:
	std::string PathName;
	GameEngineSprite* MainSprite = nullptr;
};