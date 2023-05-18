#pragma once

#include "ActorEnum.h"

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
	void ChangeState(KirbyState _State);

	void IdleStart();
	void WalkStart();

	void IdleUpdate(float _Delta);
	void WalkUpdate(float _Delta);

	KirbyState State = KirbyState::Max;
	std::string CurState = "";
	ActorDir Dir = ActorDir::Right;

	void DirChange();

	void ChangeAnimationState(const std::string& _StateName);
private:
	void Start() override;
	void Update(float _Delta) override;

	float Speed = 300.0f;
};