#pragma once

#include "ActorEnum.h"

#include <GameEngineCore/GameEngineActor.h>

#define BASESPEED 500.0f

class AttackObject : public GameEngineActor
{
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

	void Start() override;
	void Update(float _Delta) override;
};

