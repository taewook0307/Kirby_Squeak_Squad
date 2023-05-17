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

	GameEngineRenderer* MainRenderer = nullptr;
protected:
	void StateUpdate(float _Delta);

	void IdleStart();
	void WalkStart();
	void StopStart();
	void JumpStart();

	void IdleUpdate(float _Delta);
	void WalkUpdate(float _Delta);
	void StopUpdate(float _Delta);
	void JumpUpdate(float _Delta);

	void ChangeState(ActorState _State);

	ActorState State = ActorState::Max;
	ActorDir Dir = ActorDir::Right;

	void DirChange();
private:
	void Start() override;
	void Update(float _Delta) override;

	float Speed = 300.0f;
};

