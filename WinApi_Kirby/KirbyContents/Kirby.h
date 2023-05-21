#pragma once

#include "ActorEnum.h"
#include "BaseActor.h"

#include <string>

class Kirby : public BaseActor
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
	virtual void StateUpdate(float _Delta);
	virtual void ChangeState(KirbyState _State);

	virtual void IdleStart();
	virtual void DownStart();
	virtual void SlideStart();
	virtual void JumpStart();
	virtual void JumpToDownStart();
	virtual void JumpToLandStart();
	virtual void WalkStart();

	virtual void IdleUpdate(float _Delta);
	virtual void DownUpdate(float _Delta);
	virtual void SlideUpdate(float _Delta);
	virtual void JumpUpdate(float _Delta);
	virtual void JumpToDownUpdate(float _Delta);
	virtual void JumpToLandUpdate(float _Delta);
	virtual void WalkUpdate(float _Delta);

	virtual void DirCheck();

	virtual void ChangeAnimationState(const std::string& _StateName);

	KirbyState State = KirbyState::Max;
	std::string CurState = "";
	ActorDir Dir = ActorDir::Right;
private:
	void Start() override;
	void Update(float _Delta) override;

	float Speed = 300.0f;
	float JumpPower = 300.0f;
};