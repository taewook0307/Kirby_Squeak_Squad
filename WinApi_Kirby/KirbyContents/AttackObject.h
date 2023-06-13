#pragma once

#include "BaseActor.h"
#include "ActorEnum.h"

#include <vector>

#define STARCOLLISIONSCALE { 70.0f, 70.0f }
#define STARCOLLISIONPOS { 0.0f, -40.0f }

class AttackObject : public BaseActor
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

protected:

private:
	ActorDir Dir = ActorDir::Right;
	float Speed = 500.0f;
	float RatioValue = 4.0f;

	std::vector<GameEngineCollision*> StarCol;

	bool CollisionCheck = false;

	void Start() override;
	void Update(float _Delta) override;
};

