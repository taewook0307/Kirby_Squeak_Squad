#include "AttackMonster.h"

AttackMonster::AttackMonster()
{
}

AttackMonster::~AttackMonster()
{
}

void AttackMonster::StateUpdate(float _Delta)
{
	switch (State)
	{
	case MonsterState::Idle:
		return IdleUpdate(_Delta);
	case MonsterState::Walk:
		return WalkUpdate(_Delta);
	case MonsterState::Attack:
		return AttackUpdate(_Delta);
	case MonsterState::Inhale:
		return InhaleUpdate(_Delta);
	case MonsterState::Damage:
		return DamageUpdate(_Delta);
	case MonsterState::Death:
		return DeathUpdate(_Delta);
	default:
		break;
	}
}

void AttackMonster::ChangeState(MonsterState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case MonsterState::Idle:
			IdleStart();
			break;
		case MonsterState::Walk:
			WalkStart();
			break;
		case MonsterState::Attack:
			AttackStart();
			break;
		case MonsterState::Inhale:
			InhaleStart();
			break;
		case MonsterState::Damage:
			DamageStart();
			break;
		case MonsterState::Death:
			DeathStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}

void AttackMonster::AttackStart()
{
	ChangeAnimationState("Attack");
}

void AttackMonster::AttackUpdate(float _Delta) {}