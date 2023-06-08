#pragma once

#include "ActorEnum.h"

#include <vector>
#include <GameEngineCore/GameEngineActor.h>

#define BASESPEED 500.0f
#define STARCOLLISIONSCALE { 70.0f, 70.0f }
#define STARCOLLISIONPOS { 0.0f, -40.0f }

class AttackObject : public GameEngineActor
{
	friend class Kirby;
public:
	// constrcuter destructer
	AttackObject();
	~AttackObject();

	// delete Function
	AttackObject(const AttackObject& _Other) = delete;
	AttackObject(AttackObject&& _Other) noexcept = delete;
	AttackObject& operator=(const AttackObject& _Other) = delete;
	AttackObject& operator=(AttackObject&& _Other) noexcept = delete;

	class GameEngineRenderer* MainRenderer;
	class GameEngineCollision* AttackCollision;

	void SetDir(const ActorDir _Dir)
	{
		Dir = _Dir;
	}

	void SetSpeed(const float _Speed)
	{
		Speed = _Speed;
	}
protected:

private:
	ActorDir Dir = ActorDir::Right;
	float Speed = BASESPEED;
	float RatioValue = 4.0f;

	std::vector<GameEngineCollision*> StarCol;

	void Start() override;
	void Update(float _Delta) override;
};

