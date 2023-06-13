#include "BossMonster.h"

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
	static float ShoutingTimer = 0.0f;

	if (ShoutingTimer > 2.0f)
	{
		ChangeState(BossState::MonsterSummonJump);
		return;
	}

	ShoutingTimer += _Delta;
}

void BossMonster::MonsterSummonJumpUpdate(float _Delta)
{

}

void BossMonster::MonsterSummonDropUpdate(float _Delta)
{

}

void BossMonster::MonsterSummonUpdate(float _Delta)
{

}