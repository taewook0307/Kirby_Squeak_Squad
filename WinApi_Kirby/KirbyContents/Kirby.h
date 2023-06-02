#pragma once

#include "ActorEnum.h"
#include "BaseActor.h"

#include <string>
#include <vector>

#define BODYCOLLISIONPOS { 0.0f, -30.0f }
#define BODYCOLLISIONSCALE { 70.0f, 70.0f }
#define ATTACKCOLLSIONSCALE { 80.0f, 80.0f }

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

	GameEngineCollision* AttackCollision = nullptr;

	KirbyState& GetKirbyState()
	{
		return State;
	}

	MonsterType& GetKeepType()
	{
		return KeepType;
	}

protected:
	virtual void StateUpdate(float _Delta);
	virtual void ChangeState(KirbyState _State);

	void IdleStart();
	void DownStart();
	void SlideStart();
	void JumpStart();
	void JumpToDownStart();
	void JumpToLandStart();
	void WalkStart();
	void RunStart();
	void StopStart();
	void StopToIdleStart();
	void BreatheStart();
	void FlyStart();
	void BreatheOutLandStart();
	void BreatheOutStart();
	void DropStart();
	void FlyToLandStart();
	void FlyToTurnUpStart();
	void FlyToTurnLandStart();
	void LevelMoveStart();
	void DamageStart();
	void DamageLandStart();
	void AttackReadyStart();
	void AttackLoopStart();
	void AttackStart();
	void KeepStart();
	void KeepIdleStart();
	void KeepWalkStart();

	void IdleUpdate(float _Delta);
	void DownUpdate(float _Delta);
	void SlideUpdate(float _Delta);
	void JumpUpdate(float _Delta);
	void JumpToDownUpdate(float _Delta);
	void JumpToLandUpdate(float _Delta);
	void WalkUpdate(float _Delta);
	void RunUpdate(float _Delta);
	void StopUpdate(float _Delta);
	void StopToIdleUpdate(float _Delta);
	void BreatheUpdate(float _Delta);
	void FlyUpdate(float _Delta);
	void BreatheOutLandUpdate(float _Delta);
	void BreatheOutUpdate(float _Delta);
	void DropUpdate(float _Delta);
	void FlyToLandUpdate(float _Delta);
	void FlyToTurnUpUpdate(float _Delta);
	void FlyToTurnLandUpdate(float _Delta);
	void LevelMoveUpdate(float _Delta);
	void DamageUpdate(float _Delta);
	void DamageLandUpdate(float _Delta);
	virtual void AttackReadyUpdate(float _Delta);
	virtual void AttackLoopUpdate(float _Delta);
	virtual void AttackUpdate(float _Delta);
	void KeepUpdate(float _Delta);
	void KeepIdleUpdate(float _Delta);
	void KeepWalkUpdate(float _Delta);

	virtual void DirCheck();

	virtual void ChangeAnimationState(const std::string& _StateName);

	void CameraMove(float4 _MovePos);

	void KirbyGravity(float _Delta);

	void IsCheckPosPointChange()
	{
		IsCheckPosPoint = !IsCheckPosPoint;
	}

	KirbyState State = KirbyState::Max;
	ActorDir Dir = ActorDir::Right;
	std::string CurState = "";
	float RatioValue = 4.0f;
	float Speed = BASEPOWER;
	float RunSpeed = Speed * 1.5f;
	float JumpPower = BASEPOWER;
	float FlyPower = BASEPOWER;
	std::vector<GameEngineCollision*> Col;

	bool IsCheckPosPoint = false;

private:
	MonsterType KeepType = MonsterType::Max;

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;
};