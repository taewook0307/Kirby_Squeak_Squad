#pragma once

#include "Monster.h"

class AttackMonster : public Monster
{
public:
	// constrcuter destructer
	AttackMonster();
	~AttackMonster();

	// delete Function
	AttackMonster(const AttackMonster& _Other) = delete;
	AttackMonster(AttackMonster&& _Other) noexcept = delete;
	AttackMonster& operator=(const AttackMonster& _Other) = delete;
	AttackMonster& operator=(AttackMonster&& _Other) noexcept = delete;

protected:
	void StateUpdate(float _Delta);
	void ChangeState(MonsterState _State);
	void AttackStart();
	virtual void AttackUpdate(float _Delta);

private:

};

