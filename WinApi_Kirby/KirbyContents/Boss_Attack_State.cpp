#include "BossMonster.h"

#include <GameEngineCore/GameEngineRenderer.h>

void BossMonster::AttackReadyStart()
{
	ChangeAnimationState("AttackReady");
}

void BossMonster::AttackStart()
{
	ChangeAnimationState("Attack");
}

void BossMonster::AttackToIdleStart()
{
	ChangeAnimationState("AttackToIdle");
}

void BossMonster::AttackReadyUpdate(float _Delta)
{
	static float ShoutingTimer = 0.0f;

	if (ShoutingTimer > 2.0f)
	{
		ShoutingTimer = 0.0f;
		ChangeState(BossState::Attack);
		return;
	}

	ShoutingTimer += _Delta;
}

void BossMonster::AttackUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(BossState::AttackToIdle);
		return;
	}
}

void BossMonster::AttackToIdleUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(BossState::Idle);
		return;
	}
}