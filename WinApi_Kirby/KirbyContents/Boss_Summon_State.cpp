#include "BossMonster.h"

#include <GameEngineCore/GameEngineRenderer.h>

void BossMonster::MonsterSummonReadyStart()
{
	ChangeAnimationState("MonsterSummonReady");
}

void BossMonster::MonsterSummonJumpStart()
{
	ChangeAnimationState("MonsterSummonJump");
	SetGravityVector(float4::UP * 700.0f);
}

void BossMonster::MonsterSummonDropStart()
{
	ChangeAnimationState("MonsterSummonDrop");
}

void BossMonster::MonsterSummonStart()
{
	ChangeAnimationState("MonsterSummon");
}

void BossMonster::MonsterSummonReadyUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(BossState::MonsterSummonJump);
		return;
	}
}

void BossMonster::MonsterSummonJumpUpdate(float _Delta)
{
	unsigned int Color = GetGroundColor(EMPTYCOLOR, TOPCHECKPOS);

	if (EMPTYCOLOR == Color)
	{
		Gravity(_Delta);
	}
	else
	{
		GravityReset();
	}

	if (0.0f < GetGravityVector().Y)
	{
		ChangeState(BossState::MonsterSummonDrop);
		return;
	}
}

void BossMonster::MonsterSummonDropUpdate(float _Delta)
{
	unsigned int Color = GetGroundColor(EMPTYCOLOR);

	if (EMPTYCOLOR == Color)
	{
		Gravity(_Delta);
	}
	else
	{
		GravityReset();
		ChangeState(BossState::MonsterSummon);
		return;
	}
}

void BossMonster::MonsterSummonUpdate(float _Delta)
{
	// 몬스터 소환 기능 추가 필요


	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(BossState::Idle);
		return;
	}
}