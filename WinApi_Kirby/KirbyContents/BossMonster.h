#pragma once

#include "BaseActor.h"
#include "ActorEnum.h"

#include <string>

class BossMonster : public BaseActor
{
public:
	// constrcuter destructer
	BossMonster();
	~BossMonster();

	// delete Function
	BossMonster(const BossMonster& _Other) = delete;
	BossMonster(BossMonster&& _Other) noexcept = delete;
	BossMonster& operator=(const BossMonster& _Other) = delete;
	BossMonster& operator=(BossMonster&& _Other) noexcept = delete;

protected:
	void StateUpdate(float _Delta);
	void ChangeState(BossState _State);

	void IdleStart();
	void WalkStart();
	void JumpReadyStart();
	void JumpStart();
	void DropStart();
	void AttackReadyStart();
	void AttackStart();
	void AttackToIdleStart();
	void MonsterSummonReadyStart();
	void MonsterSummonJumpStart();
	void MonsterSummonDropStart();
	void MonsterSummonStart();
	void DamageStart();
	void DeathStart();

	void IdleUpdate(float _Delta);
	void WalkUpdate(float _Delta);
	void JumpReadyUpdate(float _Delta);
	void JumpUpdate(float _Delta);
	void DropUpdate(float _Delta);
	void AttackReady(float _Delta);
	void AttackUpdate(float _Delta);
	void AttackToIdle(float _Delta);
	void MonsterSummonReadyUpdate(float _Delta);
	void MonsterSummonJumpUpdate(float _Delta);
	void MonsterSummonDropUpdate(float _Delta);
	void MonsterSummonUpdate(float _Delta);
	void DamageUpdate(float _Delta);
	void DeathUpdate(float _Delta);

	void DirChange();
	void ChangeAnimationState(const std::string& _StateName);

	float RatioValue = 5.0f;
	ActorDir Dir = ActorDir::Left;
	BossState State = BossState::Max;
	std::string CurState = "";
	MonsterType Type = MonsterType::Boss;

	GameEngineCollision* SearchCollision = nullptr;
private:
	float Speed = 100.0f;

	void Start() override;
	void Update(float _Delta) override;
};