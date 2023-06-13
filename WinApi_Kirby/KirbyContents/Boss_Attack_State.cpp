#include "BossMonster.h"

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

}

void BossMonster::AttackUpdate(float _Delta)
{

}

void BossMonster::AttackToIdleUpdate(float _Delta)
{

}