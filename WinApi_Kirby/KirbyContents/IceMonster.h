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

	/*void IdleStart() override;
	void WalkStart() override;
	void DamageStart() override;
	void AttackStart() override;

	void IdleUpdate(float _Delta) override;
	void WalkUpdate(float _Delta) override;
	void DamageUpdate(float _Delta) override;
	void AttackUpdate(float _Delta) override;*/

private:
	float Speed = 300.0f;
};