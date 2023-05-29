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
	virtual void StateUpdate(float _Delta);
	virtual void ChangeState(MonsterState _State);

	void WalkUpdate(float _Delta) override;
	void AttackUpdate(float _Delta) override;
	void DamageUpdate(float _Delta) override;

	void ChangeAnimationState(const std::string& _StateName) override;
private:
	float RatioValue = 3.0f;

	void Start() override;
};

