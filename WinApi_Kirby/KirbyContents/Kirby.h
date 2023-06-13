#pragma once

#include "ActorEnum.h"
#include "BaseActor.h"

#include <string>
#include <vector>

#define BASEPOWER 300.0f
#define FLYPOWER 300.0f

#define BODYCOLLISIONPOS { 0.0f, -30.0f }
#define BODYCOLLISIONSCALE { 70.0f, 70.0f }
#define LEFTINHALECOLLSIONSCALE { -150.0f, -40.0f }
#define RIGHTINHALECOLLSIONSCALE { 150.0f, -40.0f }
#define INHALECOLLSIONSCALE { 200.0f, 80.0f }

class AttackObject;
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

	KirbyState& GetKirbyState()
	{
		return State;
	}

	MonsterType& GetKeepType()
	{
		return KeepType;
	}

	bool GetMapChangeAnimationEnd() const
	{
		return MapChangeAnimationEnd;
	}

	void MapChangeAnimationEndReset()
	{
		MapChangeAnimationEnd = false;
	}

	inline int GetHp() const
	{
		return Hp;
	}

	inline int GetAtt() const
	{
		return Att;
	}

	inline bool GetDeathCheck() const
	{
		return DeathCheck;
	}

protected:
	virtual void StateUpdate(float _Delta);
	virtual void ChangeState(KirbyState _State);

	void IdleStart();
	void DownStart();
	void SlideStart();
	void JumpStart();
	void JumpToDropStart();
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
	void AttackStart();
	void AttackToIdleStart();
	void KeepStart();
	void KeepIdleStart();
	void KeepWalkStart();
	void KeepJumpStart();
	void KeepJumpToDropStart();
	void KeepJumpToLandStart();
	void KeepDamageStart();
	void ChangeStart();
	void DeathStart();

	void IdleUpdate(float _Delta);
	void DownUpdate(float _Delta);
	void SlideUpdate(float _Delta);
	virtual void JumpUpdate(float _Delta);
	virtual void JumpToDropUpdate(float _Delta);
	void JumpToLandUpdate(float _Delta);
	void WalkUpdate(float _Delta);
	void RunUpdate(float _Delta);
	void StopUpdate(float _Delta);
	void StopToIdleUpdate(float _Delta);
	void BreatheUpdate(float _Delta);
	void FlyUpdate(float _Delta);
	void BreatheOutLandUpdate(float _Delta);
	void BreatheOutUpdate(float _Delta);
	virtual void DropUpdate(float _Delta);
	void FlyToLandUpdate(float _Delta);
	void FlyToTurnUpUpdate(float _Delta);
	void FlyToTurnLandUpdate(float _Delta);
	void LevelMoveUpdate(float _Delta);
	void DamageUpdate(float _Delta);
	void DamageLandUpdate(float _Delta);
	void AttackReadyUpdate(float _Delta);
	virtual void AttackUpdate(float _Delta);
	virtual void AttackToIdleUpdate(float _Delta);
	void KeepUpdate(float _Delta);
	void KeepIdleUpdate(float _Delta);
	void KeepWalkUpdate(float _Delta);
	void KeepJumpUpdate(float _Delta);
	void KeepJumpToDropUpdate(float _Delta);
	void KeepJumpToLandUpdate(float _Delta);
	void KeepDamageUpdate(float _Delta);
	void ChangeUpdate(float _Delta);
	void DeathUpdate(float _Delta);

	virtual void DirCheck();

	virtual void ChangeAnimationState(const std::string& _StateName);

	void CameraMove(float4 _MovePos);

	void KirbyGravity(float _Delta);

	KirbyState State = KirbyState::Max;
	ActorDir Dir = ActorDir::Right;
	std::string CurState = "";
	float RatioValue = 4.0f;
	float Speed = BASEPOWER;
	float RunSpeed = Speed * 1.5f;
	float JumpPower = GRAVITYPOWER;
	float FlyPower = FLYPOWER;

	std::vector<GameEngineCollision*> Col;

	bool MapChangeAnimationEnd = false;

	void Damage(int _Value)
	{
		Hp -= _Value;
	}

	int Hp = BASEHP;
	int Att = BASEATT;

	bool DeathCheck = false;
private:
	GameEngineCollision* InhaleCollision = nullptr;
	MonsterType KeepType = MonsterType::Max;
	AttackObject* StarAttack = nullptr;

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;
};