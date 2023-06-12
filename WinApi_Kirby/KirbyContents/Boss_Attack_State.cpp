#include "BossMonster.h"

#include <GameEngineCore/GameEngineRenderer.h>

void BossMonster::SearchStart()
{
	ChangeAnimationState("Search");
}

void BossMonster::AttackSummonStart()
{
	ChangeAnimationState("AttackSummon");
}

void BossMonster::AttackStart()
{
	ChangeAnimationState("Attack");
}

void BossMonster::MonsterSummonStart()
{
	ChangeAnimationState("MonsterSummon");
}

void BossMonster::SearchUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(BossState::AttackSummon);
		return;
	}
}

void BossMonster::AttackSummonUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(BossState::Attack);
		return;
	}
}

void BossMonster::AttackUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(BossState::Idle);
		return;
	}
}

void BossMonster::MonsterSummonUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(BossState::Idle);
		return;
	}
}