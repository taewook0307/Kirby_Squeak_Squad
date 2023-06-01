#pragma once

#include "Monster.h"

#define LEFTSEARCHCOLLISIONPOS { -140.0f, -30.0f }
#define RIGHTTSEARCHCOLLISIONPOS { 140.0f, -30.0f }
#define SEARCHCOLLISONSCALE { 160.0f, 70.0f }
#define TORNADOATTACKCOLLISIONSCALE { 80.0f, 80.0f }

class TornadoMonster : public Monster
{
public:
	// constrcuter destructer
	TornadoMonster();
	~TornadoMonster();

	// delete Function
	TornadoMonster(const TornadoMonster& _Other) = delete;
	TornadoMonster(TornadoMonster&& _Other) noexcept = delete;
	TornadoMonster& operator=(const TornadoMonster& _Other) = delete;
	TornadoMonster& operator=(TornadoMonster&& _Other) noexcept = delete;

protected:
	MonsterType GetMonsterType() const override
	{
		return Type;
	}

	GameEngineRenderer* MainRenderer = nullptr;
	GameEngineCollision* AttackCollision = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	GameEngineCollision* SearchCollision = nullptr;

	void ChangeAnimationState(const std::string& _StateName) override;

	void IdleUpdate(float _Delta) override;
	void WalkUpdate(float _Delta) override;
	void DamageUpdate(float _Delta) override;
	void AttackUpdate(float _Delta) override;

	float RatioValue = 3.0f;
	float Speed = BASEPOWER * 0.5f;
	MonsterType Type = MonsterType::Tornado;
	std::vector<GameEngineCollision*> Col;
private:
	void Start() override;
};

