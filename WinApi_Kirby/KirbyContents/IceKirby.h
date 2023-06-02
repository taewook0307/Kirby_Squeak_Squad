#pragma once

#include "Kirby.h"

#define LEFTATTACKCOLLISIONPOS { -140.0f, -30.0f }
#define RIGHTTATTACKCOLLISIONPOS { 140.0f, -30.0f }
#define ICEATTACKCOLLISIONSCALE { 130.0f, 70.0f }

class IceKirby : public Kirby
{
public:
	// constrcuter destructer
	IceKirby();
	~IceKirby();

	// delete Function
	IceKirby(const IceKirby& _Other) = delete;
	IceKirby(IceKirby&& _Other) noexcept = delete;
	IceKirby& operator=(const IceKirby& _Other) = delete;
	IceKirby& operator=(IceKirby&& _Other) noexcept = delete;

protected:
	void StateUpdate(float _Delta) override;
	void ChangeState(KirbyState _State) override;
	void ChangeAnimationState(const std::string& _StateName) override;

	void AttackLoopUpdate(float _Delta) override;
private:
	/*KirbyState State = KirbyState::Max;
	ActorDir Dir = ActorDir::Right;
	std::string CurState = "";
	float RatioValue = 4.0f;
	float Speed = BASEPOWER;
	float RunSpeed = Speed * 1.5f;
	float JumpPower = BASEPOWER;
	float FlyPower = BASEPOWER;
	std::vector<GameEngineCollision*> Col;*/
	void Start() override;
};

