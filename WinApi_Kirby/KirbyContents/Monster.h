#pragma once

#include "ActorEnum.h"

#include <GameEngineCore/GameEngineActor.h>

class Monster : public GameEngineActor
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
	void ChangeState(ActorState _State);
	void Start() override;
	void Update(float _Delta) override;

	virtual void IdleStart();
	virtual void WalkStart();
	virtual void RunStart();
	virtual void StopStart();
	virtual void AttackStart();
	virtual void DamageStart();
	virtual void JumpStart();

	virtual void IdleUpdate(float _Delta);
	virtual void WalkUpdate(float _Delta);
	virtual void RunUpdate(float _Delta);
	virtual void StopUpdate(float _Delta);
	virtual void AttackUpdate(float _Delta);
	virtual void DamageUpdate(float _Delta);
	virtual void JumpUpdate(float _Delta);

	ActorState State = ActorState::Max;
	ActorDir Dir = ActorDir::Right;

	void DirChange(int _Value);

private:
	float Speed = 300.0f;
};

