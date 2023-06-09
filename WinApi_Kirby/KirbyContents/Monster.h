#pragma once

#include "ActorEnum.h"
#include "BaseActor.h"

#include <string>
#include <vector>
#include <GameEngineCore/GameEngineCollision.h>

#define MONSTERSPEED 150.0f
#define MONSTERBODYCOLLISONPOS { 0.0f, -30.0f }
#define MONSTERBODYCOLLISIONSCALE { 70.0f, 70.0f }

class Monster : public BaseActor
{
public:
	// constrcuter destructer
	Monster();
	~Monster();

	// delete Function
	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;

	virtual MonsterType GetMonsterType() const
	{
		return Type;
	}

protected:
	virtual void StateUpdate(float _Delta);
	virtual void ChangeState(MonsterState _State);

	void IdleStart();
	void WalkStart();
	void DamageStart();

	virtual void IdleUpdate(float _Delta);
	virtual void WalkUpdate(float _Delta);
	virtual void DamageUpdate(float _Delta);

	virtual void DirChange();

	virtual void ChangeAnimationState(const std::string& _StateName);

	MonsterState State = MonsterState::Max;
	std::string CurState = "";
	ActorDir Dir = ActorDir::Left;
	float RatioValue = 3.0f;
	float Speed = MONSTERSPEED;
	MonsterType Type = MonsterType::Normal;
	std::vector<GameEngineCollision*> Col;

private:
	void Start() override;
	void Update(float _Delta) override;
};

