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
	void ChangeState(MonsterState _State);

	void IdleStart();
	void WalkStart();
	void JumpStart();
	void DropStart();
	void SearchStart();
	void AttackSumonStart();
	void AttackStart();
	void MonsterSummonStart();
	void DamageStart();
	void DeathStart();

	void IdleUpdate(float _Delta);
	void WalkUpdate(float _Delta);
	void JumpUpdate(float _Delta);
	void DropUpdate(float _Delta);
	void SearchUpdate(float _Delta);
	void AttackSumonUpdate(float _Delta);
	void AttackUpdate(float _Delta);
	void MonsterSummonUpdate(float _Delta);
	void DamageUpdate(float _Delta);
	void DeathUpdate(float _Delta);

	void DirChange();

	float RatioValue = 3.0f;
	ActorDir Dir = ActorDir::Left;
	std::string CurState = "";
	MonsterType Type = MonsterType::Boss;

	GameEngineCollision* SearchCollision = nullptr;
private:
	void Start() override;
	void Update(float _Delta) override;
};