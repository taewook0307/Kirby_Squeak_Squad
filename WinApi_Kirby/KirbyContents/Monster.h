#pragma once

#include "ActorEnum.h"
#include "BaseActor.h"

#include <string>
#include <vector>
#include <GameEngineCore/GameEngineCollision.h>

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

	MonsterType GetMonsterType() const
	{
		return Type;
	}

protected:
	virtual void StateUpdate(float _Delta);
	virtual void ChangeState(MonsterState _State);

	void IdleStart();
	void WalkStart();
	void AttackStart();
	void DamageStart();

	virtual void IdleUpdate(float _Delta);
	virtual void WalkUpdate(float _Delta);
	virtual void AttackUpdate(float _Delta);
	virtual void DamageUpdate(float _Delta);

	void DirChange();

	virtual void ChangeAnimationState(const std::string& _StateName);

	MonsterState State = MonsterState::Max;
	std::string CurState = "";
	ActorDir Dir = ActorDir::Right;
private:
	float RatioValue = 3.0f;
	float Speed = BASEPOWER / 3 * 2;
	MonsterType Type = MonsterType::Normal;

	std::vector<GameEngineCollision*> Col;

	void Start() override;
	void Update(float _Delta) override;
};

