#pragma once

#include "Monster.h"

#define LEFTSEARCHCOLLISIONPOS { -140.0f, -30.0f }
#define RIGHTTSEARCHCOLLISIONPOS { 140.0f, -30.0f }
#define SEARCHCOLLISONSCALE { 160.0f, 70.0f }
#define ATTACKDISTANCE 170.0f
#define ATTACKCOLLISIONSCALE { 130.0f, 70.0f }

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
	MonsterType GetMonsterType() const override
	{
		return Type;
	}

	GameEngineRenderer* MainRenderer = nullptr;
	GameEngineCollision* AttackCollision = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	GameEngineCollision* SearchCollision = nullptr;

	void DirChange() override;
	void ChangeAnimationState(const std::string& _StateName) override;

	void IdleUpdate(float _Delta) override;
	void WalkUpdate(float _Delta) override;
	void DamageUpdate(float _Delta) override;
	void AttackUpdate(float _Delta) override;

	MonsterState State = MonsterState::Max;
	std::string CurState = "";
	ActorDir Dir = ActorDir::Left;
private:
	float RatioValue = 3.0f;
	float Speed = BASEPOWER * 0.5f;
	MonsterType Type = MonsterType::Ice;
	std::vector<GameEngineCollision*> Col;

	void Start() override;
};