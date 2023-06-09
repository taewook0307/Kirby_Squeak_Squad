#pragma once

#include "BaseActor.h"
#include "ActorEnum.h"

#include <string>
#include <vector>

#define BOSSBODYCOLLISIONPOS { 0.0f, -100.0f }
#define BOSSBODYCOLLISIONSCALE { 200.0f, 200.0f }

#define LEFTSEARCHCOLLISIONPOS { -220.0f, -120.0f }
#define RIGHTSEARCHCOLLISIONPOS { 220.0f, -120.0f }
#define SEARCHCOLLISIONSCALE { 180.0f, 230.0f }

#define BOSSNODAMAGETIMERVALUE 1.5f

class BossMonster : public BaseActor
{
private:
	static BossMonster* MainBoss;

public:
	static BossMonster* GetMainBoss()
	{
		return MainBoss;
	}
public:
	// constrcuter destructer
	BossMonster();
	~BossMonster();

	// delete Function
	BossMonster(const BossMonster& _Other) = delete;
	BossMonster(BossMonster&& _Other) noexcept = delete;
	BossMonster& operator=(const BossMonster& _Other) = delete;
	BossMonster& operator=(BossMonster&& _Other) noexcept = delete;

	inline int GetBossHp() const
	{
		return BossHp;
	}

	inline bool GetEndingCheck()
	{
		return EndingCheck;
	}

protected:
	void StateUpdate(float _Delta);
	void ChangeState(BossState _State);

	void IdleStart();
	void WalkStart();
	void JumpReadyStart();
	void JumpStart();
	void DropStart();
	void AttackReadyStart();
	void AttackRunStart();
	void AttackStart();
	void AttackToIdleStart();
	void FlyReadyStart();
	void FlyUpStart();
	void FlyStart();
	void FlyDropStart();
	void MonsterSummonReadyStart();
	void MonsterSummonJumpStart();
	void MonsterSummonDropStart();
	void MonsterSummonStart();
	void DamageStart();
	void DeathJumpStart();
	void DeathStart();

	void IdleUpdate(float _Delta);
	void WalkUpdate(float _Delta);
	void JumpReadyUpdate(float _Delta);
	void JumpUpdate(float _Delta);
	void DropUpdate(float _Delta);
	void AttackReadyUpdate(float _Delta);
	void AttackRunUpdate(float _Delta);
	void AttackUpdate(float _Delta);
	void AttackToIdleUpdate(float _Delta);
	void FlyReadyUpdate(float _Delta);
	void FlyUpUpdate(float _Delta);
	void FlyUpdate(float _Delta);
	void FlyDropUpdate(float _Delta);
	void MonsterSummonReadyUpdate(float _Delta);
	void MonsterSummonJumpUpdate(float _Delta);
	void MonsterSummonDropUpdate(float _Delta);
	void MonsterSummonUpdate(float _Delta);
	void DamageUpdate(float _Delta);
	void DeathJumpUpdate(float _Delta);
	void DeathUpdate(float _Delta);

	void DirChange();
	void ChangeAnimationState(const std::string& _StateName);

	float RatioValue = 4.0f;
	ActorDir Dir = ActorDir::Left;
	BossState State = BossState::Max;
	std::string CurState = "";
	MonsterType Type = MonsterType::Boss;

	GameEngineCollision* SearchCollision = nullptr;

	bool BossDeath = false;
	bool NoDamage = false;
	float NoDamageTimer = BOSSNODAMAGETIMERVALUE;

	void Damage()
	{
		BossHp -= 40;
	}

	void BossHpReset()
	{
		BossHp = 140;
	}

	void SoundEffectLoad() override;

	// 패턴 동작 On/Off
	void ManualSwitch()
	{
		Manual = !Manual;
	}
private:
	int BossHp = 140;
	float Speed = 150.0f;
	float BossJumpPower = GRAVITYPOWER;

	float EndingTimer = 3.0f;
	bool EndingItemCreate = false;
	bool EndingCheck = false;

	std::vector<GameEngineCollision*> BossCol;

	int FlySoundCount = 1;

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	// 패턴 수동 작동
	bool Manual = false;
};