#pragma once

#include "Monster.h"
#include "ActorEnum.h"

#include <vector>

#define BOSSATTACKCOLLISIONSCALE { 70.0f, 70.0f }
#define BOSSATTACKCOLLISIONPOS { 0.0f, -40.0f }

class BossAttackObject : public Monster
{
	friend class BossMonster;
public:
	// constrcuter destructer
	BossAttackObject();
	~BossAttackObject();

	// delete Function
	BossAttackObject(const BossAttackObject& _Other) = delete;
	BossAttackObject(BossAttackObject&& _Other) noexcept = delete;
	BossAttackObject& operator=(const BossAttackObject& _Other) = delete;
	BossAttackObject& operator=(BossAttackObject&& _Other) noexcept = delete;

	class GameEngineRenderer* MainRenderer;
	class GameEngineCollision* AttackCollision;
protected:

private:
	float Speed = 300.0f;
	float RatioValue = 4.0f;
	bool Move = true;
	bool AttackSuccess = false;

	std::vector<GameEngineCollision*> BossAttackCol;

	void Start() override;
	void Update(float _Delta) override;
};