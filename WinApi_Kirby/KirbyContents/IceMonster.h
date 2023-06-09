#pragma once

#include "AttackMonster.h"

#define LEFTSEARCHCOLLISIONPOS { -140.0f, -30.0f }
#define RIGHTTSEARCHCOLLISIONPOS { 140.0f, -30.0f }
#define SEARCHCOLLISONSCALE { 160.0f, 70.0f }
#define ATTACKDISTANCE 170.0f
#define ATTACKCOLLISIONSCALE { 130.0f, 70.0f }

class IceMonster : public AttackMonster
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

	MonsterType Type = MonsterType::Ice;
private:
	void Start() override;
};