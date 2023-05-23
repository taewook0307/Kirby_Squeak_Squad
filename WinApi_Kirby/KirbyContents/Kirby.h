#pragma once

#include "ActorEnum.h"
#include "BaseActor.h"

#include <string>

#define EMPTYCOLOR RGB(255,255,255)

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
	void StateUpdate(float _Delta);
	void ChangeState(KirbyState _State);

	void IdleStart();
	void DownStart();
	void SlideStart();
	void JumpStart();
	void JumpToDownStart();
	void JumpToLandStart();
	void WalkStart();
	void RunStart();
	void StopStart();

	void IdleUpdate(float _Delta);
	void DownUpdate(float _Delta);
	void SlideUpdate(float _Delta);
	void JumpUpdate(float _Delta);
	void JumpToDownUpdate(float _Delta);
	void JumpToLandUpdate(float _Delta);
	void WalkUpdate(float _Delta);
	void RunUpdate(float _Delta);

	void DirCheck();

	virtual void ChangeAnimationState(const std::string& _StateName);

	void CameraMove(float4 _MovePos);

	void KirbyGravity(float _Delta);

	KirbyState State = KirbyState::Max;
	std::string CurState = "";
	ActorDir Dir = ActorDir::Right;

private:
	void Start() override;
	void Update(float _Delta) override;

	float Speed = 300.0f;
	float JumpPower = 300.0f;
};