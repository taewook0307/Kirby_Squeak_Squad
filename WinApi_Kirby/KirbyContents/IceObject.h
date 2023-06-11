#pragma once

#include "ActorEnum.h"

#include <vector>
#include <GameEngineCore/GameEngineActor.h>

#define BASESPEED 500.0f
#define STARCOLLISIONSCALE { 70.0f, 70.0f }
#define STARCOLLISIONPOS { 0.0f, -40.0f }

class IceObject : public GameEngineActor
{
public:
	// constrcuter destructer
	IceObject();
	~IceObject();

	// delete Function
	IceObject(const IceObject& _Other) = delete;
	IceObject(IceObject&& _Other) noexcept = delete;
	IceObject& operator=(const IceObject& _Other) = delete;
	IceObject& operator=(IceObject&& _Other) noexcept = delete;

	class GameEngineRenderer* MainRenderer;
	class GameEngineCollision* AttackCollision;

protected:

private:
	float Speed = BASESPEED;
	float RatioValue = 4.0f;

	std::vector<GameEngineCollision*> IceCol;

	bool CollisionCheck = false;

	void Start() override;
	void Update(float _Delta) override;
};

