#pragma once

#include "GameEngineObject.h"

#include <map>
#include <vector>
#include <string>
#include <GameEngineBase/GameEngineMath.h>

class GameEngineActor;
class GameEngineCollision : public GameEngineObject
{
public:
	// constrcuter destructer
	GameEngineCollision();
	~GameEngineCollision();

	// delete Function
	GameEngineCollision(const GameEngineCollision& _Other) = delete;
	GameEngineCollision(GameEngineCollision&& _Other) noexcept = delete;
	GameEngineCollision& operator=(const GameEngineCollision& _Other) = delete;
	GameEngineCollision& operator=(GameEngineCollision&& _Other) noexcept = delete;

protected:

private:

};

