#pragma once
#include "GameEngineRenderer.h"

#include <map>
#include <list>

class GameEngineRenderer;
class GameEngineCamera
{
public:
	// constrcuter destructer
	GameEngineCamera();
	~GameEngineCamera();

	// delete Function
	GameEngineCamera(const GameEngineCamera& _Other) = delete;
	GameEngineCamera(GameEngineCamera&& _Other) noexcept = delete;
	GameEngineCamera& operator=(const GameEngineCamera& _Other) = delete;
	GameEngineCamera& operator=(GameEngineCamera&& _Other) noexcept = delete;

protected:

private:
	std::map<int, std::list<GameEngineRenderer*>> Renderers;
};