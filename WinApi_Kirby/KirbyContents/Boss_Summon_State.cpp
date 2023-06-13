#include "BossMonster.h"

void BossMonster::MonsterSummonReadyStart()
{
	ChangeAnimationState("MonsterSummonReady");
}

void BossMonster::MonsterSummonJumpStart()
{
	ChangeAnimationState("MonsterSummonJump");
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