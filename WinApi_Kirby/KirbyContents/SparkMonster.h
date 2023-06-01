#pragma once

#include "Monster.h"

class SparkMonster : public Monster
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

	GameEngineRenderer* MainRenderer = nullptr;
	GameEngineCollision* AttackCollision = nullptr;
	GameEngineCollision* BodyCollision = nullptr;

	void ChangeAnimationState(const std::string& _StateName) override;

	void IdleUpdate(float _Delta) override;
	void WalkUpdate(float _Delta) override;
	void DamageUpdate(float _Delta) override;
	void AttackUpdate(float _Delta) override;

	float RatioValue = 3.0f;
	float Speed = BASEPOWER * 0.5f;
	MonsterType Type = MonsterType::Spark;
	std::vector<GameEngineCollision*> Col;
private:
	void Start() override;
};

