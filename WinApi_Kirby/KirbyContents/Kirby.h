#pragma once

#include "ActorEnum.h"
#include "BaseActor.h"

#include <string>
#include <vector>

#define HPVALUE 120
#define BASEPOWER 300.0f
#define FLYPOWER 300.0f
#define NODAMAGETIMERVALUE 3.0f
#define CHECKINPUTTIMERVALUE 0.2f

#define BODYCOLLISIONPOS { 0.0f, -30.0f }
#define BODYCOLLISIONSCALE { 70.0f, 70.0f }
#define LEFTINHALECOLLSIONSCALE { -150.0f, -40.0f }
#define RIGHTINHALECOLLSIONSCALE { 150.0f, -40.0f }
#define INHALECOLLSIONSCALE { 200.0f, 80.0f }

class AttackObject;
class TranslucentBlock;
class Kirby : public BaseActor
{
	friend class AttackObject;
private:
	static Kirby* MainKirby;

public:
	static Kirby* GetMainKirby()
	{
		return MainKirby;
	}

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

	inline bool GetDeathCheck() const
	{
		return DeathCheck;
	}

	void ChangeLevelStart()
	{
		ChangeState(KirbyState::Drop);
		return;
	}

	void ClearForm()
	{
		ChangeState(KirbyState::Change);
		return;
	}

	static int GetKirbyHp()
	{
		return KirbyHp;
	}

	static void HpReset()
	{
		KirbyHp = HPVALUE;
	}

	static void SetKirbyHp(int _Value)
	{
		KirbyHp = _Value;
	}

	TranslucentBlock* GetChangeBackGroundEffect()
	{
		return ChangeBackGroundEffect;
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
	void BreatheStart();
	void FlyStart();
	void BreatheOutStart();
	void DropStart();
	void FlyToLandStart();
	void FlyToTurnUpStart();
	void FlyToTurnLandStart();
	void LevelMoveStart();
	void DamageStart();
	void DamageLandStart();
	virtual void AttackReadyStart();
	void AttackStart();
	void AttackToIdleStart();
	void KeepStart();
	void KeepIdleStart();
	void KeepWalkStart();
	void KeepJumpStart();
	void KeepJumpToDropStart();
	void KeepJumpToLandStart();
	void KeepDamageStart();
	virtual void ChangeStart();
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
	void BreatheUpdate(float _Delta);
	void FlyUpdate(float _Delta);
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
	virtual void ChangeUpdate(float _Delta);
	void DeathUpdate(float _Delta);

	virtual void DirCheck();

	virtual void ChangeAnimationState(const std::string& _StateName);

	void CameraMove(float4 _MovePos);

	void KirbyGravity(float _Delta);

	void InclineCheck(float4& _MovePos);

	TranslucentBlock* ChangeBackGroundEffect = nullptr;
protected:
	void DamageFromMonster()
	{
		++Count;
		KirbyHp -= 20;
	}

	void DamageFromBoss()
	{
		KirbyHp -= 40;
	}

	float RatioValue = 4.0f;
	KirbyState State = KirbyState::Max;
	std::string CurState = "";

	ActorDir Dir = ActorDir::Right;

	static int KirbyHp;
	float Speed = BASEPOWER;
	float RunSpeed = Speed * 1.5f;
	float JumpPower = GRAVITYPOWER;
	float FlyPower = FLYPOWER;

	GameEngineCollision* AttackCollision = nullptr;
	std::vector<GameEngineCollision*> Col;

	bool MapChangeAnimationEnd = false;

	float4 DropStartPos = float4::ZERO;
	float4 LandPos = float4::ZERO;

	// LevelPlayer를 Death시키기 위해 확인하는 변수
	bool DeathCheck = false;

	// 데미지를 입었을 경우 일정 시간동안 무적을 하기위한 변수
	bool NoDamage = false;
	static float NoDamageTimer;

	// 빠르게 두 번 입력을 확인하기 위한 변수
	bool CheckInputA = false;
	float CheckInputATimer = CHECKINPUTTIMERVALUE;

	bool CheckInputD = false;
	float CheckInputDTimer = CHECKINPUTTIMERVALUE;

private:
	int Count = 0;

	MonsterType KeepType = MonsterType::Max;
	AttackObject* StarAttack = nullptr;

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;
};