#pragma once

#include "ActorEnum.h"
#include "BaseActor.h"

#include <string>

#define IDLE 0
#define WALK 1

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

protected:
	GameEngineRenderer* MainRenderer = nullptr;

	void StateUpdate(float _Delta);
	void ChangeState(MonsterState _State);
	void Start() override;
	void Update(float _Delta) override;

	void IdleStart();
	void WalkStart();
	void AttackStart();
	void DamageStart();

	virtual void IdleUpdate(float _Delta);
	virtual void WalkUpdate(float _Delta);
	virtual void AttackUpdate(float _Delta);
	virtual void DamageUpdate(float _Delta);

	virtual void ChangeAnimationState(const std::string& _StateName);

	MonsterState State = MonsterState::Max;
	std::string CurState = "";
	ActorDir Dir = ActorDir::Right;

	void DirChange(int _Value);
private:
	float Speed = BASEPOWER;
};

