#pragma once
#include "StateEnum.h"

#include <string>
#include <GameEngineCore/GameEngineActor.h>

class Kirby : public GameEngineActor
{
public:
	// constrcuter destructer
	Kirby();
	~Kirby();

	// delete Function
	Kirby(const Kirby& _Other) = delete;
	Kirby(Kirby&& _Other) noexcept = delete;
	Kirby& operator=(const Kirby& _Other) = delete;
	Kirby& operator=(Kirby&& _Other) noexcept = delete;

	GameEngineRenderer* MainRenderer = nullptr;
protected:
	void StateUpdate(float _Delta);

	void IdleStart();
	void WalkStart();
	void RunStart();
	void StopStart();
	void JumpStart();

	void IdleUpdate(float _Delta);
	void WalkUpdate(float _Delta);
	void RunUpdate(float _Delta);
	void StopUpdate(float _Delta);
	void JumpUpdate(float _Delta);

	void ChangeState(PlayerState _State);

	PlayerState State = PlayerState::Max;

private:
	void Start() override;
	void Update(float _Delta) override;

	float Speed = 300.0f;
};