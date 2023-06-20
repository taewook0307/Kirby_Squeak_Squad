#pragma once

#include "AttackMonster.h"

#define LEFTSEARCHCOLLISIONPOS { -140.0f, -30.0f }
#define RIGHTTSEARCHCOLLISIONPOS { 140.0f, -30.0f }
#define SEARCHCOLLISONSCALE { 160.0f, 70.0f }
#define TORNADOATTACKCOLLISIONSCALE { 80.0f, 80.0f }

class TornadoMonster : public AttackMonster
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

	GameEngineCollision* AttackCollision = nullptr;
	GameEngineCollision* SearchCollision = nullptr;

	void ChangeAnimationState(const std::string& _StateName) override;

	void IdleUpdate(float _Delta) override;
	void WalkUpdate(float _Delta) override;
	void AttackUpdate(float _Delta) override;

	MonsterType Type = MonsterType::Tornado;
private:
	float WalkTimer = 2.0f;

	void Start() override;
};

