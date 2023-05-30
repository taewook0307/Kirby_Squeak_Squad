#pragma once

#include "Monster.h"

class IceMonster : public Monster
{
public:
	// constrcuter destructer
	IceMonster();
	~IceMonster();

	// delete Function
	IceMonster(const IceMonster& _Other) = delete;
	IceMonster(IceMonster&& _Other) noexcept = delete;
	IceMonster& operator=(const IceMonster& _Other) = delete;
	IceMonster& operator=(IceMonster&& _Other) noexcept = delete;

protected:
	GameEngineRenderer* MainRenderer = nullptr;

	void ChangeAnimationState(const std::string& _StateName) override;

	void IdleUpdate(float _Delta) override;
	void WalkUpdate(float _Delta) override;
	void DamageUpdate(float _Delta) override;
	void AttackUpdate(float _Delta) override;

private:
	float RatioValue = 3.0f;

	float Speed = 300.0f;

	void Start() override;
};