#pragma once

#include "AttackMonster.h"

#define SPARKATTACKCOLLISIONPOS { 0.0f, -55.0f }

class SparkMonster : public AttackMonster
{
public:
	// constrcuter destructer
	SparkMonster();
	~SparkMonster();

	// delete Function
	SparkMonster(const SparkMonster& _Other) = delete;
	SparkMonster(SparkMonster&& _Other) noexcept = delete;
	SparkMonster& operator=(const SparkMonster& _Other) = delete;
	SparkMonster& operator=(SparkMonster&& _Other) noexcept = delete;

protected:
	MonsterType GetMonsterType() const override
	{
		return Type;
	}

	GameEngineCollision* AttackCollision = nullptr;

	void ChangeAnimationState(const std::string& _StateName) override;

	void IdleUpdate(float _Delta) override;
	void WalkUpdate(float _Delta) override;
	void AttackUpdate(float _Delta) override;
	void DamageUpdate(float _Delta) override;

	MonsterType Type = MonsterType::Spark;
private:
	void Start() override;
};

